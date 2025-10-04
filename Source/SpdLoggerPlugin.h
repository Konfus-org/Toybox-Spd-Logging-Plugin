#pragma once
#include <Tbx/Plugins/Plugin.h>
#include <Tbx/Debug/ILogger.h>
#include <spdlog/spdlog.h>

namespace SpdLogging
{
    class SpdLoggerPlugin final
        : public Tbx::Plugin
        , public Tbx::ILogger
    {
    public:
        SpdLoggerPlugin(Tbx::Ref<Tbx::EventBus> eventBus);
        ~SpdLoggerPlugin() override;
        void Open(const std::string& name, const std::string& filePath) override;
        void Close() override;
        void Write(int lvl, const std::string& msg) override;
        void Flush() override;

    private:
        Tbx::Ref<spdlog::logger> _spdLogger = nullptr;
    };

    TBX_REGISTER_PLUGIN(SpdLoggerPlugin);
}

