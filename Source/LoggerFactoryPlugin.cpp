#include "LoggerFactoryPlugin.h"
#include "SpdLogger.h"

namespace SpdLogging
{
    SpdLoggerFactoryPlugin::SpdLoggerFactoryPlugin(std::weak_ptr<Tbx::App> app)
        : Tbx::Plugin(app)
    {

    }

    SpdLoggerFactoryPlugin::~SpdLoggerFactoryPlugin()
    {
        spdlog::shutdown();
    }

    std::shared_ptr<Tbx::ILogger> SpdLoggerFactoryPlugin::Create(const std::string& name, const std::string filePath)
    {
        auto logger = std::shared_ptr<Tbx::ILogger>(New(), [this](Tbx::ILogger* logger) { Delete(logger); });
        logger->Open(name, filePath);
        return logger;
    }

    Tbx::ILogger* SpdLoggerFactoryPlugin::New()
    {
        auto* logger = new SpdLogger();
        return logger;
    }

    void SpdLoggerFactoryPlugin::Delete(Tbx::ILogger* logger)
    {
        delete logger;
    }
}
