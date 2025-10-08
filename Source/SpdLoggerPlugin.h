#pragma once
#include <Tbx/Plugins/Plugin.h>
#include <Tbx/Debug/ILogger.h>
#include <spdlog/spdlog.h>

namespace Tbx::Plugins::SpdLogging
{
    class SpdLoggerPlugin final
        : public Plugin
        , public ILogger
    {
    public:
        SpdLoggerPlugin(Ref<EventBus> eventBus);
        ~SpdLoggerPlugin() override;
        void Open(const std::string& name, const std::string& filePath) override;
        void Close() override;
        void Write(int lvl, const std::string& msg) override;
        void Flush() override;

    private:
        Ref<spdlog::logger> _spdLogger = nullptr;
    };

    TBX_REGISTER_PLUGIN(SpdLoggerPlugin);
}

