#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include <fstream>
#include <algorithm>
#include <vector>

#include "check.h"

std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &inout)
{
    std::sort(
        inout.begin(), inout.end(),
        [](std::vector<int> const &l, std::vector<int> const &r) {
            if (l[0] != r[0])
            {
                return l[0] < r[0];
            }
            else
            {
                return l[1] < r[1];
            }
        });

    std::vector<std::vector<int>> retval;
    size_t n = inout.size();
    retval.reserve(n);
    for (size_t i = 0; i < n;)
    {
        int start = inout[i][0];
        int stop = inout[i][1];
        size_t j = i + 1;
        while (j < n)
        {
            int nt = inout[j][0];
            int np = inout[j][1];
            if (nt <= stop)
            {
                stop = std::max(stop, np);
                ++j;
            }
            else
            {
                break;
            }
        }
        std::vector<int> nv = {start, stop};
        retval.emplace_back(std::move(nv));
        i = j;
    }
    return retval;
}

std::vector<std::vector<int>> insert(std::vector<std::vector<int>> const &intervals, std::vector<int> const &new_interval)
{
    auto start = new_interval[0];
    auto stop = new_interval[1];

    std::vector<std::vector<int>> retval;
    size_t n = intervals.size();
    retval.reserve(n);
    size_t i = 0;
    bool crossing = false;

    while (i < n)
    {
        auto it = intervals[i][0];
        auto ip = intervals[i][1];
        if (it <= start && start <= ip)
        {
            start = it;
            stop = std::max(stop, ip);
            crossing = true;
            break;
        }
        if (it > start)
        {
            break;
        }

        retval.push_back(intervals[i]);
        ++i;
    }

    if (i < n)
    {
        if (crossing)
        {
            ++i;
        }
        while (i < n)
        {
            auto it = intervals[i][0];
            auto ip = intervals[i][1];
            if (stop < ip)
            {
                if (it <= stop)
                {
                    ++i;
                    stop = ip;
                }
                break;
            }
            else if (stop == ip)
            {
                ++i;
                break;
            }
            ++i;
        }
        std::vector<int> itv = {start, stop};
        retval.emplace_back(std::move(itv));
        if (i < n)
        {
            retval.insert(retval.end(), intervals.begin() + i, intervals.end());
        }
    }
    else
    {
        std::vector<int> itv = { start, stop };
        retval.emplace_back(std::move(itv));
    }

    return retval;
}

int main(int argc, char *argv[])
{
    {
        const std::vector<std::vector<int>> expection = {{1, 5}, {6, 9}};
        std::vector<std::vector<int>> intervals = {{1, 3}, {6, 9}};
        std::vector<int> new_interval = {2, 5};
        auto result = insert(intervals, new_interval);
        examine(expection == result, "insert is wrong, the code line is: %d\n", __LINE__);
    }
    {
        const std::vector<std::vector<int>> expection = {{1, 5}};
        std::vector<std::vector<int>> intervals = {{1, 5}};
        std::vector<int> new_interval = {2, 3};
        auto result = insert(intervals, new_interval);
        examine(expection == result, "insert is wrong, the code line is: %d\n", __LINE__);
    }
    {
        const std::vector<std::vector<int>> expection = {{1, 7}};
        std::vector<std::vector<int>> intervals = {{1, 5}};
        std::vector<int> new_interval = {2, 7};
        auto result = insert(intervals, new_interval);
        examine(expection == result, "insert is wrong, the code line is: %d\n", __LINE__);
    }
    {
        const std::vector<std::vector<int>> expection = {{2, 5}};
        std::vector<std::vector<int>> intervals;
        std::vector<int> new_interval = {2, 5};
        auto result = insert(intervals, new_interval);
        examine(expection == result, "insert is wrong, the code line is: %d\n", __LINE__);
    }
    {
        const std::vector<std::vector<int>> expection = {{1, 2}, {3, 10}, {12, 16}};
        std::vector<std::vector<int>> intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
        std::vector<int> new_interval = {4, 8};
        auto result = insert(intervals, new_interval);
        examine(expection == result, "insert is wrong, the code line is: %d\n", __LINE__);
    }

    {
        const std::vector<std::vector<int>> expection = {
            {1, 6}, {8, 10}, {15, 18}};
        std::vector<std::vector<int>> inout = {
            {1, 3}, {2, 6}, {8, 10}, {15, 18}};
        auto result = merge(inout);
        examine(expection == result, "merge is wrong, the code line is: %d\n", __LINE__);
    }
    {
        const std::vector<std::vector<int>> expection = {
            {1, 5}};
        std::vector<std::vector<int>> inout = {
            {1, 4}, {4, 5}};
        auto result = merge(inout);
        examine(expection == result, "merge is wrong, the code line is: %d\n", __LINE__);
    }
    {
        const std::vector<std::vector<int>> expection = {
            {1, 18}};
        std::vector<std::vector<int>> inout = {
            {1, 3}, {2, 6}, {8, 10}, {15, 18}, {5, 9}, {7, 8}, {10, 14}, {11, 17}};
        auto result = merge(inout);
        examine(expection == result, "merge is wrong, the code line is: %d\n", __LINE__);
    }
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        auto randinterval = [](int upper_limit, int range) {
            assert(upper_limit > 0 && range > 0);
            unsigned start = static_cast<unsigned>(rand()) % static_cast<unsigned>(upper_limit);
            unsigned stop = start + static_cast<unsigned>(rand()) % static_cast<unsigned>(range);
            return std::vector<int>{static_cast<int>(start), static_cast<int>(stop)};
        };

        size_t limit = 100000;
        std::vector<std::vector<int>> inout;
        inout.reserve(limit);
        for (size_t i = 0; i < limit; ++i)
        {
            inout.emplace_back(randinterval(static_cast<int>(limit * 1000), 11));
        }
        auto result = merge(inout);
        examine(!result.empty(), "merge is wrong, the code line is: %d\n", __LINE__);
    }

    for (int i = 1; i < argc; ++i)
    {
        std::ifstream ifs(argv[i]);
        if (ifs.is_open())
        {
            std::vector<std::vector<int>> inout;
            char buf[128] = "";
            while (!ifs.eof())
            {
                ifs.getline(buf, sizeof(buf));
                auto s = strchr(buf, ',');
                if (s != nullptr)
                {
                    *s++ = 0;
                    std::vector<int> interval;
                    interval.push_back(atoi(buf));
                    interval.push_back(atoi(s));
                    inout.emplace_back(std::move(interval));
                }
            }
            if (!inout.empty())
            {
                auto result = merge(inout);
                examine(!result.empty(), "merge is wrong, the code line is: %d\n", __LINE__);
            }
        }
    }
    return 0;
}
