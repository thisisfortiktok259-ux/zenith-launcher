// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Zenith Launcher - Next-Gen Gaming Minecraft Launcher
 *  Copyright (C) 2026 Zenith Launcher Contributors
 */
#pragma once

#include <QString>
#include <QStringList>
#include <QList>

class MinecraftInstance;

class OptimizationHelper {
public:
    struct BoostMod {
        QString slug;
        QString displayName;
        QString description;
    };

    static QList<BoostMod> recommendedMods();
    static bool isBoostSupported(const QString& mcVersion, const QString& loader);
    static QString boostSummary();
    static void applyBoostToInstance(MinecraftInstance* instance, const QString& mcVersion);
};
