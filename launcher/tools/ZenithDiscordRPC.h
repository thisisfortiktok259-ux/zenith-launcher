// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Zenith Launcher - Next-Gen Gaming Minecraft Launcher
 *  Copyright (C) 2026 Zenith Launcher Contributors
 */
#pragma once

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QLocalSocket>
#include <memory>

class ZenithDiscordRPC : public QObject {
    Q_OBJECT
public:
    static ZenithDiscordRPC& instance();

    void initialize();
    void setPlayingInstance(const QString& instanceName, const QString& mcVersion, const QString& loader = "");
    void clearActivity();

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    ZenithDiscordRPC(QObject* parent = nullptr);
    ~ZenithDiscordRPC() override;

    void sendHandshake();
    void sendActivity(const QString& details, const QString& state, qint64 startTime);
    void writePacket(int opcode, const QByteArray& data);

    std::unique_ptr<QLocalSocket> m_socket;
    bool m_connected = false;
    qint64 m_sessionStart = 0;
    QString m_currentDetails;
    QString m_currentState;
};
