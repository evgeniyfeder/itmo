#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include <iostream>

std::string file_name = "trie";

class suf_pork {
private:
	size_t num_nodes, num_edges;

	struct node {
		std::unordered_map<char, std::unique_ptr<node>> next;
		size_t index;
		size_t *num_nodes, *num_edges;

		node(size_t index, size_t *num_nodes, size_t *num_edges) : index(index), num_nodes(num_nodes), num_edges(num_edges) {}

		node * go(char c) {
			if (next.find(c) == next.end()) {
				next[c] = std::make_unique<node>(++(*num_nodes), num_nodes, num_edges);
				++(*num_edges);
			}
			return next[c].get();
		}
	};
	std::unique_ptr<node> head{new node(1, &num_nodes, &num_edges)};

	void print_rec(node *cur) {
		for (auto it = cur->next.begin(); it != cur->next.end(); ++it) {
			std::cout << cur->index << " " << it->second->index << " " << it->first << "\n";
			print_rec(it->second.get());
		}
	}
public:
	suf_pork(const std::string &str) : num_nodes(1), num_edges(0) {
		for (size_t i = 0; i < str.size(); i++) {
			node *ptr = head.get();

			for (size_t j = i; j < str.size(); j++) {
				ptr = ptr->go(str[j]);
			}
		}
	}

	void print() {
		std::cout << num_nodes << " " << num_edges << '\n';
		print_rec(head.get());
	}
};

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	std::string input;
	std::cin >> input;

	suf_pork sp(input);
	sp.print();
}
