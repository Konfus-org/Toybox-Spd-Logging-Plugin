#pragma once
#include <Tbx/PluginAPI/RegisterPlugin.h>

namespace SpdLogging
{
    class SpdLoggerFactory : public Tbx::ILoggerFactoryPlugin
    {
    public:
        void OnLoad() override;
        void OnUnload() override;

        std::shared_ptr<Tbx::ILogger> Create(const std::string& name, const std::string filePath) override;

    protected:
        Tbx::ILogger* New();
        void Delete(Tbx::ILogger* logger);
    };


    TBX_REGISTER_PLUGIN(SpdLoggerFactory);
}

