//
// Created by vadim on 27.12.18.
//

#pragma once

#include <random>
#include <vector>
#include <algorithm>

std::vector<int64_t> generate_random_array(size_t arr_size)
{
    std::vector<int64_t> random_array(arr_size);

    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    std::normal_distribution<> dist {100, 30};

    auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

    std::generate(std::begin(random_array), std::end(random_array), gen);

    return random_array;
}