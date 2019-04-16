//
// Created by vadim on 11.02.19.
//

#pragma once

#include <tuple>
#include <vector>
#include <limits>
#include <functional>
#include <cmath>
#include <map>
#include "abstract_sorter.hpp"

//TODO: debug optimized and hoare partitions - some problem with algorithm
enum class separator_type { REGULAR , OPTIMIZED, HOARE };

template<typename T>
class quick_sorter: public abstract_sorter<T>
{
private:
//public:

    using sort_iter = typename std::vector<T>::iterator;
    using comparator = std::function<bool(T &, T &)>;
    comparator obj_comparator;
    separator_type sep;
    sort_iter vector_begin;

    /*
    Iter optimized_partition(Iter left, Iter right, std::vector<T> & vec)
    {
        bool all_elements_same = true;
        T & base_elem = *right;
        Iter i = std::prev(left);
        for(auto j = left; j < right; j++)
        {
            if(*j != base_elem)
                all_elements_same = false;
            if(obj_comparator(*j, base_elem))
            {
                i = std::next(i);
                std::swap(*i, *j);
            }
        }
        Iter new_base = std::next(i);
        std::swap(*new_base, *right);
        std::cout << "when same " << std::distance(vec.begin(), left) << "--" << std::distance(vec.begin(), right)
                  << "--" << std::floor((std::distance(vec.begin(), left) + std::distance(vec.begin(), right))/2.0) << '\n';
        return all_elements_same ? std::next(vec.begin(), std::floor((std::distance(vec.begin(), left) + std::distance(vec.begin(), right))/2.0)) : new_base;
        //return new_base;
    }
    */

    sort_iter partition(sort_iter left, sort_iter right)
    {
        T & base_elem = *right;
        sort_iter i = std::prev(left);
        for(auto j = left; j < right; j++)
        {
            if(obj_comparator(*j, base_elem))
            {
                i = std::next(i);
                std::swap(*i, *j);
            }
        }
        sort_iter new_base = std::next(i);
        std::swap(*new_base, *right);
        return new_base;
    }

    sort_iter optimized_partition(sort_iter left, sort_iter right)
    {
        bool all_elements_same = true;
        T & base_elem = *right;
        sort_iter i = std::prev(left);
        for(auto j = left; j < right; j++)
        {
            if(*j != base_elem)
                all_elements_same = false;
            if(obj_comparator(*j, base_elem))
            {
                i = std::next(i);
                std::swap(*i, *j);
            }
        }
        sort_iter new_base = std::next(i);
        std::swap(*new_base, *right);
        return all_elements_same ? compute_middle(left, right) : new_base;
    }

    sort_iter hoare_partition(sort_iter left, sort_iter right)
    {
        T & base_elem = *left;
        sort_iter i = std::prev(left);
        sort_iter j = std::next(right);
        while(true)
        {
            do
            {
                j = std::prev(j);
                std::cout << "j-dist: " << std::distance(vector_begin, j) << ", j-val: " << *j << ", base_elem: " << base_elem << '\n';
            }
            while(*j < base_elem);
            do
            {
                i = std::next(i);
                std::cout << "i-dist: " << std::distance(vector_begin, i) << ", i-val: " << *i << ", base_elem: " << base_elem << '\n';
            }
            while(*i > base_elem);
            if(i >= j)
                return j;
            std::swap(*i, *j);
        }
    }

    void quick_sort_step(sort_iter left, sort_iter right)
    {
        if(left < right)
        {
            sort_iter base;
            switch(sep)
            {
                //TODO: uncomment when fixed
                case separator_type::HOARE:
                {
                    //base = hoare_partition(left, right);
                    //break;
                }
                case separator_type::OPTIMIZED:
                {
                    //base = optimized_partition(left, right);
                    //break;
                }
                default:
                {
                    base = partition(left, right);
                    break;
                }
            }
            quick_sort_step(left, std::prev(base));
            quick_sort_step(base, right);
        }
    }

public:

    quick_sorter(): sep(separator_type::REGULAR)
    {
        // Sort ascending
        obj_comparator = [](T & left_val, T & right_val) {return left_val <= right_val;};
    }

    quick_sorter(comparator other): sep(separator_type::REGULAR), obj_comparator(other){}

    quick_sorter(separator_type sep_): sep(sep_)
    {
        // Sort ascending
        obj_comparator = [](T & left_val, T & right_val) {return left_val <= right_val;};
    }

    quick_sorter(comparator other, separator_type sep_): obj_comparator(other), sep(sep_){}

    void sort(std::vector<T> & vec)
    {
        this->vbegin = vec.begin();
        quick_sort_step(vec.begin(), std::prev(vec.end()));
    }

};
