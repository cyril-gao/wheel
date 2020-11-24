#ifndef INSERTION_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define INSERTION_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <stdint.h>
#include <iterator>

template <typename RandomIt, typename Compare>
inline void insertion_sort(RandomIt begin, RandomIt end, Compare comp)
{
	for (RandomIt i = begin + 1; i < end; ++i)
	{
		auto sentinel = *i;
		int64_t j = static_cast<int64_t>(std::distance(begin, i)) - 1;
		for (; j >= 0; --j)
		{
			if (comp(sentinel, *(begin + j)))
			{
				*(begin + j + 1) = *(begin + j);
			}
			else
			{
				break;
			}
		}
		*(begin + (j + 1)) = sentinel;
	}
}

template <typename RandomIt>
inline void insertion_sort(RandomIt begin, RandomIt end)
{
	using Compare = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>;
	insertion_sort<RandomIt, Compare>(begin, end, Compare());
}

#endif //INSERTION_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00