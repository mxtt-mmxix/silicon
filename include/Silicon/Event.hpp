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

#ifndef SILICON_EVENT_HPP
#define SILICON_EVENT_HPP

#include "SDL2/SDL_events.h"

#include <functional>

#include "Types.hpp"

namespace Si {

namespace Event {

    struct AppQuit { };

    struct Window {
        Window(SDL_WindowEvent);
        std::uint32_t windowID;
    };

    struct WindowClose : public Window {
        WindowClose(SDL_WindowEvent);
    };
    struct WindowResize : public Window {
        WindowResize(SDL_WindowEvent);
        std::uint32_t width, height;
    };
    struct WindowMove : public Window {
        WindowMove(SDL_WindowEvent);
        std::uint32_t x, y;
    };

}

template <typename T>
class Sub {

    friend void Pub(const T& data);
    using Callback = std::function<void(const T&)>;

public:
    explicit Sub(Callback func)
        : Func(func)
    {
        Sub<T>::Subscribers.push_back(this);
    }

    ~Sub()
    {
        const auto& i = std::find_if(Sub<T>::Subscribers.begin(), Sub<T>::Subscribers.end(), [this](Sub<T>* sub) {
            return this == sub;
        });

        if (i != Sub<T>::Subscribers.end())
            Sub<T>::Subscribers.erase(i);
    }

    static std::vector<Sub<T>*> Subscribers;
    const Callback& Func;
};

template <class T>
void Pub(const T& data)
{
    for (Sub<T>* i : Sub<T>::Subscribers) {
        i->Func(data);
    }
}

template <typename T>
std::vector<Sub<T>*> Sub<T>::Subscribers {};

}

#endif // SILICON_EVENT_HPP
