#pragma once
#include <Tbx/Plugins/Plugin.h>
#include <Tbx/Debug/ILogger.h>

namespace SpdLogging
{
    class SpdLoggerFactoryPlugin
        : public Tbx::Plugin
        , public Tbx::ILoggerFactory
    {
    public:
        SpdLoggerFactoryPlugin(std::weak_ptr<Tbx::App> app) {}
        void OnUnload() override;

        std::shared_ptr<Tbx::ILogger> Create(const std::string& name, const std::string filePath) override;

    protected:
        Tbx::ILogger* New();
        void Delete(Tbx::ILogger* logger);
    };

    TBX_REGISTER_PLUGIN(SpdLoggerFactoryPlugin);
}

