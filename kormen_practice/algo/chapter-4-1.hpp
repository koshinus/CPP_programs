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

    int64_t barrier;

    std::vector<int64_t> array_preprocessing(const std::vector<int64_t> & vec)
    {
        std::vector<int64_t> preprocessed(vec.size() - 1, 0);
        for(size_t i = 0; i < vec.size() - 1; i++)
            preprocessed[i] = vec[i+1] - vec[i];

        std::cout << "Preprocessed array: [";
        for (auto elem : preprocessed)
            std::cout << elem << ' ';
        std::cout << "\b]\n";

        return preprocessed;
    }

public:

    max_subarray_searcher()
    {
        std::numeric_limits<int64_t> limits;
        barrier = limits.max();
    }

    max_subarray_searcher(int64_t barrier_): barrier(barrier_) {}

    std::tuple<Iter64, Iter64, std::int64_t> find_max_subarray_brute_force(std::vector<int64_t> & vec)
    {
        std::numeric_limits<int64_t> i64_limits;
        std::tuple<Iter64, Iter64, std::int64_t> result = std::make_tuple(vec.begin(), vec.begin(), i64_limits.min());
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
    std::tuple<Iter64, Iter64, std::int64_t> find_max_subarray_recursively(std::vector<int64_t> & vec)
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

    std::tuple<Iter64, Iter64, std::int64_t>
    find_max_subarray_recursively_subroutine(Iter64 low, Iter64 high)
    {
        if (low == high)
            return std::make_tuple(low, high, *high);

        Iter64 mid = std::next(low, std::distance(low, high)/2);

        std::tuple<Iter64, Iter64, std::int64_t> left_tup =
                find_max_subarray_recursively_subroutine(low, mid);
        std::tuple<Iter64, Iter64, std::int64_t> right_tup =
                find_max_subarray_recursively_subroutine(std::next(mid), high);
        std::tuple<Iter64, Iter64, std::int64_t> crossed_tup =
                find_max_crossing_subarray(low, mid, high);
        if (std::get<2>(left_tup) >= std::get<2>(right_tup) && std::get<2>(left_tup) >= std::get<2>(crossed_tup))
            return left_tup;
        else if (std::get<2>(right_tup) >= std::get<2>(left_tup) && std::get<2>(right_tup) >= std::get<2>(crossed_tup))
            return right_tup;
        else
            return crossed_tup;
    }

    std::tuple<Iter64, Iter64, std::int64_t>
    find_max_crossing_subarray(Iter64 low, Iter64 mid, Iter64 high)
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

    std::tuple<Iter64, Iter64, std::int64_t> find_max_subarray_recursively_enchanted(std::vector<int64_t> & vec)
    {
        if (vec.size() <= barrier)
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
    // TODO: understand, why this realization doesn't work
    // TODO: (something wrong with "high" border in "fmcs" function)
    std::tuple<std::int64_t, std::int64_t, std::int64_t> fmsr(std::vector<int64_t> & vec)
    {
        std::vector<int64_t> preprocessed_array = array_preprocessing(vec);
        auto tup = fms(preprocessed_array, 0, vec.size()-1);
        int64_t left  = std::get<0>(tup);
        int64_t right = std::get<1>(tup);
        return std::make_tuple
                (
                    left,
                    right,
                    std::get<2>(tup)
                );
    }

    std::tuple<std::int64_t, std::int64_t, std::int64_t> fms(std::vector<int64_t> & vec, int64_t low, int64_t high)
    {
        if (low == high)
            return std::make_tuple(low, high, vec[low]);

        int64_t mid = (low + high)/2;
        //std::cout << "Mid-m: " << mid << '\n';
        std::tuple<std::int64_t, std::int64_t, std::int64_t> left_tup = fms(vec, low, mid);
        std::tuple<std::int64_t, std::int64_t, std::int64_t> right_tup = fms(vec, mid + 1, high);
        std::tuple<std::int64_t, std::int64_t, std::int64_t> cross_tup = fmcs(vec, low, mid, high);
        /*
        std::cout << "Left:  (" << std::get<0>(left_tup) << ',' << std::get<1>(left_tup) << ',' << std::get<2>(left_tup) << ") | "
                  << "Right: (" << std::get<0>(right_tup) << ',' << std::get<1>(right_tup) << ',' << std::get<2>(right_tup) << ") | "
                  << "Cross: (" << std::get<0>(cross_tup) << ',' << std::get<1>(cross_tup) << ',' << std::get<2>(cross_tup) << ")\n";

        if (std::get<2>(left_tup) >= std::get<2>(right_tup) && std::get<2>(left_tup) >= std::get<2>(cross_tup))
            return left_tup;
        else if (std::get<2>(right_tup) >= std::get<2>(left_tup) && std::get<2>(right_tup) >= std::get<2>(cross_tup))
            return right_tup;
        else
            return cross_tup;
    }

    std::tuple<std::int64_t, std::int64_t, std::int64_t>
    fmcs(std::vector<int64_t> & vec, int64_t low, int64_t mid, int64_t high)
    {
        std::numeric_limits<int64_t> i64_limits;
        std::int64_t left_sum = i64_limits.min(), right_sum = i64_limits.min(), sum = 0;
        std::int64_t min_left, max_right;
        for (int64_t i = mid; i > low - 1; i--)
        {
            sum += vec[i];
            if (sum > left_sum)
            {
                left_sum = sum;
                min_left = i;
            }
        }
        sum = 0;
        for (int64_t j = mid + 1; j < high + 1; j++)
        {
            sum += vec[j];
            if (sum > right_sum)
            {
                right_sum = sum;
                max_right = j;
            }
        }
        return std::make_tuple(min_left, max_right, right_sum + left_sum);
    }
    */

    std::tuple<Iter64, Iter64, std::int64_t> kadane_max_subarray_search(std::vector<int64_t> & vec)
    {
        std::vector<int64_t> preprocessed_array = array_preprocessing(vec);
        int64_t sum = 0, cur_sum = 0;
        Iter64 cur_i, best_i, start_i;
        cur_i = start_i = best_i = preprocessed_array.begin();
        for(Iter64 it = preprocessed_array.begin(); it < preprocessed_array.end(); it++)
        {
            if(cur_sum + *it > 0)
                cur_sum += *it;
            else
            {
                cur_sum = 0;
                cur_i = std::next(it);
            }
            if(cur_sum > sum)
            {
                start_i = cur_i;
                best_i = std::next(it);
                sum = cur_sum;
            }
        }
        return std::make_tuple(start_i, best_i, sum);
    }
};