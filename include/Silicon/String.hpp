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

#ifndef SILICON_STRING_HPP
#define SILICON_STRING_HPP

#include <string>

#include "Allocator.hpp"

namespace Si {

/**
 * Template class for storing strings with a custom underlying datatype.
 */
template <typename T>
using IString = std::basic_string<T, std::char_traits<T>, Allocator<T>>;

/**
 * Stores char type strings. Compatible with std::string and const char*
 */
class String : public IString<char>
{
public:
    String() = default;
    String(std::string&& other);
    String(const char* other);

    operator std::string();
};

/**
 * Stores wide-char strings.
 */
using WideString = IString<wchar_t>;

/**
 * Stores UTF-8 strings.
 */
using U8String = IString<char8_t>;

/**
 * Stores UTF-16 strings.
 */
using U16String = IString<char16_t>;

/**
 * Stores UTF-32 strings.
 */
using U32String = IString<char32_t>;

}

#endif // SILICON_STRING_HPP
