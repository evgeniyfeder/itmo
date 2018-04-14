//
// Created by Evgeniy on 10.05.2017.
//

#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

const uint p_mul[] = { 1, 31, 961, 29791, 923521, 28629151, 887503681, 1742810335, 2487512833, 4098453791, 2498015937, 129082719, 4001564289, 3789408671, 1507551809, 3784433119, 1353309697, 3297894943, 3450495425, 3886143071 };

class string_map {
private:
	typedef std::pair<std::string, std::string> pair;

	std::vector<std::list<pair>> arr;
	size_t size;
	
	uint hash(std::string key, int capacity) {
		uint hash = 0;

		for (size_t i = 0; i < key.length(); i++) {
			hash += p_mul[i] * (key[i] - 'a' + 1);
		}
		return hash % capacity;
	}

	void resize(size_t new_capacity) {
		std::vector<std::list<pair>> copy = arr;
		arr.clear();
		arr.resize(new_capacity);
		for (auto i = copy.begin(); i != copy.end(); ++i)
			for (auto j = i->begin(); j != i->end(); ++j)
				arr[hash(j->first, new_capacity)].push_back(*j);
	}

public:

	string_map(size_t capacity = 16) : arr(capacity), size(0) {
	}

	void insert(std::string key, std::string data) {
		if ((double)size > 1.5 * arr.capacity())
			resize(arr.capacity() * 2);
		uint h = hash(key, arr.capacity());
		for (auto i = arr[h].begin(); i != arr[h].end(); ++i)
			if (i->first == key) {
				i->second = data;
				return;
			}
		arr[h].push_back(pair(key, data));
		size++;
	}

	bool remove(std::string key) {
		uint h = hash(key, arr.capacity());
		for (auto i = arr[h].begin(); i != arr[h].end(); ++i)
			if (i->first == key) {
				arr[h].erase(i);
				return true;
			}
		return false;
	}

	bool exist(std::string key, std::string *res_data) {
		uint h = hash(key, arr.capacity());
		for (auto i = arr[h].begin(); i != arr[h].end(); ++i)
			if (i->first == key) {
				if (res_data != nullptr)
					*res_data = i->second;
				return true;
			}
		return false;
	}
};

std::string file_name = "map";

int main(void) {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(0);

	string_map s;
	std::string key_word;
	while (std::cin >> key_word) {
		std::string key, data;
		std::cin >> key;

		if (key_word == "put") {
			std::cin >> data;
			s.insert(key, data);
		}
		else if (key_word == "get") {
			bool res = s.exist(key, &data);
			if (res)
				std::cout << data << std::endl;
			else
				std::cout << "none\n";
		}
		else if (key_word == "delete")
			s.remove(key);
	}

	return 0;
}