//
// Created by vadim on 08.04.19.
//

#pragma once

#include <vector>
#include <cmath>

template<typename T>
class abstract_sorter
{
protected:
    using TVec = typename std::vector<T>;
    using Iter = typename TVec::iterator;
public:
    virtual void sort(TVec & vec) = 0;
protected:
    Iter vbegin;
    Iter compute_middle(Iter left, Iter right)
    {
        double l_dist = std::distance(vbegin, left);
        double r_dist = std::distance(vbegin, right);
        std::size_t m_dist = std::floor((l_dist + r_dist)/2.0);
        return vbegin + m_dist;
    }
};
