//
// Created by Matthew McCall on 5/27/22.
//

#ifndef SILICON_LOG_HPP
#define SILICON_LOG_HPP

#include <fmt/core.h>

#include "Types.hpp"

namespace Si {

struct LogEntry {
    enum class Type {
        Engine,
        Client
    };

    enum class Level {
        Trace,
        Information,
        Debug,
        Warning,
        Error,
        Critical
    };

    Type type = Type::Client;
    Level level = Level::Information;
    String message;
};

void Log(const LogEntry&);

} // Si

/**
 * @brief Logs warning messages. This is enabled in Release builds
 */
#define SI_WARN(...) Si::Log({ Si::LogEntry::Type::Client, Si::LogEntry::Level::Warning, fmt::format(__VA_ARGS__) });

/**
 * @brief Logs non-fatal error messages. This is enabled in Release builds
 */
#define SI_ERROR(...) Si::Log({ Si::LogEntry::Type::Client, Si::LogEntry::Level::Error, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs fatal error messages. This is enabled in Release builds
 */
#define SI_CRITICAL(...) Si::Log({ Si::LogEntry::Type::Client, Si::LogEntry::Level::Critical, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs warning messages. This is enabled in Release builds. For engine use only
 */
#define SI_CORE_WARN(...) Si::Log({ Si::LogEntry::Type::Engine, Si::LogEntry::Level::Warning, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs non-fatal error messages. This is enabled in Release builds. For engine use only
 */
#define SI_CORE_ERROR(...) Si::Log({ Si::LogEntry::Type::Engine, Si::LogEntry::Level::Error, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs fatal error messages. This is enabled in Release builds. For engine use only
 */
#define SI_CORE_CRITICAL(...) Si::Log({ Si::LogEntry::Type::Engine, Si::LogEntry::Level::Critical, fmt::format(__VA_ARGS__) })

#ifdef NDEBUG

#define SI_TRACE
#define SI_INFO
#define SI_DEBUG

#define SI_CORE_TRACE
#define SI_CORE_INFO
#define SI_CORE_DEBUG

#else

/**
 * @brief Logs trace messages. This is disabled in Release builds.
 */
#define SI_TRACE(...) Si::Log({ Si::LogEntry::Type::Client, Si::LogEntry::Level::Trace, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs informational messages. This is disabled in Release builds.
 */
#define SI_INFO(...) Si::Log({ Si::LogEntry::Type::Client, Si::LogEntry::Level::Information, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs debug messages. This is disabled in Release builds.
 */
#define SI_DEBUG(...) Si::Log({ Si::LogEntry::Type::Client, Si::LogEntry::Level::Debug, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs trace messages. This is disabled in Release builds. For engine use only
 */
#define SI_CORE_TRACE(...) Si::Log({ Si::LogEntry::Type::Engine, Si::LogEntry::Level::Trace, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs informational messages. This is disabled in Release builds. For engine use only
 */
#define SI_CORE_INFO(...) Si::Log({ Si::LogEntry::Type::Engine, Si::LogEntry::Level::Information, fmt::format(__VA_ARGS__) })

/**
 * @brief Logs debug messages. This is disabled in Release builds. For engine use only
 */
#define SI_CORE_DEBUG(...) Si::Log({ Si::LogEntry::Type::Engine, Si::LogEntry::Level::Debug, fmt::format(__VA_ARGS__) })

#endif

#endif // SILICON_LOG_HPP
