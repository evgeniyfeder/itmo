#include <cstring>
#include "my_vector.h"

void my_vector::big_vector::inplace_reserve(int new_capacity) {
	capacity = new_capacity;
	new (&data) sp_type(new uint32_t[new_capacity]);
}

void my_vector::big_vector::inplace_copy(const big_vector &to_copy) {
	capacity = to_copy.capacity;
	new (&data) sp_type(to_copy.data);
}

my_vector::big_vector::big_vector() : capacity(0), data(nullptr) {
}

my_vector::big_vector::~big_vector() {
}

my_vector::big_vector::big_vector(size_t capacity) : 
    capacity(capacity), data(new uint32_t[capacity], std::default_delete<uint32_t[]>()) {
	
}

void my_vector::do_empty() {
	size = 0;
}

bool my_vector::is_small() const {
	return !is_big;
}

void my_vector::do_unique_copy() {
	if (!is_small() && !big.data.unique()) {
		big_vector tmp(big.capacity);
		memcpy(tmp.data.get(), big.data.get(), sizeof(uint32_t) * big.capacity);
		big = tmp;
		cur_data = big.data.get();
	}
}

my_vector::my_vector(size_t size) : size(size), big(), is_big(size > small_capacity) {
	if (is_small()) 
		cur_data = small;
	else {
		big.inplace_reserve(size);
		cur_data = big.data.get();
	}
	memset(cur_data, 0, get_capacity() * sizeof(uint32_t));
}

my_vector::my_vector(const my_vector& vec) : size(vec.size), big(), is_big(vec.is_big) {
	if (vec.is_small()) {
		cur_data = small;
		memcpy(small, vec.small, small_capacity * sizeof(uint32_t));
	}
	else {
		big.inplace_copy(vec.big);
		cur_data = big.data.get();
	}
}

my_vector::~my_vector() {
	if (!is_small())
		big.~big_vector();
}

my_vector& my_vector::operator=(const my_vector& vec) {
    if (!is_small())
        big.~big_vector();

    size = vec.size;
    is_big = vec.is_big;
    if (vec.is_small()) {
        cur_data = small;
        memcpy(small, vec.small, small_capacity * sizeof(uint32_t));
    }
    else {
        big.inplace_copy(vec.big);
        cur_data = big.data.get();
    }
    return *this;
}

void my_vector::push_back(uint32_t elem) {
    push_back_allocate(size + 1);
	cur_data[size - 1] = elem;
}

uint32_t my_vector::operator[](size_t ind) const {
	return cur_data[ind];
}

my_vector& my_vector::set(size_t ind, uint32_t elem) {
	do_unique_copy();
	cur_data[ind] = elem;
	return *this;
}

void my_vector::reverse() {
	do_unique_copy();
	for (size_t i = 0; i < size / 2; i++)
		std::swap(cur_data[i], cur_data[size - i - 1]);
}

void my_vector::normalize() {
	while (cur_data[get_size() - 1] == 0 && get_size() > 1)
		size--;
}

void my_vector::push_back_allocate(size_t new_size) {
	size_t old_capacity = get_capacity();

	size = new_size;
	if (new_size <= old_capacity)
		return;

	big_vector tmp(2 * old_capacity);
	memcpy(tmp.data.get(), cur_data, sizeof(uint32_t) * old_capacity);
	if (old_capacity == small_capacity) {
		is_big = true;
		memset(small, 0, sizeof(uint32_t) * small_capacity);
	}
	big = tmp;
	size = new_size;
	cur_data = big.data.get();
}

void my_vector::resize(size_t new_size) {
    size_t old_capacity = get_capacity();

    size = new_size;
    if (new_size <= old_capacity)
        return;

    big_vector tmp(new_size);
    memcpy(tmp.data.get(), cur_data, sizeof(uint32_t) * old_capacity);
    if (old_capacity == small_capacity) {
        is_big = true;
        memset(small, 0, sizeof(uint32_t) * small_capacity);
    }
    big = tmp;
    size = new_size;
    cur_data = big.data.get();
}

size_t my_vector::get_capacity() const {
	return is_small() ? small_capacity : big.capacity;
}

size_t my_vector::get_size() const {
	return size;
}
