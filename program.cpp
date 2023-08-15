#include <iostream>
#include "macros.h"
#include "CustomVector.h"
#include <random>

using namespace std;

#define MAXN 100000

int main() {
	srand(time(NULL));
	CustomVector<int> vec;
	
	for (int i = 0; i < MAXN; i++) {
		int n = rand() % MAXN;
		info("%d", n);
		vec.push_back(n);
	}

	for (auto it = vec.begin(); it != vec.end(); it++) {
		cout << *it << endl;
	}

	info("size: %ld", vec.size());
	info("capacity: %ld", vec.capacity());
	
	return 0;
}