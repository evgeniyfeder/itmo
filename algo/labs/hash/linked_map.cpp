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
	struct hash_node {
		std::string key;
		std::string data;
		int hash;
		hash_node *list_next;
		hash_node *deq_prev, *deq_next;
		
		hash_node(std::string key,
			std::string data,
			int hash,
			hash_node *list_next = nullptr,
			hash_node *deq_prev = nullptr, hash_node *deq_next = nullptr) : key(key), data(data), hash(hash),
				list_next(list_next), deq_prev(deq_prev), deq_next(deq_next) {
		}

		hash_node() : key(std::string()), data(std::string()), hash(-1),
			list_next(nullptr), deq_prev(nullptr), deq_next(nullptr) {
		}
	} *header;

	std::vector<hash_node *> arr;
	size_t size;

	uint hash(std::string key, int capacity) {
		uint hash = 0;

		for (size_t i = 0; i < key.length(); i++) {
			hash += p_mul[i] * (key[i] - 'a' + 1);
		}
		return hash % capacity;
	}

	hash_node *find(const std::string &key) {
		uint h = hash(key, arr.capacity());
		for (hash_node *node = arr[h]; node != nullptr; node = node->list_next) {
			if (node->key == key) {
				return node;
			}

		}
		return nullptr;
	}
public:

	string_map(size_t capacity = 16) : arr(capacity), size(0) {
		header = new hash_node(std::string(), std::string(), -1);
		header->deq_next = header;
		header->deq_prev = header;
	}

	
	void insert(std::string key, std::string data) {
		hash_node *node = find(key);
		if (node != nullptr)
			node->data = data;
		else {
			uint h = hash(key, arr.capacity());
			arr[h] = new hash_node(key, data, h, arr[h], header->deq_prev, header);
			header->deq_prev->deq_next = arr[h];
			header->deq_prev = arr[h];
			size++;
		}
	}

	bool remove(std::string key) {
		uint h = hash(key, arr.capacity());
		if (arr[h] != nullptr && arr[h]->key == key) {
			arr[h]->deq_prev->deq_next = arr[h]->deq_next;
			arr[h]->deq_next->deq_prev = arr[h]->deq_prev;
			arr[h] = arr[h]->list_next;
		}
		for (hash_node *node = arr[h]; node != nullptr; node = node->list_next) {
			if (node->list_next != nullptr && node->list_next->key == key) {
				node->list_next->deq_prev->deq_next = node->list_next->deq_next;
				node->list_next->deq_next->deq_prev = node->list_next->deq_prev;
				node = node->list_next->list_next;
				return true;
			}
		}
		return false;
	}

	bool exist(std::string key, std::string *res_data) {
		hash_node *node = find(key);
		if (node != nullptr) {
			if (res_data != nullptr)
				*res_data = node->data;
			return true;
		}
		return false;
	}

	std::string next(const std::string &key) {
		hash_node *node = find(key);
		if (node == nullptr || node->deq_next->hash == -1)
			return "none";
		return node->deq_next->data;
	}

	std::string prev(const std::string &key) {
		hash_node *node = find(key);
		if (node == nullptr || node->deq_prev->hash == -1)
			return "none";
		return node->deq_prev->data;
	}
};

std::string file_name = "linkedmap";

int main(void) {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(0);

	string_map s(3000000);
	std::string key_word;

	while (std::cin >> key_word) {
		std::string key, data;
		std::cin >> key;

		if (key_word == "put") {
			std::cin >> data;
			s.insert(key, data);
		}
		else if (key_word == "get") {
			if (s.exist(key, &data))
				std::cout << data << std::endl;
			else
				std::cout << "none\n";
		}
		else if (key_word == "delete")
			s.remove(key);
		else if (key_word == "prev")
			std::cout << s.prev(key) << std::endl;
		else if (key_word == "next")
			std::cout << s.next(key) << std::endl;
	}

	return 0;
}