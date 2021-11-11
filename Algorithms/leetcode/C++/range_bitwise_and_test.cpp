#include <assert.h>
#include <stdio.h>

#include "check.h"


/*
 * Given two integers left and right that represent the range [left, right],
 * return the bitwise AND of all numbers in this range, inclusive.
 */

size_t range_bitwise_and(size_t begin, size_t last)
{
	assert(begin <= last);
	size_t diff = last - begin;
	size_t mask = -1;
	while (diff != 0) {
		mask <<= 1;
		diff >>= 1;
	}
	return begin & last & mask;
}

int main()
{
	try {
		examine(range_bitwise_and(5, 7) == 4, "range_bitwise_and is failed at the line: %d\n", __LINE__);
		examine(range_bitwise_and(0, 0) == 0, "range_bitwise_and is failed at the line: %d\n", __LINE__);
		examine(range_bitwise_and(1, 1) == 1, "range_bitwise_and is failed at the line: %d\n", __LINE__);
		examine(range_bitwise_and(2, 3) == 2, "range_bitwise_and is failed at the line: %d\n", __LINE__);
		examine(range_bitwise_and(1, 2147483647) == 0, "range_bitwise_and is failed at the line: %d\n", __LINE__);
		examine(range_bitwise_and(19, 22) == 16, "range_bitwise_and is failed at the line: %d\n", __LINE__);
	} catch (std::exception const& e) {
		fprintf(stderr, "%s\n", e.what());
		return 1;
	}
	return 0;
}
