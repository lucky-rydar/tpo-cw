#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>

#include "qsort.hpp"
#include "qsort_async.hpp"

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

template <int SZ>
void compare_qsorts(int n = 1'000'000) {
	vector<int> v;
	// generate 10 random numbers
	for (int i = 0; i < n; i++)
		v.push_back(rand() % n);

	vector<int> v_async = v;

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

	cout << "Async qsort was " << (float)duration_sync.count() / (float)duration_async.count() << " times faster" << endl;
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

	// puts("");
	// LOG("Test qsort sync");
	// test_qsort_sync();
	// LOG("Passed");

	// puts("");
	// LOG("Test qsort async");
	// test_qsort_async();
	// LOG("Passed");

	// puts("");
	// LOG("Test qsort correct");
	// test_qsort_correct();
	// LOG("Passed");

	// puts("");
	// LOG("Test qsort async correct");
	// test_qsort_async_correct();
	// LOG("Passed");

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
