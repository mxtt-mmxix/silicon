//
// Created by Matthew McCall on 5/27/22.
//

#ifndef SILICON_TYPES_HPP
#define SILICON_TYPES_HPP

#include <string>

#include <boost/pool/pool_alloc.hpp>

namespace Si {

template <typename T>
using Allocator = boost::pool_allocator<T>;

template <typename T>
using IString = std::basic_string<T, std::char_traits<T>, Allocator<T>>;

class String : public IString<char>
{
public:
    String() = default;
    String(std::string&& other);
};

using WideString = IString<wchar_t>;
using U8String = IString<char8_t>;
using U16String = IString<char16_t>;
using U32String = IString<char32_t>;

}

#endif // SILICON_TYPES_HPP
