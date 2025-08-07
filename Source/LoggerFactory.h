#pragma once
#include <Tbx/Plugin API/RegisterPlugin.h>

namespace SpdLogging
{
    class SpdLoggerFactory : public Tbx::ILoggerFactoryPlugin
    {
    public:
        void OnLoad() override;
        void OnUnload() override;

    protected:
        Tbx::ILogger* New() override;
        void Delete(Tbx::ILogger* logger) override;
    };


    TBX_REGISTER_PLUGIN(SpdLoggerFactory);
}

