#ifndef CW_UTILS_HPP_
#define CW_UTILS_HPP_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
#include <memory>

#define LOG(x) std::cout << "log: " << x << std::endl;

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
T get_pivot(std::vector<T>& v, int left, int right)
{
	return middle_of_three(v[left], v[(left + right) / 2], v[right]);
}

template <typename T>
void partition(std::vector<T>& v, int left, int right, int pivot, int& i, int& j)
{
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
}

#endif // CW_UTILS_HPP_
