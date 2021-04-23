#include <stdio.h>
#include <stdint.h>

#include <chrono>
#include <algorithm>
#include <random>
#include <vector>
#include <counting_sort.h>
#include <unordered_map>
#include "check.h"


/*
Given a non-empty array of integers, return the k most frequent elements.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]
*/

struct Pair
{
    int value;
    int count;

    Pair(int v, int c) : value(v), count(c) {}
    Pair(): Pair(0, 0) {}
};

namespace v1
{
    std::vector<int> top_k_frequent(std::vector<int>& nums, int k_frequent)
    {
        auto comp = [](Pair p1, Pair p2) {
            return p1.count > p2.count;
        };
        integer_sort(nums.begin(), nums.end());
        std::vector<Pair> heap;
        heap.reserve(k_frequent);
        for (int i = 0, hi = 0, ie = static_cast<int>(nums.size()); i < ie;) {
            int j = i + 1;
            int c = 1;
            while (j < ie && nums[j] == nums[i]) {
                ++c;
                ++j;
            }
            if (hi < k_frequent) {
                heap.emplace_back(Pair(nums[i], c));
                ++hi;
                if (hi == k_frequent) {
                    std::make_heap(heap.begin(), heap.end(), comp);
                }
            } else {
                if (c > heap[0].count) {
                    std::pop_heap(heap.begin(), heap.end(), comp);
                    heap.back() = Pair(nums[i], c);
                    std::push_heap(heap.begin(), heap.end(), comp);
                }
            }
            i = j;
        }
        std::vector<int> retval;
        retval.reserve(k_frequent);
        for(auto p : heap) {
            retval.push_back(p.value);
        }
        return retval;
    }
}

namespace v2
{
    std::vector<int> top_k_frequent(std::vector<int>& nums, int k_frequent)
    {
        std::unordered_map<int, int> map;
        for (auto n : nums) {
            ++map[n];
        }
        auto comp = [](Pair p1, Pair p2) {
            return p1.count > p2.count;
        };
        std::vector<Pair> heap;
        heap.reserve(k_frequent);
        int hi = 0;
        for (auto i = map.begin(), ie = map.end(); i != ie; ++i) {
            if (hi < k_frequent) {
                heap.emplace_back(i->first, i->second);
                ++hi;
                if (hi == k_frequent) {
                    std::make_heap(heap.begin(), heap.end(), comp);
                }
            } else {
                if (i->second > heap[0].count) {
                    std::pop_heap(heap.begin(), heap.end(), comp);
                    heap.back() = Pair(i->first, i->second);
                    std::push_heap(heap.begin(), heap.end(), comp);
                }
            }
        }
        std::vector<int> retval;
        retval.reserve(k_frequent);
        for(auto p : heap) {
            retval.push_back(p.value);
        }
        return retval;
    }
}

int main()
{
    {
        std::vector<int> nums = {1, 1, 1, 2, 2, 3};
        auto result = v1::top_k_frequent(nums, 2);
        std::sort(result.begin(), result.end());
        examine(
            result.size() == 2 && result[0] == 1 && result[1] == 2,
            "v1::top_k_frequent is failed at the line: %d\n", __LINE__
        );
        result = v1::top_k_frequent(nums, 3);
        std::sort(result.begin(), result.end());
        examine(
            result.size() == 3 && result[0] == 1 && result[1] == 2 && result[2] == 3,
            "v1::top_k_frequent is failed at the line: %d\n", __LINE__
        );
        result = v1::top_k_frequent(nums, 4);
        std::sort(result.begin(), result.end());
        examine(
            result.size() == 3 && result[0] == 1 && result[1] == 2 && result[2] == 3,
            "v1::top_k_frequent is failed at the line: %d\n", __LINE__
        );
    }
    {
        std::vector<int> nums = {1};
        auto result = v1::top_k_frequent(nums, 1);
        examine(
            result.size() == 1 && result[0] == 1,
            "v1::top_k_frequent is failed at the line: %d\n", __LINE__
        );
        result = v1::top_k_frequent(nums, 3);
        examine(
            result.size() == 1 && result[0] == 1,
            "v1::top_k_frequent is failed at the line: %d\n", __LINE__
        );
    }
    {
        std::vector<int> nums = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 5, 6, 7, 8, 9, 9 };
        auto result = v1::top_k_frequent(nums, 2);
        std::sort(result.begin(), result.end());
        examine(
            result.size() == 2 && result[0] == 1 && result[1] == 2,
            "v1::top_k_frequent is failed at the line: %d\n", __LINE__
        );
        result = v1::top_k_frequent(nums, 3);
        std::sort(result.begin(), result.end());
        examine(
            result.size() == 3 && result[0] == 1 && result[1] == 2 && result[2] == 3,
            "v1::top_k_frequent is failed at the line: %d\n", __LINE__
        );
        result = v1::top_k_frequent(nums, 4);
        std::sort(result.begin(), result.end());
        examine(
            result.size() == 4 && result[0] == 1 && result[1] == 2 && result[2] == 3 && result[3] == 9,
            "v1::top_k_frequent is failed at the line: %d\n", __LINE__
        );
    }
    {
        int k_frequent = 1000000;
        std::random_device rd;
        std::uniform_int_distribution<int> dist(-2 * k_frequent, 2 * k_frequent);
        std::vector<int> nums(k_frequent * 6);
        for (auto & n : nums) {
            n = dist(rd);
        }
        auto begin = std::chrono::system_clock::now();
        auto r1 = v1::top_k_frequent(nums, k_frequent);
        auto end = std::chrono::system_clock::now();
        double d1 = std::chrono::duration<double>(end - begin).count();
        begin = std::chrono::system_clock::now();
        auto r2 = v2::top_k_frequent(nums, k_frequent);
        end = std::chrono::system_clock::now();
        double d2 = std::chrono::duration<double>(end - begin).count();
        std::sort(r1.begin(), r1.end());
        std::sort(r2.begin(), r2.end());
        printf("v1: %f seconds, v2: %f seconds\n", d1, d2);
    }
    printf("OK\n");
    return 0;
}
