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

//
// Created by Matthew McCall on 5/27/22.
//

#include <cstdlib>

#include "Silicon/Log.hpp"
#include "Silicon/Node.hpp"
#include "Silicon/String.hpp"

class CustomNodeImpl : public Si::Node {
public:
    explicit CustomNodeImpl(Si::String message)
        : m_message(std::move(message))
    {
    }

    CustomNodeImpl(const CustomNodeImpl&) = delete;

    bool OnAttach() override
    {
        SI_INFO(m_message);
        return true;
    }

    ~CustomNodeImpl() {
        SI_INFO("Destroying {}", m_message);
    };

private:
    Si::String m_message;
};

SI_DECL_NODE(CustomNode, CustomNodeImpl)

int main(int argc, char** argv)
{
    CustomNode root {
        {
            CustomNode {
                {},
                "Node B"
            }
        },
        "Node A"
    };

    root->OnAttach();

    return EXIT_SUCCESS;
}