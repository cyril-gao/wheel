#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <algorithm>
#include <vector>

#include "check.h"


/*
Seating Arrangements
There are n guests attending a dinner party, numbered from 1 to n.
The ith guest has a height of arr[i-1] inches.

The guests will sit down at a circular table which has n seats, numbered
from 1 to n in clockwise order around the table. As the host, you will
choose how to arrange the guests, one per seat. Note that there are n!
possible permutations of seat assignments.

Once the guests have sat down, the awkwardness between a pair of guests
sitting in adjacent seats is defined as the absolute difference between
their two heights. Note that, because the table is circular, seats 1 and
n are considered to be adjacent to one another, and that there are therefore
n pairs of adjacent guests.

The overall awkwardness of the seating arrangement is then defined as the
maximum awkwardness of any pair of adjacent guests. Determine the minimum
possible overall awkwardness of any seating arrangement.

Example
n = 4
arr = [5, 10, 6, 8]
output = 4

If the guests sit down in the permutation [3, 1, 4, 2] in clockwise order
around the table (having heights [6, 5, 8, 10], in that order), then the
four awkwardnesses between pairs of adjacent guests will be |6-5| = 1,
|5-8| = 3, |8-10| = 2, and |10-6| = 4, yielding an overall awkwardness of
4. It's impossible to achieve a smaller overall awkwardness.
*/

int min_overall_awkwardness(std::vector<int>& heights)
{
    int retval = 0;
    size_t n = heights.size();
    if (n > 2) {
        std::sort(heights.begin(), heights.end());
        retval = std::max(heights[1] - heights[0], heights[2] - heights[0]);
        size_t i = 1, j = 2;
        size_t next_i = i + 2, next_j = j + 2;
        while (next_j < n) {
            int v1 = std::max(heights[next_i] - heights[i], heights[next_j] - heights[j]);
            int v2 = std::max(heights[next_i] - heights[j], heights[next_j] - heights[i]);
            retval = std::max(retval, std::min(v1, v2));
            i = next_i;
            next_i += 2;
            j = next_j;
            next_j += 2;
        }
        if (next_i < n) {
            int v = std::max(heights[next_i] - heights[i], heights[next_i] - heights[j]);
            retval = std::max(retval, v);
        } else {
            retval = std::max(retval, heights[j] - heights[i]);
        }
    } else {
        if (n == 2) {
            retval = abs(heights[0] - heights[1]);
        }
    }
    return retval;
}

int main(int argc, char * argv[])
{
    try {
        {
            std::vector<int> heights = {};
            examine(min_overall_awkwardness(heights) == 0, "min_overall_awkwardness is failed at the line: %d\n", __LINE__);
        }
        
        {
            std::vector<int> heights = {7};
            examine(min_overall_awkwardness(heights) == 0, "min_overall_awkwardness is failed at the line: %d\n", __LINE__);
        }

        {
            std::vector<int> heights = {7, 13};
            examine(min_overall_awkwardness(heights) == 6, "min_overall_awkwardness is failed at the line: %d\n", __LINE__);
        }

        {
            std::vector<int> heights = {7, 13, 21};
            examine(min_overall_awkwardness(heights) == 14, "min_overall_awkwardness is failed at the line: %d\n", __LINE__);
        }

        {
            std::vector<int> heights = {2, 4, 6, 8, 9, 11, 13};
            examine(min_overall_awkwardness(heights) == 4, "min_overall_awkwardness is failed at the line: %d\n", __LINE__);
        }

        {
            std::vector<int> heights = {2, 4, 6, 8, 9, 11, 13, 16};
            examine(min_overall_awkwardness(heights) == 5, "min_overall_awkwardness is failed at the line: %d\n", __LINE__);
        }

        {
            std::vector<int> heights = {5, 6, 8, 10};
            examine(min_overall_awkwardness(heights) == 4, "min_overall_awkwardness is failed at the line: %d\n", __LINE__);
        }

        {
            std::vector<int> heights = {1, 2, 3, 5, 7};
            examine(min_overall_awkwardness(heights) == 4, "min_overall_awkwardness is failed at the line: %d\n", __LINE__);
        }
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}

