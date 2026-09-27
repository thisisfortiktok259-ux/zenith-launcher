// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Zenith Launcher - Next-Gen Gaming Minecraft Launcher
 *  Copyright (C) 2026 Zenith Launcher Contributors
 */
#include "ZenithDiscordRPC.h"

#include <QDataStream>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcessEnvironment>
#include <QStandardPaths>
#include <QDebug>

namespace {
const char* ZENITH_DISCORD_APP_ID = "1200000000000000000"; // Generic gaming application ID for Zenith

QString getIpcPipePath(int index = 0)
{
#if defined(Q_OS_WIN)
    return QStringLiteral(R"(\\.\pipe\discord-ipc-%1)").arg(index);
#else
    QString xdg = QProcessEnvironment::systemEnvironment().value("XDG_RUNTIME_DIR");
    if (!xdg.isEmpty() && QDir(xdg).exists()) {
        return QString("%1/discord-ipc-%2").arg(xdg).arg(index);
    }
    return QString("/tmp/discord-ipc-%1").arg(index);
#endif
}
} // namespace

ZenithDiscordRPC& ZenithDiscordRPC::instance()
{
    static ZenithDiscordRPC s_instance;
    return s_instance;
}

ZenithDiscordRPC::ZenithDiscordRPC(QObject* parent) : QObject(parent), m_socket(std::make_unique<QLocalSocket>(this))
{
    connect(m_socket.get(), &QLocalSocket::connected, this, &ZenithDiscordRPC::onConnected);
    connect(m_socket.get(), &QLocalSocket::disconnected, this, &ZenithDiscordRPC::onDisconnected);
    connect(m_socket.get(), &QLocalSocket::readyRead, this, &ZenithDiscordRPC::onReadyRead);
}

ZenithDiscordRPC::~ZenithDiscordRPC()
{
    clearActivity();
    if (m_socket && m_socket->isOpen()) {
        m_socket->close();
    }
}

void ZenithDiscordRPC::initialize()
{
    if (m_connected || (m_socket && m_socket->state() == QLocalSocket::ConnectingState)) {
        return;
    }

    for (int i = 0; i < 10; ++i) {
        QString pipePath = getIpcPipePath(i);
        m_socket->connectToServer(pipePath);
        if (m_socket->waitForConnected(200)) {
            break;
        }
    }
}

void ZenithDiscordRPC::onConnected()
{
    m_connected = true;
    sendHandshake();
}

void ZenithDiscordRPC::onDisconnected()
{
    m_connected = false;
}

void ZenithDiscordRPC::onReadyRead()
{
    if (!m_socket) return;
    m_socket->readAll(); // Drain incoming frames
}

void ZenithDiscordRPC::writePacket(int opcode, const QByteArray& data)
{
    if (!m_socket || !m_socket->isOpen()) return;

    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << static_cast<qint32>(opcode);
    stream << static_cast<qint32>(data.size());
    packet.append(data);

    m_socket->write(packet);
    m_socket->flush();
}

void ZenithDiscordRPC::sendHandshake()
{
    QJsonObject obj;
    obj["v"] = 1;
    obj["client_id"] = QString(ZENITH_DISCORD_APP_ID);

    QByteArray data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    writePacket(0, data); // Opcode 0 = Handshake

    if (!m_currentDetails.isEmpty()) {
        sendActivity(m_currentDetails, m_currentState, m_sessionStart);
    }
}

void ZenithDiscordRPC::setPlayingInstance(const QString& instanceName, const QString& mcVersion, const QString& loader)
{
    m_sessionStart = QDateTime::currentSecsSinceEpoch();
    m_currentDetails = QString("Playing: %1").arg(instanceName);
    m_currentState = loader.isEmpty() ? QString("Minecraft %1").arg(mcVersion)
                                     : QString("Minecraft %1 (%2)").arg(mcVersion, loader);

    if (!m_connected) {
        initialize();
    } else {
        sendActivity(m_currentDetails, m_currentState, m_sessionStart);
    }
}

void ZenithDiscordRPC::sendActivity(const QString& details, const QString& state, qint64 startTime)
{
    if (!m_connected) return;

    QJsonObject timestamps;
    timestamps["start"] = startTime;

    QJsonObject assets;
    assets["large_image"] = "zenith_logo";
    assets["large_text"] = "Zenith Launcher (Gamer Edition)";
    assets["small_image"] = "minecraft";
    assets["small_text"] = "Minecraft";

    QJsonObject activity;
    activity["details"] = details;
    activity["state"] = state;
    activity["timestamps"] = timestamps;
    activity["assets"] = assets;

    QJsonObject args;
    args["pid"] = static_cast<qint64>(QCoreApplication::applicationPid());
    args["activity"] = activity;

    QJsonObject frame;
    frame["cmd"] = "SET_ACTIVITY";
    frame["args"] = args;
    frame["nonce"] = QString::number(QDateTime::currentMSecsSinceEpoch());

    QByteArray data = QJsonDocument(frame).toJson(QJsonDocument::Compact);
    writePacket(1, data); // Opcode 1 = Frame
}

void ZenithDiscordRPC::clearActivity()
{
    m_currentDetails.clear();
    m_currentState.clear();
    m_sessionStart = 0;

    if (!m_connected) return;

    QJsonObject args;
    args["pid"] = static_cast<qint64>(QCoreApplication::applicationPid());

    QJsonObject frame;
    frame["cmd"] = "SET_ACTIVITY";
    frame["args"] = args;
    frame["nonce"] = QString::number(QDateTime::currentMSecsSinceEpoch());

    QByteArray data = QJsonDocument(frame).toJson(QJsonDocument::Compact);
    writePacket(1, data);
}
