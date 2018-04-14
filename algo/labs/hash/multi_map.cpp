//
// Created by Evgeniy on 10.05.2017.
//

#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

typedef unsigned int uint;

const uint p_mul[] = { 1, 31, 961, 29791, 923521, 28629151, 887503681, 1742810335, 2487512833, 4098453791, 2498015937, 129082719, 4001564289, 3789408671, 1507551809, 3784433119, 1353309697, 3297894943, 3450495425, 3886143071 };

class multi_map {
private:
	typedef std::pair<std::string, std::unordered_set<std::string>> pair;

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
		std::vector<std::list<pair>> copy(new_capacity);
		for (auto i = arr.begin(); i != arr.end(); ++i)
			for (auto j = i->begin(); j != i->end(); ++j)
				copy[hash(j->first, new_capacity)].push_back(*j);
		arr = copy;
	}

public:

	multi_map(size_t capacity = 16) : arr(capacity), size(0) {
	}

	void insert(std::string key, std::string data) {
		if ((double)size > 1.5 * arr.capacity())
			resize(arr.capacity() * 2);
		uint h = hash(key, arr.capacity());
		for (auto i = arr[h].begin(); i != arr[h].end(); ++i)
			if (i->first == key) {
				i->second.insert(data);
				return;
			}
		arr[h].push_front(pair(key, std::unordered_set<std::string>()));
		arr[h].begin()->second.insert(data);
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

	bool remove(std::string key, std::string data) {
		uint h = hash(key, arr.capacity());
		for (auto i = arr[h].begin(); i != arr[h].end(); ++i)
			if (i->first == key) {
				if (i->second.erase(data) != 0)
					return true;
				else
					return false;

			}
		return false;
	}

	bool exist(std::string key, std::unordered_set<std::string> * res_data) {
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

std::string file_name = "multimap";

int main(void) {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(0);

	multi_map s;
	std::string key_word;
	std::unordered_set<std::string> get_data;

	while (std::cin >> key_word) {
		
		std::string key, data;
		std::cin >> key;

		if (key_word == "put") {
			std::cin >> data;
			s.insert(key, data);
		}
		else if (key_word == "get") {
			if (s.exist(key, &get_data)) {
				std::cout << get_data.size() << " ";
				for (auto i = get_data.begin(); i != get_data.end(); ++i)
					std::cout << *i << " ";
				std::cout << std::endl;
			}
			else
				std::cout << "0\n";
		}
		else if (key_word == "delete") {
			std::cin >> data;
			s.remove(key, data);
		}
		else if (key_word == "deleteall") {
			s.remove(key);
		}
	}

	return 0;
}