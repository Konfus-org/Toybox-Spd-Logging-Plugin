#include "LoggerFactory.h"
#include "SpdLogger.h"

namespace SpdLogging
{
    void SpdLoggerFactory::OnLoad()
    {
    }

    void SpdLoggerFactory::OnUnload()
    {
        spdlog::shutdown();
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
