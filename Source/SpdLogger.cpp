#pragma once
#include "SpdLogger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace SpdLogging
{
    void SpdLogger::OnLoad()
    {
        _writeToLogEventId = Tbx::EventCoordinator::Subscribe<Tbx::WriteLineToLogRequest>(TBX_BIND_FN(OnWriteToLogEvent));
        _openLogEventId = Tbx::EventCoordinator::Subscribe<Tbx::OpenLogRequest>(TBX_BIND_FN(OnOpenLogEvent));
        _closeLogEventId = Tbx::EventCoordinator::Subscribe<Tbx::CloseLogRequest>(TBX_BIND_FN(OnCloseLogEvent));
    }

    void SpdLogger::OnUnload()
    {
        Tbx::EventCoordinator::Unsubscribe<Tbx::WriteLineToLogRequest>(_writeToLogEventId);
        Tbx::EventCoordinator::Unsubscribe<Tbx::OpenLogRequest>(_openLogEventId);
        Tbx::EventCoordinator::Unsubscribe<Tbx::CloseLogRequest>(_closeLogEventId);

        Close();

        spdlog::drop_all();
    }

    void SpdLogger::OnWriteToLogEvent(Tbx::WriteLineToLogRequest& e)
    {
        if (_spdLogger == nullptr) Open(e.GetLogName(), e.GetLogFilePath());
        Log((int)e.GetLogLevel(), e.GetLineToWriteToLog());
        e.IsHandled = true;
    }

    void SpdLogger::OnOpenLogEvent(Tbx::OpenLogRequest& e)
    {
        Open(e.GetLogName(), e.GetLogFilePath());
        e.IsHandled = true;
    }

    void SpdLogger::OnCloseLogEvent(Tbx::CloseLogRequest& e)
    {
        Close();
        e.IsHandled = true;
    }

    void SpdLogger::Open(const std::string& name, const std::string& filePath)
    {
        // First close any logs we may have open
        Close(); // TODO: support multiple logs at once!

        // Create console and file sinks
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        if (!filePath.empty())
        {
            // We have file path, make file sync
            auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filePath);

            // Combine file and console sinks into a logger
            spdlog::logger multiSinkLogger(name, { consoleSink, fileSink });
            _spdLogger = std::make_shared<spdlog::logger>(multiSinkLogger);
        }
        else
        {
            // Just use console
            _spdLogger = std::make_shared<spdlog::logger>(name, consoleSink);
        }

        // Set up and register the logger
        _spdLogger->set_pattern("%^[%T]: %v%$");
        _spdLogger->set_level(spdlog::level::level_enum::trace);
        spdlog::register_logger(_spdLogger);
    }

    void SpdLogger::Close()
    {
        if (_spdLogger == nullptr) return;

        Flush();
        spdlog::drop(_spdLogger->name());
        _spdLogger = nullptr;
    }

    void SpdLogger::Log(int lvl, const std::string& msg)
    {
        _spdLogger->log(spdlog::source_loc{}, (spdlog::level::level_enum)lvl, msg);
    }

    void SpdLogger::Flush()
    {
        _spdLogger->flush();
    }
}
