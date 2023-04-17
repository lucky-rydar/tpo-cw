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

#endif // CW_UTILS_HPP_
