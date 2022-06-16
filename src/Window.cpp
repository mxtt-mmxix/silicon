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

#include <SDL2/SDL_video.h>

#include "Silicon/Window.hpp"
#include "Silicon/Log.hpp"

namespace Si {

Window::Window(const String& name, std::uint32_t width, std::uint32_t height)
{
    Open(name, width, height);
}

bool Window::Open(const String& name, std::uint32_t width, uint32_t height)
{
    SDL_Window* window = SDL_GetWindowFromID(m_id);

    if (window != nullptr) {
        SI_CORE_ERROR("{}: Failed to open window: Window already created!", BOOST_CURRENT_FUNCTION);
        return false;
    }

    std::uint32_t flags = SDL_WINDOW_ALLOW_HIGHDPI;

    if constexpr (Si::PLATFORM_NAME == "Darwin") {
        flags |= SDL_WINDOW_METAL;
    }

    window = SDL_CreateWindow(
        name.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        static_cast<int>(width),
        static_cast<int>(height),
        flags);

    if (window == nullptr) {
        SI_CORE_ERROR("{}: Failed to open window: {}", BOOST_CURRENT_FUNCTION, SDL_GetError());
        return false;
    }

    m_id = SDL_GetWindowID(window);

    return true;
}

void Window::Close()
{
    SDL_Window* window = SDL_GetWindowFromID(m_id);
    if (window != nullptr) SDL_DestroyWindow(window);
}

Window::~Window()
{
    Close();
}

uint32_t Window::getID() const
{
    return m_id;
}

} // Si