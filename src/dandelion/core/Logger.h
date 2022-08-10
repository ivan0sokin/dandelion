#ifndef DANDELION_LOGGER_H
#define DANDELION_LOGGER_H

#include "Core.h"

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Dandelion {
    enum class LogLevel : int {
        Trace = SPDLOG_LEVEL_TRACE,
        Debug = SPDLOG_LEVEL_DEBUG,
        Info = SPDLOG_LEVEL_INFO,
        Warn = SPDLOG_LEVEL_WARN,
        Error = SPDLOG_LEVEL_ERROR,
        Critical = SPDLOG_LEVEL_CRITICAL
    };

    class DANDELION_API Logger {
    public:
        Logger() noexcept = default;

        inline Logger(std::string_view loggerName, std::string_view outputFileName) noexcept : mLoggerName(loggerName), mOutputFileName(outputFileName) {}

        ~Logger() noexcept = default;

        void Create() noexcept;

        void Log(const LogLevel &logLevel, std::string_view message) noexcept;

    private:
        std::shared_ptr<spdlog::logger> mInternalLogger;
        std::string mLoggerName, mOutputFileName;
    };

    inline static auto coreLogger = Logger("Core", "Dandelion.log");
}

#ifdef DANDELION_DEBUG
    #define _DANDELION_DEBUG_LOG(message) Dandelion::coreLogger.Log(Dandelion::LogLevel::Debug, (message))
#else
    #define _DANDELION_DEBUG_LOG(message)
#endif

#endif