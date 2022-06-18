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

#ifndef SILICON_ENGINE_HPP
#define SILICON_ENGINE_HPP

#include <cstdint>

/**
 * Contains the necessary functions to initialize, run, and shutdown the engine.
 */
namespace Si::Engine {

enum : std::uint32_t {
    LOOP_CONTINUE = 0, /**< The loop should continue running. */
    LOOP_USER_QUIT, /**< The user requested a quit, i.e window close. */
    LOOP_ENGINE_NOT_INITIALIZED, /**< The engine was not initialized. */
    LOOP_ALREADY_RUNNING, /**< Engine::Loop() is being called elsewhere. */
    LOOP_UNKNOWN_ERROR /**< Some other error occurred. */
};

/**
 * Initializes the engine. This is necessary everything besides logging and containers.
 * @return true if the engine initializes successfully.
 */
bool Initialize();

/**
 * Runs the loop once; If you do need control of the main loop, please see Engine::Run().
 * @param outLoopReturn A pointer to a std::uint32_t to store the exit code. For Emscripten builds, control is passed to the
 * browser with no way to return a value, thus an out variable is used. 0 indicates the loop should continue running while a
 * non-zero exit code indicates a user quit event (i.e. window closed), or an error. See SI_ENGINE_LOOP_* enums for details.
 */
void Loop(void* outLoopReturn = nullptr);

/**
 * Enters the main loop and does not return until the Engine is ready to shutdown.
 */
void Run();

/**
 * Shuts down the engine. Containers and logging will continue to work.
 */
void DeInitialize();

}

#endif // SILICON_ENGINE_HPP
