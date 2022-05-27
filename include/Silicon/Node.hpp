//
// Created by Matthew McCall on 5/27/22.
//

#ifndef SILICON_NODE_HPP
#define SILICON_NODE_HPP

namespace Si {

class Node {
public:
    Node() = delete;

    virtual bool OnAttach();
    virtual void OnTick(float deltaTime);
    virtual void OnDetach();

    virtual ~Node() = default;
};

} // Si

#endif // SILICON_NODE_HPP
