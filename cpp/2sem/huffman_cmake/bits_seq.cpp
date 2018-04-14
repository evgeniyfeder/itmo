#include "bits_seq.h"
#include <assert.h>
#include <cstring>

bits_sequence::bits_sequence() : num_init_bits(0) {
}

bits_sequence::bits_sequence(uint8_t * data, size_t size) : bits((size % sizeof_type != 0) ? (size / sizeof_type + 1) : (size / sizeof_type)), num_init_bits(size) {
	memcpy(bits.data(), data, bits.size() * sizeof(type));
}

bits_sequence::bits_sequence(std::vector<type>& data) : bits(data), num_init_bits(data.size() * sizeof_type) {
}

void bits_sequence::set_bit(size_t ind, bool bit) {
	assert(ind < num_init_bits);
	if (bit)
		bits[ind / sizeof_type] |= (1LL << (ind % sizeof_type));
	else
		bits[ind / sizeof_type] &= ~(1LL << (ind % sizeof_type));
}

void bits_sequence::set_next(bool bit) {
	assert(num_init_bits != UINT64_MAX);
	if ((num_init_bits % sizeof_type) == 0)
		bits.push_back(0);
	if (bit)
		bits[num_init_bits / sizeof_type] |= (1LL << (num_init_bits % sizeof_type));
	else
		bits[num_init_bits / sizeof_type] &= ~(1LL << (num_init_bits % sizeof_type));
	num_init_bits++;
}

void bits_sequence::remove_last() {
	num_init_bits--;
	if ((num_init_bits % sizeof_type) == 0)
		bits.pop_back();
}

void bits_sequence::remove_last(size_t num) {
	assert(num <= num_init_bits);
	while (num > sizeof_type) {
		bits.pop_back();
		num -= sizeof_type;
	}
	if (num >= num_init_bits % sizeof_type && num_init_bits / sizeof_type != (double)num_init_bits / sizeof_type) {
		bits.pop_back();
		num_init_bits = sizeof_type - (num - num_init_bits);
	}
	else
		num_init_bits -= num;
}

bool bits_sequence::get_bit(size_t ind) {
	assert(ind < num_init_bits);
	return (bool) ((bits[ind / sizeof_type] >> (ind % sizeof_type)) & 1);
}
bool bits_sequence::get_bit(size_t ind) const {
	assert(ind < num_init_bits);
	return (bool) ((bits[ind / sizeof_type] >> (ind % sizeof_type)) & 1);
}

int64_t bits_sequence::get_block(size_t ind) {
	assert(ind >= bits.size());
	return bits[ind];
}

int64_t bits_sequence::get_block(size_t ind) const {
	assert(ind >= bits.size());
	return bits[ind];
}

void bits_sequence::set_block(size_t ind, type data) {
	assert(ind < bits.size());
	if (ind == bits.size() - 1)
		num_init_bits = sizeof_type * bits.size();
	bits[ind] = data;
}

bool bits_sequence::get_last() {
	return get_bit(num_init_bits);
}

bool bits_sequence::get_last() const {
	return get_bit(num_init_bits);
}

uint32_t bits_sequence::size() const {
	return num_init_bits;
}

uint32_t bits_sequence::size() {
	return num_init_bits;
}

uint32_t bits_sequence::size_block() const {
	return sizeof(uint64_t);
}

uint32_t bits_sequence::size_block() {
	return sizeof(uint64_t);
}

std::vector<bits_sequence::type> bits_sequence::data() const {
	return bits;
}

std::vector<bits_sequence::type> bits_sequence::data() {
	return bits;
}

void bits_sequence::push(const bits_sequence & added) {
	bits.reserve((num_init_bits + added.size()) / (sizeof(uint64_t) * 8) + 
		((num_init_bits + added.size()) % (sizeof(uint64_t) * 8) != 0));
	for (size_t i = 0; i < added.size(); i++)
		set_next(added.get_bit(i));
}
