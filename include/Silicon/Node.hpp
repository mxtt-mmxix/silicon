//
// Created by Matthew McCall on 5/27/22.
//

#ifndef SILICON_NODE_HPP
#define SILICON_NODE_HPP

#include <initializer_list>

#include "Types.hpp"

namespace Si {

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
