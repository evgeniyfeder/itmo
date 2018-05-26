#include <string>
#include <unordered_map>
#include <utility>
#include <queue>
#include <stack>
#include <iostream>

std::string file_name = "tree";


class suf_tree {
private:
	int num_vertices;
	std::string input_str;
	
	struct node {
		int parent;								// index to parent
		int position, length;					// substr to parent [position - length, position)
		std::unordered_map<char, int> childs;   // map for childrens
		std::unordered_map<char, int> links;	// prefix links
	};

	std::vector<node> tree;

private:
	void connect_child(int child, int parent, char c, int child_len) {
		tree[parent].childs[c] = child;
		tree[child].length = child_len;
		tree[child].parent = parent;
	}

	void add_suffix(int i, int n) {
		int v, len_v_to_end =  n - i, old = num_vertices - 1;

		std::stack<int> path;
		for (v = old; tree[v].links.count(input_str[i]) == 0; v = tree[v].parent) {
			len_v_to_end -= tree[v].length;
			path.push(v);
		}

		int w = tree[v].links[input_str[i]];
		if (tree[w].childs.count(input_str[i + len_v_to_end]) != 0) {
			// create new vertex
			int u = tree[w].childs[input_str[i + len_v_to_end]];

			tree.emplace_back();
			for (tree[num_vertices].position = tree[u].position - tree[u].length; 
				input_str[tree[num_vertices].position] == input_str[i + len_v_to_end]; 
				tree[num_vertices].position += tree[v].length) {
				
				v = path.top();
				path.pop();
				len_v_to_end += tree[v].length;
			}

			// create vertex betwen w and u
			connect_child(num_vertices, w, input_str[tree[u].position - tree[u].length], tree[u].length - (tree[u].position - tree[num_vertices].position));
			connect_child(u, num_vertices, input_str[tree[num_vertices].position], tree[u].position - tree[num_vertices].position);

			tree[v].links[input_str[i]] = num_vertices++;
			w = tree[v].links[input_str[i]];
		}
		// create ending for current suffix
		tree.emplace_back();
		tree[old].links[input_str[i]] = num_vertices;
		connect_child(num_vertices, w, input_str[i + len_v_to_end], n - (i + len_v_to_end));
		tree[num_vertices++].position = n;
	}

	void print_rec(int cur) {
		std::cout << tree[cur].parent << " " << cur << " " << tree[cur].position - tree[cur].length + 1 << " " << tree[cur].position - 1 + 1 << '\n';

		for (auto it = tree[cur].childs.begin(); it != tree[cur].childs.end(); ++it) {
			print_rec(it->second);
		}
	}

public:
	suf_tree(std::string input) : input_str(std::move(input)){
		int n = (int)input_str.size();

		tree.emplace_back();
		for (int i = 0; i < 256; i++) {
			tree[0].links[(char)i] = 1;
		}

		tree.emplace_back();
		tree[1].position = -1;
		tree[1].length = 1;
		tree[1].parent = 0;

		num_vertices = 2;
		/* Algorithm Breslauera(easy Wagner) */
		for (int i = n - 1; i >= 0; i--)
			add_suffix(i, n);
	}

	void print() {
		std::cout << num_vertices - 1 << " " << num_vertices - 2 << "\n";

		for (auto it = tree[1].childs.begin(); it != tree[1].childs.end(); ++it) {
			print_rec(it->second);
		}
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

	suf_tree st(input);
	st.print();
}
