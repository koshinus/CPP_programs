//
// Created by vadim on 09.12.18.
//

#include <vector>
#include <iostream>
#include "tests.hpp"
#include "searches.hpp"
#include "sorts.hpp"
#include "chapter-4-1.hpp"
#include "support.hpp"
#include "chapter-7.hpp"

void bubble_sort_test()
{
    std::cout << "[BUBBLE SORT]...start\n";
    std::vector<int> vec{8, 2, 3, 4, 1, 3, 1};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    bubble_sort<int>(vec);
    std::cout << "Sorted array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    std::cout << "[BUBBLE SORT].....end\n";
}

void insertion_sort_test()
{
    std::cout << "[INSERTION SORT]...start\n";
    std::vector<int> vec{1, 2, 3, 4, 8, 3, 1};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    insertion_sort<int>(vec);
    std::cout << "Sorted array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    std::cout << "[INSERTION SORT].....end\n";
}

void selection_sort_test()
{
    std::cout << "[SELECTION SORT]...start\n";
    std::vector<int> vec{1, 2, 3, 4, 8, 3, 1};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    selection_sort<int>(vec);
    std::cout << "Sorted array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    std::cout << "[SELECTION SORT].....end\n";
}

void merge_sort_test()
{
    std::cout << "[MERGE SORT]...start\n";
    std::vector<int> vec{1, 2, 3, 4, 8, 3, 1};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    merge_sorter<int> sorter;
    sorter.merge_sort(vec);
    std::cout << "Sorted array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    std::cout << "[MERGE SORT].....end\n";
}

/*
void partition_test()
{
    std::cout << "[PARTITION]...start\n";
    std::vector<int> vec{1, 1, 1, 1, 1, 1, 1};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    quick_sorter<int> sorter;
    auto it = sorter.partition(vec.begin(), std::prev(vec.end()));
    std::cout << "Partition for vec with the same values " << std::distance(vec.begin(), it) << '\n';
    std::cout << "Distance between begin and end " << std::distance(vec.begin(), vec.end()) << '\n';
    std::cout << "[PARTITION].....end\n";
}
//*/

void quick_sort_test()
{
    std::cout << "[QUICK SORT]...start\n";
    std::vector<int> vec{1, 2, 3, 4, 8, 3, 1};
    //std::vector<int> vec{1, 1, 1, 1, 1, 1, 1};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    quick_sorter<int> sorter;
    //quick_sorter<int> sorter([](int & left_val, int & right_val){return left_val >= right_val;});
    sorter.quick_sort(vec);
    std::cout << "Sorted array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    std::cout << "[QUICK SORT].....end\n";
}

void enchanted_merge_sort_test(int sorted_size)
{
    std::cout << "[ENCHANTED MERGE SORT]...start\n";
    std::vector<int> vec{1, 2, 3, 4, 8, 3, 1};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    merge_sorter<int> sorter(sorted_size);
    sorter.enchanted_merge_sort(vec);
    std::cout << "Sorted array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    std::cout << "[ENCHANTED MERGE SORT].....end\n";
}

void linear_search_test()
{
    std::cout << "[LINEAR SEARCH]...start\n";
    std::vector<int> vec{1, 2, 3, 4, 8, 3, 1};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    std::vector<int>::iterator it = linear_search<int>(vec, 3);
    std::cout << "Search element " << 3
              << " it's first appearance in array at position "
              << std::distance(vec.begin(), it) << "\n";
    it = linear_search<int>(vec, 5);
    std::cout << "Search element " << 5;
    if (it == vec.end())
        std::cout << " it is not exist in this container\n";
    else
        std::cout << " it is first appearance in array at position "
                  << std::distance(vec.begin(), it) << "\n";
    std::cout << "[LINEAR SEARCH].....end\n";
}

void binary_search_test()
{
    std::cout << "[BINARY SEARCH]...start\n";
    std::vector<int> vec{1, 1, 2, 3, 3, 4, 8};
    std::cout << "Given array: [";
    for (int elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    std::vector<int>::iterator it = binary_search<int>(vec, 3);
    std::cout << "Search element " << 3
              << " it's first appearance in array at position "
              << std::distance(vec.begin(), it) << "\n";
    it = binary_search<int>(vec, 5);
    std::cout << "Search element " << 5;
    if (it == vec.end())
        std::cout << " it is not exist in this container\n";
    else
        std::cout << " it is first appearance in array at position "
                  << std::distance(vec.begin(), it) << "\n";
    std::cout << "[BINARY SEARCH].....end\n" << std::endl;
}


void max_subarray_search_test()
{
    std::cout << "[MAX SUBARRAY SEARCH]...start\n";
    //std::vector<int64_t> vec{1, 2, 3, 4, 8, 3, 1};
    //std::vector<int64_t> vec{100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97};
    //std::vector<int64_t> vec{-2,-4,-9,-8};
    // Wrong left bound for recursive algorithm
    std::vector<int64_t> vec{98, 73, 114, 110, 80, 97, 73, 127, 118, 93};
    //std::vector<int64_t> vec = generate_random_array(10);
    std::cout << "Given array: [";
    for (int64_t elem : vec)
        std::cout << elem << " ";
    std::cout << "\b]\n";
    max_subarray_searcher searcher(30);
    auto tup = searcher.find_max_subarray_brute_force(vec);
    std::cout << "Brute force: "
              << std::distance(vec.begin(), std::get<0>(tup)) << ' '
              << std::distance(vec.begin(), std::get<1>(tup)) << ' '
              << std::get<2>(tup) << '\n';
    tup = searcher.find_max_subarray_recursively(vec);
    std::cout << "Recursive: "
              << std::distance(vec.begin(), std::get<0>(tup)) << ' '
              << std::distance(vec.begin(), std::get<1>(tup)) << ' '
              << std::get<2>(tup) << '\n';

    tup = searcher.find_max_subarray_recursively_enchanted(vec);
    std::cout << "Enchanted recursive: "
              << std::distance(vec.begin(), std::get<0>(tup)) << ' '
              << std::distance(vec.begin(), std::get<1>(tup)) << ' '
              << std::get<2>(tup) << '\n';
    /*
    auto tup1 = searcher.fmsr(vec);
    std::cout << std::get<0>(tup1) << ' '
              << std::get<1>(tup1) << ' '
              << std::get<2>(tup1) << '\n';*/
    tup = searcher.kadane_max_subarray_search(vec);
    std::cout << "Kadane's: "
              << std::distance(vec.begin(), std::get<0>(tup)) << ' '
              << std::distance(vec.begin(), std::get<1>(tup)) << ' '
              << std::get<2>(tup) << '\n';
    std::cout << "[MAX SUBARRAY SEARCH].....end\n";
}
