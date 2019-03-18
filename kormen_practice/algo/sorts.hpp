//
// Created by vadim on 09.12.18.
//

#pragma once

#include <vector>
#include <iostream>

template <typename T>
void bubble_sort(std::vector<T> &vec)
{
    for(typename std::vector<T>::iterator it1 = vec.begin(); it1 <= std::prev(vec.end()); it1++)
    {
        for(typename std::vector<T>::iterator it2 = std::prev(vec.end()); it2 >= std::next(it1); it2--)
            if(*it2 < *it1)
                std::swap(*it1, *it2);/*
        std::cout << "[";
        for( auto & elem : vec )
            std::cout << elem << " ";
        std::cout << "\b]\n";*/
    }
}

template <typename T>
void insertion_sort(std::vector<T> &vec)
{
    for(typename std::vector<T>::iterator it1 = vec.begin() + 1; it1 != vec.end(); it1++)
    {
        T elem = *it1;
        typename std::vector<T>::iterator it2 = it1 - 1;
        while(it2 >= vec.begin() && elem < *it2)
        {
            *(it2 + 1) = *it2;
            it2--;
        }
        *(it2+1) = elem;
    }
}

template <typename T>
void selection_sort(std::vector<T> &vec)
{
    for(typename std::vector<T>::iterator it1 = vec.begin(); it1 != vec.end() - 1; it1++)
    {
        typename std::vector<T>::iterator min_pos = it1;
        for (typename std::vector<T>::iterator it2 = it1 + 1; it2 != vec.end(); it2++)
            if(*it2 < *min_pos) min_pos = it2;
        std::swap(*it1, *min_pos);
    }
}

template<typename T>
class merge_sorter
{
    using TVec = typename std::vector<T>;
    using Iter = typename TVec::iterator;

    void merge_step(Iter l, Iter r)
    {
        auto l_r_distance = std::distance(l, r);
        if(l_r_distance >= 2)
        {
            Iter mid = l + (l_r_distance + 1)/2;
            merge_step(l, mid);
            merge_step(mid, r);
            merge(l, mid, r);
        }
    }

    void enchanted_merge_step(TVec & vec, Iter l, Iter r)
    {
        auto l_r_distance = std::distance(l,r);
        if(l_r_distance < merge_barier)
            for(typename std::vector<T>::iterator it1 = l + 1; it1 != r; it1++)
            {
                T elem = *it1;
                typename std::vector<T>::iterator it2 = it1 - 1;
                while(it2 >= vec.begin() && elem < *it2)
                {
                    *(it2 + 1) = *it2;
                    it2--;
                }
                *(it2+1) = elem;
            }
        else
        {
            Iter mid = l + (l_r_distance + 1)/2;
            merge_step(l, mid);
            merge_step(mid, r);
            merge(l, mid, r);
        }
    }

    void merge(Iter l, Iter mid, Iter r)
    {
        std::vector<T> L, R;
        L.insert(L.begin(), l, mid);
        R.insert(R.begin(), mid, r);
        typename std::vector<T>::iterator it = l, it1 = L.begin(), it2 = R.begin();
        for(; it1 != L.end() && it2 != R.end(); it++)
        {
            if(*it1 <= *it2)
            {
                *it = *it1;
                it1++;
            }
            else
            {
                *it = *it2;
                it2++;
            }
        }
        if(it1 < L.end())
            for(; it1 < L.end(); it1++, it++)
                *it = *it1;
        else
            for(; it2 < R.end(); it2++, it++)
                *it = *it2;
        /*
        std::cout << "p = " << std::distance(vec.begin(), l)   << ", "
                  << "q = " << std::distance(vec.begin(), mid) << ", "
                  << "r = " << std::distance(vec.begin(), r)   << ", A = {";
        std::for_each(l, r - 1, [](const T &el) { std::cout << el << ", "; });
        std::cout << *(r-1) << "}" << std::endl;
        */
    }

    std::size_t merge_barier;

public:
    merge_sorter(): merge_barier(30) {}

    merge_sorter(std::size_t barier): merge_barier( barier ) {}

    void merge_sort(TVec &vec)
    {
        merge_step(vec.begin(), vec.end());
    }

    void enchanted_merge_sort(TVec &vec)
    {
        enchanted_merge_step(vec, vec.begin(), vec.end());
    }
};
