//
// Created by Matthew McCall on 5/27/22.
//

#include <cstdlib>

#include "Silicon/Log.hpp"
#include "Silicon/Node.hpp"

class CustomNode : public Si::Node
{
public:
    CustomNode(const char* message, std::initializer_list<Si::Node*> nodes = {}) : Si::Node(nodes) {
        SI_INFO(message);
    }
};

int main(int argc, char** argv)
{
    CustomNode root {
        "Node A",
        {
            new CustomNode {
                "Node B"
            }
        }
    };

    return EXIT_SUCCESS;
}