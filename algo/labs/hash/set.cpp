//
// Created by Evgeniy on 10.05.2017.
//

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

class set {
private:
	std::vector<std::list<int>> arr;
	size_t size;

	size_t hash(int k, size_t capacity) {
		static unsigned a = rand(), b = rand();
		return (a * abs(k) + b) % capacity;
	}

	void resize(size_t new_capacity) {
		std::vector<std::list<int>> copy(new_capacity);
		for (auto i = arr.begin(); i != arr.end(); ++i)
			for (auto j = i->begin(); j != i->end(); ++j)
				copy[hash(*j, new_capacity)].push_front(*j);
		arr = copy;
	}

public:

	set(size_t capacity = 16) : arr(capacity), size(0) {
	}

	void insert(int data) {
		/*if ((double)size > 1.5 * arr.capacity())
		resize(arr.capacity() * 2); */
		int h = hash(data, arr.capacity());
		for (auto i = arr[h].begin(); i != arr[h].end(); ++i)
			if (*i == data)
				return;
		arr[h].push_back(data);
		size++;
	}

	bool remove(int data) {
		int h = hash(data, arr.capacity());
		for (auto i = arr[h].begin(); i != arr[h].end(); ++i)
			if (*i == data) {
				arr[h].erase(i);
				return true;
			}
		return false;
	}

	bool exist(int data) {
		int h = hash(data, arr.capacity());
		for (auto i = arr[h].begin(); i != arr[h].end(); ++i)
			if (*i == data)
				return true;
		return false;
	}
};

std::string file_name = "set";


int main(void) {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(0);
	set s(3000000);
	std::string key_word;

	while (std::cin >> key_word) {
		int a;
		std::cin >> a;

		if (key_word == "insert")
			s.insert(a);
		else if (key_word == "exists") {
			bool res = s.exist(a);
			if (res)
				std::cout << "true\n";
			else
				std::cout << "false\n";
		}
		else if (key_word == "delete")
			s.remove(a);
	}

	return 0;
}