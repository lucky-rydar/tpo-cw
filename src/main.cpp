#include <iostream>

#include "cw_utils.hpp"
#include "qsort.hpp"

using namespace std;

void test_qsort_sync() {
	vector<int> v;
	// generate 10 random numbers
	for (int i = 0; i < 10; i++)
		v.push_back(rand() % 100);

	qsort(v);
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

int main() {
	srand(time(NULL));

	test_qsort_sync();
}
