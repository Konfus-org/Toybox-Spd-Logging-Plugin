#pragma once
#include <Tbx/Events/EventCoordinator.h>
#include <Tbx/Ids/UID.h>
#include <spdlog/spdlog.h>

namespace SpdLogging
{
    class SpdLogger final : public Tbx::ILogger
    {
    public:
        ~SpdLogger() override;

        void Open(const std::string& name, const std::string& filePath) override;
        void Close() override;
        void Write(int lvl, const std::string& msg) override;
        void Flush() override;
        std::string GetName() override { return _spdLogger->name(); }

    private:
        std::shared_ptr<spdlog::logger> _spdLogger;
    };
}

