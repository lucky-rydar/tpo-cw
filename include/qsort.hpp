#ifndef QSORT_HPP
#define QSORT_HPP

#include <vector>

template <typename T>
T middle_of_three(T& a, T& b, T& c)
{
	if (a < b)
	{
		if (b < c)
			return b;
		else if (a < c)
			return c;
		else
			return a;
	}
	else
	{
		if (a < c)
			return a;
		else if (b < c)
			return c;
		else
			return b;
	}
}

template <typename T>
void qsort_util(std::vector<T>& v, int left, int right)
{
	int i = left;
	int j = right;
	T pivot = middle_of_three(v[left], v[(left + right) / 2], v[right]);

	while (i <= j)
	{
		while (v[i] < pivot)
			i++;
		while (v[j] > pivot)
			j--;
		if (i <= j)
		{
			std::swap(v[i], v[j]);
			i++;
			j--;
		}
	}

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
