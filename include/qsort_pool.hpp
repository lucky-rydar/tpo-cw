#ifndef QSORT_POOL_HPP
#define QSORT_POOL_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <queue>
#include <functional>
#include <vector>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>

// if need to run subtasks in parallel, use thread pool and do not wait for them to finish
template <typename T, int sync_size = 10'000>
void qsort_pool_util(std::vector<T>& v, int left, int right, boost::asio::thread_pool&& tp) {
	int i = left;
	int j = right;

	T pivot = get_pivot(v, left, right);
	partition(v, left, right, pivot, i, j);

	if (left < j) {
		if (j - left < sync_size) {
			qsort_pool_util(v, left, j, std::move(tp));
		}
		else {
			boost::asio::post(tp, [&v, left, j, &tp]() { qsort_pool_util(v, left, j, std::move(tp)); });
		}
	}
	if (i < right) {
		if (right - i < sync_size) {
			qsort_pool_util(v, i, right, std::move(tp));
		}
		else {
			boost::asio::post(tp, [&v, i, right, &tp]() { qsort_pool_util(v, i, right, std::move(tp)); });
		}
	}
}

template <typename T, int SZ = 10'000>
void qsort_pool(std::vector<T>& v) {
	boost::asio::thread_pool tp(std::thread::hardware_concurrency());
	qsort_pool_util(v, 0, v.size() - 1, std::move(tp));
	tp.join();
}

#endif // QSORT_POOL_HPP
