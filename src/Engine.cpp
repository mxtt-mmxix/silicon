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

#include <mutex>

#ifdef BUILD_EMSCRIPTEN
#include <emscripten.h>
#endif

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <Silicon/Engine.hpp>
#include <Silicon/Log.hpp>
#include <Silicon/Window.hpp>

namespace {

constexpr std::uint32_t SUBSYSTEM_MASK = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

std::mutex s_loopMutex;

SDL_Event s_event;
Si::Window s_applicationWindow;

}

namespace Si::Engine {

bool Initialize()
{
    if (SDL_WasInit(SUBSYSTEM_MASK) == SUBSYSTEM_MASK) {
        SI_CORE_WARN("{}: Engine already initialized!", BOOST_CURRENT_FUNCTION);
        return true;
    }

    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SI_CORE_CRITICAL("Failed to initialize SDL: {}", SDL_GetError());
        return false;
    }

    s_applicationWindow.Open("Si Engine");

    int windowWidth = 800, windowHeight = 600;
    SDL_Window* window = SDL_GetWindowFromID(s_applicationWindow.getID());

    SDL_GL_GetDrawableSize(window, &windowWidth, &windowHeight);

    if (!windowWidth || !windowHeight) {
        SI_CORE_ERROR("Failed to get window size!");
    }

    bgfx::PlatformData bgfxPD;

    SDL_SysWMinfo info;
    SDL_VERSION(&info.version)

    if (window == nullptr) {
        SI_CORE_ERROR("Failed to get window!: {}", SDL_GetError());
        return false;
    }

#ifdef SI_PLATFORM_EMSCRIPTEN
    bgfxPD.nwh = (void*)"#canvas";
#else
    if (!SDL_GetWindowWMInfo(window, &info)) {
        SI_CORE_ERROR("Failed to get window manager information: {}", SDL_GetError());
        return false;
    }

#ifdef SI_PLATFROM_APPLE
    bgfxPD.nwh = info.info.cocoa.window;
#endif

    bgfx::renderFrame();
#endif

    bgfx::setPlatformData(bgfxPD);

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count;
    bgfxInit.resolution.width = windowWidth;
    bgfxInit.resolution.height = windowHeight;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

    bgfx::init(bgfxInit);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xff0000ff, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, windowWidth, windowHeight);

    SI_CORE_INFO("{}: Welcome to Silicon Engine!", BOOST_CURRENT_FUNCTION);

    return true;
}

void Loop(void* outLoopReturn)
{
    std::uint32_t nullParameter;
    auto* outLoopReturnInt = static_cast<uint32_t*>(outLoopReturn);

    if (outLoopReturn == nullptr) outLoopReturnInt = &nullParameter;

    if (SDL_WasInit(SUBSYSTEM_MASK) != SUBSYSTEM_MASK) {
        SI_CORE_ERROR("{}: Engine was not initialized!", BOOST_CURRENT_FUNCTION);
        *outLoopReturnInt = LOOP_ENGINE_NOT_INITIALIZED;
        return ;
    }

    std::unique_lock lock { s_loopMutex, std::defer_lock };

    if (!lock.try_lock()) {
        SI_CORE_ERROR("{}: Failed to take control of loop! Please do not call this if Engine::Run() is running.", BOOST_CURRENT_FUNCTION);
        *outLoopReturnInt = LOOP_ALREADY_RUNNING;
        return ;
    }

    while (SDL_PollEvent(&s_event)) {
        if (s_event.type == SDL_QUIT) {
            *outLoopReturnInt = LOOP_USER_QUIT;

#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return ;
        }
    }

    bgfx::touch(0);
    bgfx::frame();

    *outLoopReturnInt = LOOP_CONTINUE;
}

void Run()
{
    std::uint32_t loopReturn = 0;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(Loop, &loopReturn, 0, true);
    return;
#endif

    while (!loopReturn)
        Loop(&loopReturn);
}

void DeInitialize()
{
    if (SDL_WasInit(SUBSYSTEM_MASK) == SUBSYSTEM_MASK) {
        SDL_Quit();

        SI_CORE_INFO("{}: Silicon Engine Shutdown.", BOOST_CURRENT_FUNCTION);
        return;
    }

    SI_CORE_WARN("{}: Engine was not initialized!", BOOST_CURRENT_FUNCTION);
}

}