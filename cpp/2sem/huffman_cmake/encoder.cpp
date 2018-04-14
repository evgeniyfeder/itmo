#include "huffman_cod.h"

frequency_counter::frequency_counter() : file_freqs(256) {
	for (size_t i = 0; i < file_freqs.size(); i++)
		file_freqs[i] = 0;
}

void frequency_counter::add_file_block(const uint8_t *part, size_t size) {
	for (size_t cur_ind = 0; cur_ind < size; ++cur_ind) {
		file_freqs[part[cur_ind]]++;
	}
}

huffman_encoder::huffman_encoder(const frequency_counter &freqs) : tree(freqs.file_freqs) {
	sym_map = tree.create_alphabit();
}

bits_sequence huffman_encoder::code_part(const uint8_t *part, size_t size) {
	bits_sequence res;
	
	for (size_t i = 0; i < size; i++)
		res.push(sym_map[part[i]]);
	return res;
}

void huffman_encoder::get_tree_code(bits_sequence &bits, std::vector<uint8_t> &alpha) {
	tree.create_code(alpha, bits);
}
