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

#include <boost/current_function.hpp>

#include "Silicon/Log.hpp"
#include "Silicon/Node.hpp"

namespace {

Si::Node::Graph s_graph;

}

namespace Si {

Node::Node()
{
    m_descriptor = boost::add_vertex(s_graph);
    s_graph[m_descriptor] = this;
}

Node::Node(Node* parent)
{
    assert(parent != nullptr);

    m_descriptor = boost::add_vertex(s_graph);
    s_graph[m_descriptor] = this;

    parent->AddChild(this);
}

void Node::AddChild(Node* node)
{
    assert(node != nullptr);
    boost::add_edge(m_descriptor, node->m_descriptor, s_graph);
}

void Node::AddChild(Node& node)
{
    boost::add_edge(m_descriptor, node.m_descriptor, s_graph);
}

bool Node::Attach()
{
    String AttachFailError;

    auto [parentBegin, parentEnd] = boost::in_edges(m_descriptor, s_graph);
    auto [childrenBegin, childrenEnd] = boost::adjacent_vertices(m_descriptor, s_graph);

    if (!this->OnAttach()) {
        AttachFailError = "this->OnAttach() failed!";
        goto NodeAttachFail;
    }

    for (auto i = childrenBegin; i != childrenEnd; ++i) {
        if (!s_graph[*i]->Attach()) {
            AttachFailError = "Child Node::OnAttach() failed!";
            goto NodeAttachFail;
        }
    }

    return true;

NodeAttachFail:
    SI_CORE_ERROR("{} failed: {}", BOOST_CURRENT_FUNCTION,  AttachFailError);
    return false;
}

bool Node::OnAttach()
{
    return false;
}

void Node::OnTick(float deltaTime)
{
}

void Node::Detach()
{
    auto [childrenBegin, childrenEnd] = boost::adjacent_vertices(m_descriptor, s_graph);

    for (auto i = childrenBegin; i != childrenEnd; ++i) {
        s_graph[*i]->Detach();
    }

    this->OnDetach();
}

void Node::OnDetach()
{
}

bool Node::IsAncestor(Node& ancestor)
{
    if (m_descriptor == ancestor.m_descriptor) return true;

    auto [begin, end] = boost::inv_adjacent_vertices(ancestor.m_descriptor, s_graph);

    for (auto i = begin; i != end; ++i) {
        if (s_graph[*i]->IsAncestor(ancestor)) return true;
    }

    return false;
}

} // Si