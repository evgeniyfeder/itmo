#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
std::string file_name = "treepathadd";
std::vector<bool> was;


/******** Create LHD module *********/
std::vector<int> tree_parent, d, size;
int n;
void create_tree(int cur, const std::vector<std::vector<int>> &edges) {
	if (was[cur])
		return;
	was[cur] = true;
	for (auto to = edges[cur].begin(); to != edges[cur].end(); ++to) {
		if (!was[*to]) {
			tree_parent[*to] = cur;
			d[*to] = d[cur] + 1;
			create_tree(*to, edges);
		}
	}
}

int count_size(int cur, const std::vector<std::vector<int>> &edges) {
	int res = 0;
	for (auto to = edges[cur].begin(); to != edges[cur].end(); ++to) {
		if (tree_parent[cur] != *to) {
			res += count_size(*to, edges);
		}
	}
	return (size[cur] = res + 1);
}

std::vector<int> leader, ind_tree;
void build_lhd(int cur, int lead, const std::vector<std::vector<int>> &edges) {
	static int cur_set = -1;
	cur_set++;

	ind_tree[cur] = cur_set;
	leader[cur] = lead;

	/* Count max size of subtree */
	int max_size = -1, max_ind = 0;
	for (auto to = edges[cur].begin(); to != edges[cur].end(); ++to) {
		if (tree_parent[cur] != *to && max_size < size[*to]) {
			max_size = size[*to];
			max_ind = *to;
		}
	}
	if (max_size != -1)
		build_lhd(max_ind, lead, edges);

	/* Go to other vertices */
	for (auto to = edges[cur].begin(); to != edges[cur].end(); ++to)
		if (tree_parent[cur] != *to && max_ind != *to)
			build_lhd(*to, *to, edges);
}

void create_lhd() {
	std::cin >> n;

	std::vector<std::vector<int>> edges(n);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		std::cin >> a >> b;
		edges[a - 1].push_back(b - 1);
		edges[b - 1].push_back(a - 1);
	}

	was.resize(n);
	tree_parent.resize(n);
	d.resize(n);
	tree_parent[0] = 0;
	d[0] = 0;
	create_tree(0, edges);

	size.resize(n);
	count_size(0, edges);

	leader.resize(n);
	ind_tree.resize(n);
	build_lhd(0, 0, edges);
}


/****** Work with LHD module *********/
class segment_tree {
	struct node {
		long long add;

		node() : add(0) {
		}
	};
public:
	std::vector<node> heap;
	int n;

	segment_tree(const std::vector<long long> &arr) : n(arr.size()) {
		heap.resize(4 * n);
	}

	long long get_recur(int cur_vert, int cur_left, int cur_right, int ind) {
		if (cur_left == ind && cur_right == ind)
			return heap[cur_vert].add;

		int middle = cur_left + (cur_right - cur_left) / 2;
		if (middle >= ind)
			return get_recur(2 * cur_vert, cur_left, middle, ind) + heap[cur_vert].add;
		else
			return get_recur(2 * cur_vert + 1, middle + 1, cur_right, ind) + heap[cur_vert].add;
	}

	long long get(int ind) {
		return get_recur(1, 0, n - 1, ind);
	}

	void add_recur(int cur_vert, int cur_left, int cur_right, int add_left, int add_right, long long x) {
		if (add_right < add_left)
			return;
		if (cur_left == add_left && cur_right == add_right) {
			heap[cur_vert].add += x;
			return;
		}

		int middle = cur_left + (cur_right - cur_left) / 2;
		add_recur(2 * cur_vert, cur_left, middle, add_left, std::min(add_right, middle), x);
		add_recur(2 * cur_vert + 1, middle + 1, cur_right, std::max(add_left, middle + 1), add_right, x);
	}

	void add(int left, int right, long long x) {
		if (left > right)
			std::swap(left, right);
		add_recur(1, 0, n - 1, left, right, x);
	}
};

void add(int a, int b, int x, segment_tree &tree) {
	while (leader[a] != leader[b]) {
		if (d[leader[a]] < d[leader[b]])
			std::swap(a, b);
		tree.add(ind_tree[leader[a]], ind_tree[a], x);
		a = tree_parent[leader[a]];
	}

	tree.add(ind_tree[a], ind_tree[b], x);
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	create_lhd();
	std::vector<long long> tmp(n);
	segment_tree tree(tmp);

	int m;
	std::cin >> m;
	std::string op;
	for (int i = 0; i < m; i++) {
		std::cin >> op;
		if (op == "+") {
			int a, b, x;
			std::cin >> a >> b >> x;
			add(a - 1, b - 1, x, tree);
		}
		else if (op == "?") {
			int x;
			std::cin >> x;
			std::cout << tree.get(ind_tree[x - 1]) << std::endl;
		}
	}
	return 0;
}
