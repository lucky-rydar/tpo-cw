#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>

#include "qsort.hpp"
#include "qsort_async.hpp"
#include "qsort_pool.hpp"
#include "test_qsort.hpp"

using namespace std;

template <int SZ>
void compare_qsorts(int n = 1'000'000) {
	vector<int> v;
	// generate 10 random numbers
	for (int i = 0; i < n; i++)
		v.push_back(rand() % n);

	vector<int> v_async = v;
	vector<int> v_async_pool = v;

	auto start = chrono::high_resolution_clock::now();
	qsort(v);
	auto end = chrono::high_resolution_clock::now();
	auto duration_sync = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Sync qsort took " << (float)duration_sync.count() / 1000.0f << " ms" << endl;

	start = chrono::high_resolution_clock::now();
	qsort_async<int, SZ>(v_async);
	end = chrono::high_resolution_clock::now();
	auto duration_async = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Async qsort took " << (float)duration_async.count() / 1000.0f << " ms" << endl;

	start = chrono::high_resolution_clock::now();
	qsort_pool<int, SZ>(v_async_pool);
	end = chrono::high_resolution_clock::now();
	auto duration_async_pool = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Async qsort pool took " << (float)duration_async_pool.count() / 1000.0f << " ms" << endl;

	// verify vectors
	for (int i = 0; i < v.size(); i++) {
		if (v[i] != v_async[i]) {
			cout << "Sync and async qsorts are different" << endl;
			return;
		}
		if (v[i] != v_async_pool[i]) {
			cout << "Sync and async pool qsorts are different" << endl;
			return;
		}
	}

	puts("");
	cout << "Async qsort was " << (float)duration_sync.count() / (float)duration_async.count() << " times faster" << endl;
	cout << "Async qsort pool was " << (float)duration_sync.count() / (float)duration_async_pool.count() << " times faster" << endl;

	puts("===============================");
}

string big_num_to_string(int n) {
	string s = to_string(n);
	string res = "";
	for (int i = s.size() - 1, j = 0; i >= 0; i--, j++) {
		if (j % 3 == 0 && j != 0)
			res += " ";
		res += s[i];
	}
	reverse(res.begin(), res.end());
	return res;
}

int main() {
	srand(time(NULL));

	run_tests();

	auto range = {100'000, 1'000'000, 10'000'000, 100'000'000 /*,1'000'000'000*/};

	puts("");
	LOG("Compare qsorts with sync size " << big_num_to_string(100));
	{
		for (int n : range) {
			puts("");
			LOG("Compare qsorts " << n);
			compare_qsorts<100>(n);
		}
	}

	puts("");
	LOG("Compare qsorts with sync size " << big_num_to_string(1'000));
	{
		for (int n : range) {
			puts("");
			LOG("Compare qsorts " << n);
			compare_qsorts<1'000>(n);
		}
	}

	puts("");
	LOG("Compare qsorts with sync size " << big_num_to_string(10'000));
	{
		for (int n : range) {
			puts("");
			LOG("Compare qsorts " << n);
			compare_qsorts<10'000>(n);
		}
	}

	puts("");
	LOG("Compare qsorts with sync size " << big_num_to_string(100'000));
	{
		for (int n : range) {
			puts("");
			LOG("Compare qsorts " << n);
			compare_qsorts<100'000>(n);
		}
	}
}
