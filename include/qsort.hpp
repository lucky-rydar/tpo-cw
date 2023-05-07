#ifndef QSORT_HPP
#define QSORT_HPP

#include <vector>

#include "cw_utils.hpp"

template <typename T>
void qsort_util(std::vector<T>& v, int left, int right)
{
	int i = left;
	int j = right;

	T pivot = get_pivot(v, left, right);
	partition(v, pivot, i, j);

	if (left < j)
		qsort_util(v, left, j);
	if (i < right)
		qsort_util(v, i, right);
}

template <typename T>
void qsort(std::vector<T>& v)
{
	qsort_util(v, 0, v.size() - 1);
}

#endif // QSORT_HPP
