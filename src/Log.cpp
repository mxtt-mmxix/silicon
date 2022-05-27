//
// Created by Matthew McCall on 5/27/22.
//

#include "Silicon/Log.hpp"

#include <sstream>
#include <thread>

#include <fmt/color.h>
#include <SDL_timer.h>

namespace Si {

void Log(const LogEntry& entry)
{
    std::stringstream ss;
    ss << std::this_thread::get_id();

    static std::mutex s_mutex;
    std::unique_lock lock { s_mutex };

    switch (entry.type) {
    case LogEntry::Type::Engine:
        fmt::print("[{:>12.3f}][{:>16}][Engine][", static_cast<float>(SDL_GetTicks64()) / 1000.0f, ss.str());
        break;
    case LogEntry::Type::Client:
        fmt::print("[{:>12.3f}][{:>16}][Client][", static_cast<float>(SDL_GetTicks64()) / 1000.0f, ss.str());
        break;
    }

    switch (entry.level) {
    case LogEntry::Level::Trace:
        fmt::print(fmt::fg(fmt::color::gray), "{:>8}", "trace");
        break;
    case LogEntry::Level::Information:
        fmt::print("{:>8}", "info");
        break;
    case LogEntry::Level::Debug:
        fmt::print(fmt::fg(fmt::color::cyan), "{:>8}", "debug");
        break;
    case LogEntry::Level::Warning:
        fmt::print(fmt::fg(fmt::color::yellow), "{:>8}", "warning");
        break;
    case LogEntry::Level::Error:
        fmt::print(fmt::fg(fmt::color::orange), "{:>8}", "error");
        break;
    case LogEntry::Level::Critical:
        fmt::print(fmt::fg(fmt::color::red), "{:>8}", "critical");
        break;
    }

    fmt::print("] {}\n", entry.message);
}

String::String(std::string&& other)
    : basic_string(other.begin(), other.end())
{
}

} // Si