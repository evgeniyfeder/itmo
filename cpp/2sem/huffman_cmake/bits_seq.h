#pragma once
#ifndef _BITS_SEQ_H_
#define _BITS_SEQ_H_

#include <cstdint>
#include <vector>
#include <cstddef>

class bits_sequence {
private:
	typedef uint64_t type;
	std::vector<type> bits;
	uint32_t num_init_bits;

public:
	static const size_t sizeof_type = sizeof(type) * 8;

	bits_sequence();
	bits_sequence(uint8_t *data, size_t size);
	bits_sequence(std::vector<type> &data);

	void set_bit(size_t ind, bool bit);
	void set_next(bool bit);

	void remove_last();
	void remove_last(size_t num);
	
	bool get_bit(size_t ind);
	bool get_bit(size_t ind) const;

	int64_t get_block(size_t ind);
	int64_t get_block(size_t ind) const;

	void set_block(size_t ind, type data);

	bool get_last();
	bool get_last() const;

	uint32_t size() const;
	uint32_t size();

	uint32_t size_block() const;
	uint32_t size_block();

	std::vector<type> data() const;
	std::vector<type> data();

	void push(const bits_sequence &added);
};

#endif // _BITS_SEQ_H_

