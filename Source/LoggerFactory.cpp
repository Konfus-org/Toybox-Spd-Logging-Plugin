#include "LoggerFactory.h"
#include "SpdLogger.h"

namespace SpdLogging
{
    void SpdLoggerFactory::OnUnload()
    {
        spdlog::shutdown();
    }

    std::shared_ptr<Tbx::ILogger> SpdLoggerFactory::Create(const std::string& name, const std::string filePath)
    {
        auto logger = std::shared_ptr<Tbx::ILogger>(New(), [this](Tbx::ILogger* logger) { Delete(logger); });
        logger->Open(name, filePath);
        return logger;
    }

    Tbx::ILogger* SpdLoggerFactory::New()
    {
        auto* logger = new SpdLogger();
        return logger;
    }

    void SpdLoggerFactory::Delete(Tbx::ILogger* logger)
    {
        delete logger;
    }
}
