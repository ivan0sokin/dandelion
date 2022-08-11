#include "Logger.h"

namespace Dandelion {

    void Logger::Register() noexcept {
        using namespace spdlog;

        auto consoleSink = std::make_shared<sinks::stdout_color_sink_mt>();
        auto fileSink = std::make_shared<sinks::basic_file_sink_mt>(mOutputFileName, true);

        consoleSink->set_pattern("%^[%T] %n: %v%$");
        fileSink->set_pattern("[%T %D] %n: %v");

        mInternalLogger = std::make_shared<logger>(mLoggerName, sinks_init_list{consoleSink, fileSink});
        register_logger(mInternalLogger);

        mInternalLogger->set_level(level::trace);
        mInternalLogger->flush_on(level::warn);
    }

    void Logger::Log(const LogLevel &logLevel, std::string_view message) noexcept {
        mInternalLogger->log(static_cast<spdlog::level::level_enum>(logLevel), message);
    }

    std::shared_ptr<CoreLogger> CoreLogger::Instance() noexcept {
        static std::shared_ptr<CoreLogger> instance{new CoreLogger()};
        return instance;
    }

}