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

#include <algorithm>

#include "Silicon/Node.hpp"

namespace {

Si::NodeContainer::Graph s_graph;

}

namespace Si {

bool Node::OnAttach()
{
    return false;
}

void Node::OnTick(float deltaTime)
{
}

void Node::OnDetach()
{
}

NodeContainer::NodeContainer(std::unique_ptr<Node>&& ptr, std::initializer_list<NodeContainer> nodes)
{
    m_descriptor = boost::add_vertex(s_graph);
    s_graph[m_descriptor] = std::move(ptr);

    for (const NodeContainer& node: nodes) {
        boost::add_edge(m_descriptor, node.m_descriptor, s_graph);
        s_graph[node.m_descriptor]->OnAttach();
    }
}

NodeContainer::NodeContainer(NodeContainer&& other) noexcept
    : m_descriptor(other.m_descriptor)
{
}

Node* NodeContainer::operator->()
{
    return s_graph[m_descriptor].get();
}

} // Si