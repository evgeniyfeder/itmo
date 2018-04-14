#ifndef __FREQ_TREE_
#define __FREQ_TREE_
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "bits_seq.h"

class freq_tree {
public:
	struct node {
		uint8_t c;
		node *left, *right;

		node(uint8_t c) : c(c), left(nullptr), right(nullptr) {
		}
		node(node *left, node *right) : c(0), left(left), right(right) {
		}
		~node() {
			delete left;
			delete right;	
		}
	} *root;
	static const int alpha_size = 256;
	node *cur_read_node;
private:
	void create_code_rec(bits_sequence &bits, node *cur_node, node *parent);
	void create_code_alpha_rec(std::vector<uint8_t> &alpha, node *cur_node);
	void create_alpha_rec(std::unordered_map<uint8_t, bits_sequence> &alpha, node *cur_node, bits_sequence &cur_seq);

	node *get_symbol_by_seq_rec(node *cur_node, size_t &cur_ind, const bits_sequence &seq, uint8_t &res_sym);

	node *create_tree_rec(const bits_sequence &tree, const std::vector<uint8_t> &alpha, size_t &ind_tree, size_t &ind_alpha);
public:
	freq_tree(const std::vector<uint64_t> &all_freqs);
	freq_tree(uint8_t *tree_expl_bits, size_t size_tree, size_t size_alpha);
	~freq_tree();

	void create_code(std::vector<uint8_t>& alpha, bits_sequence & bits); 
	std::unordered_map<uint8_t, bits_sequence> create_alphabit();

	bool get_symbol_by_seq(const bits_sequence &seq, size_t &cur_ind, uint8_t &res_sym);
};


#endif // __FREQ_TREE_