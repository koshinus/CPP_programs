//
// Created by vadim on 09.12.18.
//

#pragma once


#include <vector>

template <typename T>
typename std::vector<T>::iterator linear_search(std::vector<T> &vec, T elem)
{
    for(typename std::vector<T>::iterator it = vec.begin(); it < vec.end(); it++)
        if (*it == elem) return it;
    return vec.end();
}

template <typename T>
typename std::vector<T>::iterator binary_search(std::vector<T> &vec, T elem)
{
    typename std::vector<T>::iterator l = vec.begin();
    typename std::vector<T>::iterator r = vec.end();
    while (std::distance(l, r) > 0)
    {
        typename std::vector<T>::iterator mid = l + std::distance(l, r)/2;
        if(*mid == elem) return mid;
        if(*mid > elem) r = mid;
        if(*mid < elem) l = mid + 1;
    }
    return vec.end();
}