#include "SpdLoggerPlugin.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace SpdLogging
{
    SpdLoggerPlugin::SpdLoggerPlugin(Tbx::Ref<Tbx::EventBus> eventBus)
    {
    }

    SpdLoggerPlugin::~SpdLoggerPlugin()
    {
        Close();
        spdlog::shutdown();
    }

    void SpdLoggerPlugin::Open(const std::string& name, const std::string& filePath)
    {
        if (_spdLogger)
        {
            // Logger already exists, close it first
            Close();
        }

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
        spdlog::initialize_logger(_spdLogger);
    }

    void SpdLoggerPlugin::Close()
    {
        Flush();
        spdlog::drop(_spdLogger->name());
        _spdLogger = nullptr;
    }

    void SpdLoggerPlugin::Write(int lvl, const std::string& msg)
    {
        _spdLogger->log(spdlog::source_loc{}, (spdlog::level::level_enum)lvl, msg);
    }

    void SpdLoggerPlugin::Flush()
    {
        _spdLogger->flush();
    }
}
