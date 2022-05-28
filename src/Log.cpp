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

#include "Silicon/Log.hpp"
#include "Silicon/Types.hpp"

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

} // Si