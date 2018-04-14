#include "huffman_cod.h"
huffman_decoder::huffman_decoder(uint8_t *tree_expl_bits, size_t size_tree, size_t size_alpha) : tree(tree_expl_bits, size_tree, size_alpha) {
}

std::vector<uint8_t> huffman_decoder::decode_part(const bits_sequence &seq) {
	std::vector<uint8_t> result;
	size_t cur_ind = 0;
	uint8_t sym;
	while (tree.get_symbol_by_seq(seq, cur_ind, sym)) {
		result.push_back(sym);
	}
	return result;
}