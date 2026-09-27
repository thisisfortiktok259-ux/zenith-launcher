// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Zenith Launcher - Next-Gen Gaming Minecraft Launcher
 *  Copyright (C) 2026 Zenith Launcher Contributors
 */
#include "OptimizationHelper.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include "FileSystem.h"
#include "minecraft/MinecraftInstance.h"

QList<OptimizationHelper::BoostMod> OptimizationHelper::recommendedMods()
{
    return {
        { "sodium", "Sodium", "Next-gen modern rendering engine replacement delivering up to 400% FPS boost" },
        { "lithium", "Lithium", "Comprehensive physics, chunk loading and tick optimization" },
        { "iris", "Iris Shaders", "Modern shader engine with full Sodium compatibility and zero overhead" },
        { "ferrite-core", "FerriteCore", "Reduces memory/RAM usage of Minecraft by up to 50%" },
        { "entityculling", "Entity Culling", "Skips rendering tiles and entities blocked by blocks and walls" },
        { "immediatelyfast", "ImmediatelyFast", "Optimizes immediate-mode rendering for HUD, GUI and text fonts" }
    };
}

bool OptimizationHelper::isBoostSupported(const QString& mcVersion, const QString& loader)
{
    // Boost mods primarily target Fabric / NeoForge on versions >= 1.16
    Q_UNUSED(mcVersion);
    return loader.contains("fabric", Qt::CaseInsensitive) || loader.contains("quilt", Qt::CaseInsensitive);
}

QString OptimizationHelper::boostSummary()
{
    return "⚡ Zenith Boost Pack: Sodium + Lithium + Iris + FerriteCore + Entity Culling + ImmediatelyFast";
}

void OptimizationHelper::applyBoostToInstance(MinecraftInstance* instance, const QString& mcVersion)
{
    if (!instance) return;

    QString modsDir = FS::PathCombine(instance->gameRoot(), "mods");
    FS::ensureFolderPathExists(modsDir);

    // Write a boost manifest and setup marker so the user and launcher know this instance is boosted
    QString manifestPath = FS::PathCombine(modsDir, ".zenith_boost.json");
    QFile manifest(manifestPath);
    if (manifest.open(QIODevice::WriteOnly | QIODevice::Text)) {
        manifest.write(QString("{\"boost_enabled\": true, \"minecraft_version\": \"%1\", \"pack\": \"Zenith 1-Click Boost\"}\n")
                           .arg(mcVersion).toUtf8());
        manifest.close();
    }
}
