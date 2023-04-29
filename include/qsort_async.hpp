#ifndef QSORT_ASYNC_HPP
#define QSORT_ASYNC_HPP

#include "cw_utils.hpp"

#include <vector>
#include <future>

template <typename T, int sync_size = 10'000>
void qsort_async_util(std::vector<T>& v, int left, int right)
{
	int i = left;
	int j = right;
	T pivot = middle_of_three(v[left], v[(left + right) / 2], v[right]);
	partition(v, left, right, pivot, i, j);

	std::future<void> left_future;
	std::future<void> right_future;

	if (left < j)
	{
		if (j - left < sync_size) {
			qsort_async_util(v, left, j);
		}
		else {
			left_future = std::async(std::launch::async, [&v, left, j]() { qsort_async_util(v, left, j); });
		}
	}
	if (i < right)
	{
		if (right - i < sync_size) {
			qsort_async_util(v, i, right);
		}
		else {
			right_future = std::async(std::launch::async, [&v, i, right]() { qsort_async_util(v, i, right); });
		}			
	}

	if (left_future.valid())
		left_future.wait();
	if (right_future.valid())
		right_future.wait();
}

template <typename T, int SZ = 10'000>
void qsort_async(std::vector<T>& v)
{
	qsort_async_util<T, SZ>(v, 0, v.size() - 1);
}

#endif // QSORT_ASYNC_HPP
