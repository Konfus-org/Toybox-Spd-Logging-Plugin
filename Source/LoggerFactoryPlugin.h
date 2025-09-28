#pragma once
#include <Tbx/Plugins/Plugin.h>
#include <Tbx/Debug/ILogger.h>

namespace SpdLogging
{
    class SpdLoggerFactoryPlugin final
        : public Tbx::Plugin
        , public Tbx::ILoggerFactory
    {
    public:
        SpdLoggerFactoryPlugin(std::weak_ptr<Tbx::App> app);
        ~SpdLoggerFactoryPlugin() override;

        std::shared_ptr<Tbx::ILogger> Create(const std::string& name, const std::string filePath) override;

    protected:
        Tbx::ILogger* New();
        void Delete(Tbx::ILogger* logger);
    };

    TBX_REGISTER_PLUGIN(SpdLoggerFactoryPlugin);
}

