#pragma once
#include <Tbx/Plugin API/RegisterPlugin.h>
#include <Tbx/Events/EventCoordinator.h>
#include <Tbx/Events/LogEvents.h>
#include <Tbx/Ids/UID.h>
#include <spdlog/spdlog.h>

namespace SpdLogging
{
    class SpdLogger final : public Tbx::ILoggerPlugin
    {
    public:
        void OnLoad() override;
        void OnUnload() override;

        void Open(const std::string& name, const std::string& filePath) override;
        void Close() override;
        void Log(int lvl, const std::string& msg) override;
        void Flush() override;
        std::string GetName() override { return _spdLogger->name(); }

    private:
        void OnWriteToLogEvent(Tbx::WriteLineToLogRequest& e);
        void OnOpenLogEvent(Tbx::OpenLogRequest& e);
        void OnCloseLogEvent(Tbx::CloseLogRequest& e);

        Tbx::UID _writeToLogEventId = -1;
        Tbx::UID _openLogEventId = -1;
        Tbx::UID _closeLogEventId = -1;

        std::shared_ptr<spdlog::logger> _spdLogger;
    };

    TBX_REGISTER_PLUGIN(SpdLogger);
}

