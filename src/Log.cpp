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
#include "Silicon/StopWatch.hpp"

#include <sstream>
#include <thread>

#include <fmt/color.h>

namespace {
    std::mutex s_mutex;
}

namespace Si {

void Log(const LogEntry& entry)
{
    static Si::StopWatch s_stopwatch;
    
    std::stringstream ss;
    ss << std::this_thread::get_id();

    std::unique_lock lock { s_mutex };

    switch (entry.type) {
    case LogEntry::Type::Engine:
        fmt::print("{:>12.3f} {:>16} (Engine) ", s_stopwatch.GetElapsedTime(), ss.str());
        break;
    case LogEntry::Type::Client:
        fmt::print(" {:>12.3f} {:>16} ", s_stopwatch.GetElapsedTime(), ss.str());
        break;
    }

    switch (entry.level) {
    case LogEntry::Level::Trace:
        fmt::print(fmt::bg(fmt::color::gray), "{:>10}", "TRACE ");
        break;
    case LogEntry::Level::Information:
        fmt::print(bg(fmt::color::white) | fg(fmt::color::black), "{:>10}", "INFO ");
        break;
    case LogEntry::Level::Debug:
        fmt::print(fmt::bg(fmt::color::cyan) | fg(fmt::color::black), "{:>10}", "DEBUG ");
        break;
    case LogEntry::Level::Warning:
        fmt::print(fmt::bg(fmt::color::yellow) | fg(fmt::color::black), "{:>10}", "WARNING ");
        break;
    case LogEntry::Level::Error:
        fmt::print(fmt::bg(fmt::color::orange), "{:>10}", "ERROR ");
        break;
    case LogEntry::Level::Critical:
        fmt::print(fmt::bg(fmt::color::red), "{:>10}", "CRITICAL ");
        break;
    }

    fmt::print(" {}\n", entry.message);
}

} // Si