// ALGOS.cpp: определяет точку входа для консольного приложения.
//

#include<iostream>
#include<fstream>
#include <queue>
#include<vector>
#include<algorithm>
#include<queue>
#include "edx-io.hpp"
using namespace std;

struct val {
	long long key;
	val* next;
	val(long long v) : key(v) {};

};

struct HashSet {
	vector<val*> arr;
	HashSet() {
		arr.resize(96557);
	}
	
	long long hash(long long x)
	{
		x = x ^ (x >> 32);
		return x;
	}
	val* get(long long key) {
		val* node = arr[hash(key) % 96557];
		while (node) {
			if (node->key == key) {
				return node;
			}
			node = node->next;
		}
		return nullptr;
	}
	bool exists(long long key) {
		return get(key);
	}
	void add(long long key) {
		if (exists(key)) {
			return;
		}
		val* node = new val(key);
		node->next = arr[hash(key) % 96557];
		arr[hash(key) % 96557] = node;
	}
	void remove(long long key) {
		if (!exists(key)) {
			return;
		}
		val* node = arr[hash(key) % 96557];
		val* prev = nullptr;
		while (node) {
			if (node->key == key) {
				if (!prev) {
					arr[hash(key) % 96557] = node->next;
				}
				else {
					prev->next = node->next;
					node->next = nullptr;
				}
				return;
			}
			prev = node;
			node = node->next;
		}
	}
};

int main()
{
	int n;
	io >> n;
	char c;
	long long k;
	HashSet hs;
	for (int i = 0; i < n; i++) {
		io >> c >> k;
		switch (c) {
		case 'A':
			hs.add(k);
			break;
		case '?':
			hs.exists(k) ? io << 'Y' : io << 'N';
			io << "\n";
			break;
		case 'D':
			hs.remove(k);
		}
	}
	return 0;
}

