#ifndef TEST_QSORT_HPP
#define TEST_QSORT_HPP

#include <vector>
#include <iostream>
#include <random>
#include <functional>
#include <algorithm>

#include "qsort_pool.hpp"
#include "qsort_async.hpp"
#include "qsort.hpp"
#include "cw_utils.hpp"

using namespace std;

void test_qsort_sync() {
	vector<int> v;
	// generate 10 random numbers
	for (int i = 0; i < 10; i++)
		v.push_back(rand() % 100);

	qsort(v);
	
	cout << "Sync sorted  : ";
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

void test_qsort_async() {
	vector<int> v;
	// generate 10 random numbers
	for (int i = 0; i < 10; i++)
		v.push_back(rand() % 100);

	qsort_async(v);

	cout << "Async sorted : ";
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

void test_qsort_correct() {
	int size = 1'000'000;
	int range = 10000;

	vector<int> v;
	for (int i = 0; i < size; i++)
		v.push_back(rand() % range);

	qsort(v);

	vector<int> v2;
	for (int i = 0; i < size; i++)
		v2.push_back(v[i]);

	std::sort(v2.begin(), v2.end());

	for (int i = 0; i < v.size(); i++) {
		if (v[i] != v2[i]) {
			cout << "Sync qsort is not correct" << endl;
			return;
		}
	}
	cout << "Sync qsort is correct" << endl;
}

void test_qsort_async_correct() {
	int size = 1'000'000;
	int range = 10000;

	vector<int> v;
	for (int i = 0; i < size; i++)
		v.push_back(rand() % range);

	qsort_async(v);

	vector<int> v2;
	for (int i = 0; i < size; i++)
		v2.push_back(v[i]);

	std::sort(v2.begin(), v2.end());

	for (int i = 0; i < v.size(); i++) {
		if (v[i] != v2[i]) {
			cout << "Async qsort is not correct" << endl;
			return;
		}
	}
	cout << "Async qsort is correct" << endl;
}

void test_qsort_pool_verify() {
	int size = 1'000'000;
	int range = 10000;

	vector<int> v;
	for (int i = 0; i < size; i++)
		v.push_back(rand() % range);

	qsort_pool(v);

	vector<int> v2;
	for (int i = 0; i < size; i++)
		v2.push_back(v[i]);

	std::sort(v2.begin(), v2.end());

	for (int i = 0; i < v.size(); i++) {
		if (v[i] != v2[i]) {
			cout << "Async pool qsort is not correct" << endl;
			return;
		}
	}
	cout << "Async pool qsort is correct" << endl;
}

void run_tests() {
	std::vector<std::function<void()>> tests = {
		test_qsort_sync,
		test_qsort_async,
		test_qsort_correct,
		test_qsort_async_correct,
		test_qsort_pool_verify
	};
	
	for (auto test : tests) {
		LOG("Running test...");
		test();
		LOG("Test finished");
		puts("");
	}
}

#endif // TEST_QSORT_HPP
