#pragma once
#include "freq_tree.h"
#include <unordered_map>

class frequency_counter {
	friend class huffman_encoder;
private:
	std::vector<uint64_t> file_freqs;
public:
	frequency_counter();
	void add_file_block(const uint8_t *data, size_t size);
};

class huffman_encoder {
	std::unordered_map<uint8_t, bits_sequence> sym_map;
	freq_tree tree;
public:
	huffman_encoder(const frequency_counter &freqs);
	bits_sequence code_part(const uint8_t *part, size_t size);
	void get_tree_code(bits_sequence &bits, std::vector<uint8_t> &alpha);
};

class huffman_decoder {
	freq_tree tree;
	std::vector<uint8_t> result;
public:
	huffman_decoder(uint8_t *tree_expl_bits, size_t size_tree, size_t size_alpha);
	std::vector<uint8_t> decode_part(const bits_sequence &seq);
};