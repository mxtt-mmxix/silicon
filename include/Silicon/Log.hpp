/*
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Matthew McCall
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SILICON_LOG_HPP
#define SILICON_LOG_HPP

#include <fmt/core.h>

#include "Silicon/String.hpp"

namespace Si {

class String;

/**
 * A log entry. This holds information to be logged independent of the backend.
 *
 * This allows the same information to be logged to multiple backends, e.g.: stdout or a file.
 */
struct LogEntry {

    /**
     * The type of log
     */
    enum class Type {
        Engine, /**< Logs from the engine. Please refrain from using in your application. */
        Client /**< Logs from the client. Use this to for your logging. */
    };

    enum class Level {
        Trace, /**< Verbose information, not informative to the end-user. */
        Information, /**< Information that maybe relevant to the end user. */
        Debug, /**< Debug, technical information. */
        Warning, /**< Information that could suggest an error but does not affect application. */
        Error, /**< Information that may affect the engine and may cause a crash. */
        Critical /**< Information pertaining to a crash. */
    };

    Type type = Type::Client;
    Level level = Level::Information;
    String message;
};

/**
 * Logs a log entry. See macros
 */
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
