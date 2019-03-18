//
// Created by vadim on 08.01.19.
//

#pragma once

#include <cstdint>

struct binary_node
{
    std::uint64_t key;
    binary_node * parent;
    binary_node * left;
    binary_node * right;
};

struct binary_tree
{
    binary_node * root;

    void add_node(std::uint64_t key_, bool left)
    {

    }
};