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

#ifndef SILICON_NODE_HPP
#define SILICON_NODE_HPP

#include <initializer_list>

#include "Types.hpp"

namespace Si {

/**
 * A Node is the building block of your game.
 *
 * Nodes allow you to define your application declaratively. Nodes can be attached to other nodes to form a node tree.
 * While Nodes are designed to be created and attached declaratively, they can created and attached imperatively as
 * well. You may inherit the nodes to provide your own functionality. All Nodes can be attached to another
 * declaratively, but not every Node needs or should allow child Nodes to be attached declaratively.
 */
class Node {
public:
    using Graph = Si::Graph<Node*, GraphList>;

    Node(std::initializer_list<Node*>);

    virtual bool OnAttach();
    virtual void OnTick(float deltaTime);
    virtual void OnDetach();

    virtual ~Node();

private:
    Node::Graph::vertex_descriptor m_descriptor;
};

} // Si

#endif // SILICON_NODE_HPP
