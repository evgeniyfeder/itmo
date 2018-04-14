#include "freq_tree.h"
#include <assert.h>

freq_tree::freq_tree(const std::vector<uint64_t> &all_freqs) : cur_read_node(root) {	
	assert(all_freqs.size() == alpha_size);
	typedef std::pair<uint64_t, node *> pair;
	uint64_t inf = (1LL << 60);

	/* Select non-null freqs and sort it */
	std::vector<pair> freqs;
	for (size_t i = 0; i < all_freqs.size(); i++)
		if (all_freqs[i] != 0)
			freqs.push_back(pair(all_freqs[i], new node((uint8_t)i)));
	std::sort(freqs.begin(), freqs.end(), [](const pair &a, const pair &b) { return a.first < b.first; });

    if (freqs.size() == 0)
        throw new std::runtime_error("Empty frequences");

	/* make addition data to create tree */
	size_t ind_freq = 0, ind_sum = 0;
	size_t n = freqs.size();
	freqs.push_back(pair(inf, nullptr));
	freqs.push_back(pair(inf, nullptr));
	std::vector<pair> sum_freqs;

	while (ind_freq < n || ind_sum < sum_freqs.size() - 1) {
		/* get two minimal elements from 2 arrays */
		uint64_t 
			f1 = freqs[ind_freq].first, f2 = freqs[ind_freq + 1].first, 
			s1 = inf, s2 = inf;
		if (ind_sum < sum_freqs.size())
			s1 = sum_freqs[ind_sum].first;
		if (ind_sum  + 1< sum_freqs.size())
			s2 = sum_freqs[ind_sum + 1].first;

		/* Set new node - minimal of 4 nodes */
		uint64_t res_freq;
		node *new_node;
		if (f1 + f2 <= s1 + s2 && f1 + f2 <= f1 + s1) {
			new_node = new node(freqs[ind_freq].second, freqs[ind_freq + 1].second);
			res_freq = f1 + f2;
			ind_freq += 2;

		}
		else if (f1 + s1 <= f1 + f2 && f1 + s1 <= s1 + s2) {
			new_node = new node(freqs[ind_freq++].second, sum_freqs[ind_sum++].second);
			res_freq = f1 + s1;
		}
		else {
			new_node = new node(sum_freqs[ind_sum].second, sum_freqs[ind_sum + 1].second);
			res_freq = s1 + s2;
			ind_sum += 2;		
		}
		sum_freqs.push_back(pair(res_freq, new_node));
	}
	root = sum_freqs[sum_freqs.size() - 1].second;
    if (freqs.size() == 3)
        root->right = new node(0);
}

freq_tree::freq_tree(uint8_t *tree_expl_bits, size_t size_tree, size_t size_alpha) {
	bits_sequence bs(tree_expl_bits, size_tree);
	std::vector<uint8_t> alpha(size_alpha);

	size_t begin_alpha = (size_tree / (sizeof(uint64_t) * 8) + (size_tree % (sizeof(uint64_t) * 8) != 0)) * sizeof(uint64_t);
	for (size_t i = 0; i < size_alpha; i++)
		alpha[i] = tree_expl_bits[begin_alpha + i];

	size_t a = 0, b = 0;
	root = create_tree_rec(bs, alpha, a, b);
	cur_read_node = root;
}

freq_tree::~freq_tree() {
	delete root;
}

void freq_tree::create_code_rec(bits_sequence &bits, node *cur_node, node *parent) {
	if (cur_node->left != nullptr) {
		bits.set_next(0);
		create_code_rec(bits, cur_node->left, cur_node);
		create_code_rec(bits, cur_node->right, cur_node);
	}
	if (cur_node != parent->right)
		bits.set_next(1);
}

void freq_tree::create_code(std::vector<uint8_t> &alpha, bits_sequence &bits) {
	create_code_rec(bits, root, root);
	create_code_alpha_rec(alpha, root);
}

std::unordered_map<uint8_t, bits_sequence> freq_tree::create_alphabit() {
	std::unordered_map<uint8_t, bits_sequence> map;
	bits_sequence seq;

	create_alpha_rec(map, root, seq);
	return map;
}

void freq_tree::create_code_alpha_rec(std::vector<uint8_t> &alpha, node *cur_node) {
	if (cur_node->left != nullptr) {
		create_code_alpha_rec(alpha, cur_node->left);
		create_code_alpha_rec(alpha, cur_node->right);
	}
	else {
		alpha.push_back(cur_node->c);
	}
}

void freq_tree::create_alpha_rec(std::unordered_map<uint8_t, bits_sequence> &alpha, node *cur_node, bits_sequence &cur_seq) {
	if (cur_node->left != nullptr) {
		cur_seq.set_next(0);
		create_alpha_rec(alpha, cur_node->left, cur_seq);
		cur_seq.remove_last();
		cur_seq.set_next(1);
		create_alpha_rec(alpha, cur_node->right, cur_seq);
		cur_seq.remove_last();
	}
	else {
		alpha[cur_node->c] = cur_seq;
	}
}

freq_tree::node * freq_tree::get_symbol_by_seq_rec(node *cur_node, size_t &cur_ind, const bits_sequence &seq, uint8_t &res_sym) {
	if (cur_node->left == nullptr) {
		res_sym = cur_node->c;
		return nullptr;
	}
	else if (cur_ind == seq.size())
		return cur_node;

	cur_ind++;
	if (seq.get_bit(cur_ind - 1) == 0)
		return get_symbol_by_seq_rec(cur_node->left, cur_ind, seq, res_sym);
	else
		return get_symbol_by_seq_rec(cur_node->right, cur_ind, seq, res_sym);
}

freq_tree::node * freq_tree::create_tree_rec(const bits_sequence &tree, const std::vector<uint8_t> &alpha, size_t &ind_tree, size_t &ind_alpha) {
	if (ind_tree >= tree.size())
		throw new std::runtime_error("Bad file format");

	bool bit = tree.get_bit(ind_tree++);
	if (bit) {
		if (ind_alpha >= alpha.size())
			throw new std::runtime_error("Bad file format");
		return new node(alpha[ind_alpha++]);
	}
	node *new_node = new node(0);
	new_node->left = create_tree_rec(tree, alpha, ind_tree, ind_alpha);
	new_node->right = create_tree_rec(tree, alpha, ind_tree, ind_alpha);
	return new_node;
}

bool freq_tree::get_symbol_by_seq(const bits_sequence &seq, size_t &cur_ind, uint8_t &res_sym) {
	cur_read_node = get_symbol_by_seq_rec(cur_read_node, cur_ind, seq, res_sym);
	if (cur_read_node == nullptr) {
		cur_read_node = root;
		return true;
	}
	return false;
}
