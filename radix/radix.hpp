#pragma once
#include <iterator>
#include <vector>
#include <algorithm>

namespace radix {
	template <typename  T>
	static bool abs_compare(T a,T b)
	{
		return (std::abs(a) < std::abs(b));
	}
	
	template<class RandomAccessIterator, typename T>
	void counting_sort(RandomAccessIterator first, RandomAccessIterator last, T dig)
	{
		const auto numbers = 19;
		const auto offset = 9;
		const auto amount = std::distance(first,last);
		std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> output;
		output.resize(amount);
		typename std::iterator_traits<RandomAccessIterator>::value_type  count[numbers] = { 0 };
		for (auto i = first; i != last; ++i)
		{
			++count[((*i) / dig) % 10 + offset];
		}
		for (int i = 1; i <numbers; ++i)
		{
			count[i] += count[i - 1];
		}
		for (auto i = amount - 1; i >= 0; --i)
		{
			output[count[((*(first + i)) / dig) % 10 + offset] - 1] = *(first + i);
			--count[((*(first + i)) / dig) % 10 + offset];
		}
		auto n = 0;
		for (auto i = first; i != last; ++i)
		{
			(*i) = output[n];
			n++;
		}
	}



	template <class RandomAccessIterator, class Compare>
	typename std::enable_if<std::is_integral<typename std::iterator_traits<RandomAccessIterator>::value_type>::value, void>::type
		sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		if (first == last)
			return;

		auto m = std::abs(*(std::max_element(first, last,abs_compare<typename std::iterator_traits<RandomAccessIterator>::value_type>)));
		for (long long dig = 1; m / dig > 0; dig *= 10)
		{
			counting_sort(first, last, dig);
		}
		if(!comp(-1,1))
		{
			std::reverse(first, last);
		}

	}

	template<class RandomAccessIterator, class Compare>
	typename std::enable_if<!std::is_integral<typename std::iterator_traits<RandomAccessIterator>::value_type>::value, void>::type
		sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		std::sort(first, last, comp);
	}
}

