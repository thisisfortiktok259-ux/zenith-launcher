#pragma once

#include <memory>
#include "BaseVersion.h"
#include "InstanceTask.h"
#include "minecraft/MinecraftInstance.h"

class VanillaCreationTask final : public InstanceTask {
    Q_OBJECT
   public:
    explicit VanillaCreationTask(BaseVersion::Ptr version, bool boost = false) : m_version(std::move(version)), m_boost(boost) {}
    VanillaCreationTask(BaseVersion::Ptr version, QString loader, BaseVersion::Ptr loaderVersion, bool boost = false);

    void executeTask() override;

   private:
    std::unique_ptr<MinecraftInstance> m_instance;

    // Version to update to / create of the instance.
    BaseVersion::Ptr m_version;

    bool m_usingLoader = false;
    bool m_boost = false;
    QString m_loader;
    BaseVersion::Ptr m_loaderVersion;
};
