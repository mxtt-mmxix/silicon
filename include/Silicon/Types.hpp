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

#ifndef SILICON_TYPES_HPP
#define SILICON_TYPES_HPP

#include <functional>
#include <list>
#include <optional>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

#include "Allocator.hpp"
#include "Log.hpp"

namespace Si {

/**
 * Static, compile-time, assignable, copyable, movable reference that can't be null.
 */
template <typename T>
using Ref = std::reference_wrapper<T>;

/**
 * A utility which allows us to implicitly cast references to pointers for use in containers.
 *
 * This type allows us to use stack-allocated, discarded values that can be passed to functions as references be used
 * in an STL container.
 *
 * @tparam T
 */
template <typename T>
class MoveIfRVal {
public:
    MoveIfRVal(T& object)
        : xp(&object)
    {
        SI_CORE_TRACE("Pointer to lvalue");
    }

    MoveIfRVal(T&& object)
        : x(std::move(object))
        , xp(&(*x))
    {
        SI_CORE_TRACE("Moving rvalue");
    }

    operator T&()
    {
        return *xp;
    }

    operator T&() const
    {
        return *xp;
    }

private:
    std::optional<T> x = std::nullopt;
    T* xp;
};

/**
 * STL compliant data structure for contiguously storing an arbitrary amount of data.
 */
template <typename T>
using Vector = std::vector<T, Allocator<T>>;

/**
 * STL compliant data structure for storing an arbitrary amount of data.
 */
template <typename T>
using List = std::list<T, Allocator<T>>;

/**
 * Vector for use in Graphs.
 */
struct GraphVector {};

/**
 * List for use in Graphs.
 */
struct GraphList {};

}

/// @cond

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

/// @endcond

namespace Si
{

/**
 * Container for representing relationships between objects.
 */
template <typename T, typename ContainerT = GraphVector>
using Graph = boost::adjacency_list<ContainerT, ContainerT, boost::bidirectionalS, T>;

}

#endif // SILICON_TYPES_HPP
