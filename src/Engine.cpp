//
// Created by Matthew McCall on 5/27/22.
//

#include <Silicon/Engine.hpp>

namespace {

bool s_initialized;

}

namespace Si::Engine {

bool Initialize()
{
    if (s_initialized)
        return true;

    return s_initialized = true;
}

void Run()
{

}

void DeInitialize()
{
    if (!s_initialized)
        return;



    s_initialized = false;
}

}