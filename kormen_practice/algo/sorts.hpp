//
// Created by vadim on 09.12.18.
//

#pragma once

#include "abstract_sorter.hpp"
#include <iostream>

template <typename T> class bubble_sorter: public abstract_sorter<T>
{
protected:
    using TVec = typename abstract_sorter<T>::TVec;
    using Iter = typename abstract_sorter<T>::Iter;
public:
    bubble_sorter() = default;
    void sort(TVec & vec) override
    {
        for(Iter it1 = vec.begin(); it1 <= std::prev(vec.end()); it1++)
        {
            for(Iter it2 = std::prev(vec.end()); it2 >= std::next(it1); it2--)
                if(*it2 < *it1)
                    std::swap(*it1, *it2);/*
            std::cout << "[";
            for( auto & elem : vec )
                std::cout << elem << " ";
            std::cout << "\b]\n";*/
        }
    }
};

template <typename T> class insertion_sorter: public abstract_sorter<T>
{
protected:
    using TVec = typename abstract_sorter<T>::TVec;
    using Iter = typename abstract_sorter<T>::Iter;
public:
    insertion_sorter() = default;
    void sort(TVec & vec) override
    {
        for(Iter it1 = vec.begin() + 1; it1 != vec.end(); it1++)
        {
            T elem = *it1;
            Iter it2 = it1 - 1;
            while(it2 >= vec.begin() && elem < *it2)
            {
                *(it2 + 1) = *it2;
                it2--;
            }
            *(it2+1) = elem;
        }
    }
};

template <typename T> class selection_sorter: public abstract_sorter<T>
{
protected:
    using TVec = typename abstract_sorter<T>::TVec;
    using Iter = typename abstract_sorter<T>::Iter;
public:
    selection_sorter() = default;
    void sort(TVec & vec) override
    {
        for(Iter it1 = vec.begin(); it1 != vec.end() - 1; it1++)
        {
            Iter min_pos = it1;
            for (Iter it2 = it1 + 1; it2 != vec.end(); it2++)
                if(*it2 < *min_pos)
                    min_pos = it2;
            std::swap(*it1, *min_pos);
        }
    }
};

template<typename T> class merge_sorter: public abstract_sorter<T>
{
protected:
    using my_parent = abstract_sorter<T>;
    using TVec = typename my_parent::TVec;
    using Iter = typename my_parent::Iter;
private:
    void merge_step(Iter l, Iter r)
    {
        auto l_r_distance = std::distance(l, r);
        if(l_r_distance >= 2)
        {
            Iter mid = my_parent::compute_middle(l, r);
            merge_step(l, mid);
            merge_step(mid, r);
            merge(l, mid, r);
        }
    }

    void enchanted_merge_step(Iter l, Iter r)
    {
        auto l_r_distance = std::distance(l,r);
        if(l_r_distance < merge_barier)
            for(Iter it1 = l + 1; it1 != r; it1++)
            {
                T elem = *it1;
                Iter it2 = it1 - 1;
                while(it2 >= this->vbegin && elem < *it2)
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
        Iter it = l, it1 = L.begin(), it2 = R.begin();
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
    bool enchanted;

public:
    merge_sorter(): merge_barier(30) {}

    merge_sorter(std::size_t barier): merge_barier(barier), enchanted(false) {}

    merge_sorter(bool enchanted_): merge_barier(30), enchanted(enchanted_) {}

    merge_sorter(std::size_t barier, bool enchanted_): merge_barier(barier), enchanted(enchanted_) {}

    void sort(TVec &vec) override
    {
        this->vbegin = vec.begin();
        if(enchanted)
            enchanted_merge_step(this->vbegin, vec.end());
        else
            merge_step(this->vbegin, vec.end());
    }
};
