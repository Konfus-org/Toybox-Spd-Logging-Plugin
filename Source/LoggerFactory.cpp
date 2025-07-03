#include "LoggerFactory.h"
#include "SpdLogger.h"

namespace SpdLogging
{
    void SpdLoggerFactory::OnLoad()
    {
    }

    void SpdLoggerFactory::OnUnload()
    {
        spdlog::drop_all();
    }

    void DeleteLogger(SpdLogger* loggerToDelete)
    {
        delete loggerToDelete;
    }

    std::shared_ptr<Tbx::ILogger> SpdLoggerFactory::Create(const std::string& name, const std::string filePath)
    {
        auto* newLogger = new SpdLogger();
        newLogger->Open(name, filePath);
        return std::shared_ptr<SpdLogger>(newLogger, [](SpdLogger* loggerToDelete) { DeleteLogger(loggerToDelete); });
    }
}
