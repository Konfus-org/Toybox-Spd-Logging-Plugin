#pragma once
#include <Tbx/Plugin API/RegisterPlugin.h>

namespace SpdLogging
{
    class SpdLoggerFactory : public Tbx::ILoggerFactoryPlugin
    {
        void OnLoad() override;
        void OnUnload() override;
        std::shared_ptr<Tbx::ILogger> Create(const std::string& name, const std::string filePath = "") override;
    };


    TBX_REGISTER_PLUGIN(SpdLoggerFactory);
}

