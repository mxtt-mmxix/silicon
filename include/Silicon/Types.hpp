//
// Created by Matthew McCall on 5/27/22.
//

#ifndef SILICON_TYPES_HPP
#define SILICON_TYPES_HPP

#include <functional>
#include <list>
#include <string>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/pool/pool_alloc.hpp>

namespace Si {

template <typename T>
using Allocator = boost::pool_allocator<T>;

template <typename T>
using Ref = std::reference_wrapper<T>;

template <typename T>
using Vector = std::vector<T, Allocator<T>>;

template <typename T>
using List = std::list<T, Allocator<T>>;

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

struct GraphVector {};
struct GraphList {};

}

namespace boost
{

template <class T>
struct container_gen<Si::GraphVector, T> {
    typedef Si::Vector<T> type;
};

template <>
struct parallel_edge_traits<Si::GraphVector> {
    typedef allow_parallel_edge_tag type;
};

template <class T>
struct container_gen<Si::GraphList, T> {
    typedef Si::List<T> type;
};

template <>
struct parallel_edge_traits<Si::GraphList> {
    typedef allow_parallel_edge_tag type;
};

}

namespace Si
{

template <typename T, typename ContainerT = GraphVector>
using Graph = boost::adjacency_list<ContainerT, ContainerT, boost::bidirectionalS, T>;

}

#endif // SILICON_TYPES_HPP
