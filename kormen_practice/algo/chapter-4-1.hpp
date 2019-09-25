//
// Created by vadim on 24.12.18.
//

#pragma once

#include <tuple>
#include <vector>
#include <limits>
#include <functional>

class max_subarray_searcher
{
private:

    template <typename T>
    using Iter = typename std::vector<T>::iterator;
    using Iter64 = Iter<std::int64_t>;
    using RetTripleType = std::tuple<Iter64, Iter64, std::int64_t>;

    int64_t threshold;

    std::vector<int64_t> array_preprocessing(const std::vector<int64_t> & vec)
    {
        std::vector<int64_t> preprocessed(vec.size() - 1, 0);
        for(size_t i = 0; i < vec.size() - 1; i++)
            preprocessed[i] = vec[i+1] - vec[i];
        /*
        std::cout << "Preprocessed array: [";
        for (auto elem : preprocessed)
            std::cout << elem << ' ';
        std::cout << "\b]\n";
        */
        return preprocessed;
    }

public:

    max_subarray_searcher()
    {
        std::numeric_limits<int64_t> limits;
        threshold = limits.max();
    }

    max_subarray_searcher(int64_t threshold_): threshold(threshold_) {}

    RetTripleType find_max_subarray_brute_force(std::vector<int64_t> & vec)
    {
        std::numeric_limits<int64_t> i64_limits;
        RetTripleType result = std::make_tuple(vec.begin(), vec.begin(), i64_limits.min());
        for(Iter64 iter1 = vec.begin(); iter1 < vec.end(); iter1++)
            for(Iter64 iter2 = std::next(iter1); iter2 < vec.end(); iter2++)
            {
                if(std::get<2>(result) < *iter2 - *iter1)
                {
                    std::get<0>(result) = iter1;
                    std::get<1>(result) = iter2;
                    std::get<2>(result) = *iter2 - *iter1;
                }
            }
        return result;
    }

    // TODO: recursive and Kadane's algorithms work with preprocessed array and returns bounds
    // TODO: for this array, not for original.
    RetTripleType find_max_subarray_recursively(std::vector<int64_t> & vec)
    {
        std::vector<int64_t> preprocessed_array = array_preprocessing(vec);
        auto tup = find_max_subarray_recursively_subroutine(preprocessed_array.begin(),
                                                            std::prev(preprocessed_array.end()));
        return std::make_tuple
                (
                    std::next(vec.begin(), std::distance(preprocessed_array.begin(), std::get<0>(tup))),
                    // Repair original array bounds
                    std::next(vec.begin(), std::distance(preprocessed_array.begin(), std::get<1>(tup)) + 1),
                    std::get<2>(tup)
                );
        /*
        Iter64 left  = std::get<0>(tup);
        Iter64 right = std::get<1>(tup);

        std::cout << "Preprocessed: " << std::distance(preprocessed_array.begin(), left)  << ' '
                                      << std::distance(preprocessed_array.begin(), right) << ' '
                                      << std::get<2>(tup) << '\n';
        return std::make_tuple
            (
                // We form preprocessed array as A[i+1]-A[i], so the right side
                // in the original array is moved left on one position
                std::next(vec.begin(), std::distance(preprocessed_array.begin(), left)),
                std::next(vec.begin(), std::distance(preprocessed_array.begin(), right)),
                std::get<2>(tup)
            );*/
    }

    RetTripleType find_max_subarray_recursively_subroutine(Iter64 low, Iter64 high)
    {
        if (low == high)
            return std::make_tuple(low, high, *high);

        Iter64 mid = std::next(low, std::distance(low, high)/2);

        RetTripleType left_tup = find_max_subarray_recursively_subroutine(low, mid);
        RetTripleType right_tup = find_max_subarray_recursively_subroutine(std::next(mid), high);
        RetTripleType crossed_tup = find_max_crossing_subarray(low, mid, high);
        if (std::get<2>(left_tup) >= std::get<2>(right_tup) && std::get<2>(left_tup) >= std::get<2>(crossed_tup))
            return left_tup;
        else if (std::get<2>(right_tup) >= std::get<2>(left_tup) && std::get<2>(right_tup) >= std::get<2>(crossed_tup))
            return right_tup;
        else
            return crossed_tup;
    }

    RetTripleType find_max_crossing_subarray(Iter64 low, Iter64 mid, Iter64 high)
    {
        std::numeric_limits<int64_t> i64_limits;
        int64_t left_sum = i64_limits.min(), right_sum = i64_limits.min(), sum = 0;
        Iter64 min_left, max_right;
        for(Iter64 it = mid; it > std::prev(low); it--)
        {
            sum += *it;
            if(sum > left_sum)
            {
                left_sum = sum;
                min_left = it;
            }
        }
        sum = 0;
        for(Iter64 it = std::next(mid); it < std::next(high); it++)
        {
            sum += *it;
            if(sum > right_sum)
            {
                right_sum = sum;
                max_right = it;
            }
        }
        return std::make_tuple(min_left, max_right, right_sum + left_sum);
    }

