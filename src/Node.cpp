//
// Created by Matthew McCall on 5/27/22.
//

#include <algorithm>

#include "Silicon/Node.hpp"

namespace {

Si::Node::Graph s_graph;

}

namespace Si {

Node::Node(std::initializer_list<Node*> nodes)
{
    m_descriptor = boost::add_vertex(this, s_graph);

    for (Node* node: nodes)
        boost::add_edge(m_descriptor, node->m_descriptor, s_graph);
}

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

Node::~Node()
{
    auto [begin, end] = boost::adjacent_vertices(m_descriptor, s_graph);

    std::for_each(begin, end, [](Node::Graph::vertex_descriptor node) {
       delete s_graph[node];
    });

    boost::clear_vertex(m_descriptor, s_graph);
    boost::remove_vertex(m_descriptor, s_graph);
}

} // Si