    RetTripleType find_max_subarray_recursively_enchanted(std::vector<int64_t> & vec)
    {
        if (vec.size() <= threshold)
            return find_max_subarray_brute_force(vec);

        std::vector<int64_t> preprocessed_array = array_preprocessing(vec);
        auto tup = find_max_subarray_recursively_subroutine(preprocessed_array.begin(),
                                                            std::prev(preprocessed_array.end()));
        return std::make_tuple
                (
                    std::next(vec.begin(), std::distance(preprocessed_array.begin(), std::get<0>(tup))),
                    std::next(vec.begin(), std::distance(preprocessed_array.begin(), std::get<1>(tup)) + 1),
                    std::get<2>(tup)
                );
    }
    /*
    RetTripleType kadane_max_subarray_search(std::vector<int64_t> & original)
    {
        if(original.empty())
            return std::make_tuple(Iter64(), Iter64(), 0);

        std::vector<std::int64_t> vec = array_preprocessing(original);
        // Triples are represent segments of array: best and current.
        // First element is the start, second is the end, third is the sum of segment elements.
        RetTripleType cur = std::make_tuple(vec.begin(), vec.begin(), 0),
                      best = std::make_tuple(vec.begin(), vec.begin(), 0);
        auto get_segment_start = [](RetTripleType & triple) -> Iter64 & {return std::get<0>(triple);};
        auto get_segment_end = [](RetTripleType & triple) -> Iter64 & {return std::get<1>(triple);};
        auto get_segment_sum = [](RetTripleType & triple) -> std::int64_t & {return std::get<2>(triple);};
        for(Iter64 i = vec.begin(); i < vec.end(); i++, get_segment_end(cur)++)
        {
            if(get_segment_sum(cur) <= 0)
            {
                get_segment_start(cur) = get_segment_end(cur);
                get_segment_sum(cur) = *i;
            }
            else
                get_segment_sum(cur) += *i;
            if(get_segment_sum(cur) > get_segment_sum(best))
            {
                get_segment_sum(best) = get_segment_sum(cur);
                get_segment_start(best) = get_segment_start(cur);
                get_segment_end(best) = get_segment_end(cur) + 1;
            }
        }
        return std::make_tuple
                (
                    std::next(original.begin(), std::distance(vec.begin(), get_segment_start(best))),
                    std::next(original.begin(), std::distance(vec.begin(), get_segment_end(best))),
                    get_segment_sum(best)
                );
    }
    */
    // This version have O(1) extra space in comprasion with one above
    RetTripleType kadane_max_subarray_search(std::vector<int64_t> & original)
    {
        if(original.empty())
            return std::make_tuple(Iter64(), Iter64(), 0);
        else if(original.size() < 2)
            return original[0] < 0 ? std::make_tuple(original.end(), original.end(), 0l) :
                    std::make_tuple(original.begin(), original.begin(), original[0]);

        Iter64 fst_elem_it = std::next(original.begin());
        // Triples are represent segments of array: best and current.
        // First element is the start, second is the end, third is the sum of segment elements.
        RetTripleType cur = std::make_tuple(fst_elem_it, fst_elem_it, 0),
                      best = std::make_tuple(fst_elem_it, fst_elem_it, 0);
        auto get_segment_start = [](RetTripleType & triple) -> Iter64 & {return std::get<0>(triple);};
        auto get_segment_end = [](RetTripleType & triple) -> Iter64 & {return std::get<1>(triple);};
        auto get_segment_sum = [](RetTripleType & triple) -> std::int64_t & {return std::get<2>(triple);};
        for(Iter64 i = fst_elem_it; i < original.end(); i++, get_segment_end(cur)++)
        {
            if(get_segment_sum(cur) <= 0)
            {
                get_segment_start(cur) = get_segment_end(cur);
                get_segment_sum(cur) = (*i - *std::prev(i));
            }
            else
                get_segment_sum(cur) += (*i - *std::prev(i));
            if(get_segment_sum(cur) > get_segment_sum(best))
            {
                get_segment_sum(best) = get_segment_sum(cur);
                get_segment_start(best) = get_segment_start(cur);
                get_segment_end(best) = get_segment_end(cur) + 1;
            }
        }
        return std::make_tuple(std::prev(get_segment_start(best)), std::prev(get_segment_end(best)), get_segment_sum(best));
    }
};
