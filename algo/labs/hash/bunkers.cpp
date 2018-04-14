#include <string>
#include <iostream>
#include <vector>
#include <queue>
std::string file_name = "";

std::vector<std::vector<int>> graph;
int n;

struct tree_node {
	int parent, deep;

	tree_node() : parent(-1), deep(-1) {
	}
};

int root_ind, far_vert_ind, max_deep;
void create_tree(int v) {
	std::vector<tree_node> tree(n);

	std::vector<bool> was(n);
	std::queue<int> q;
	
	tree[v].deep = 0;
	q.push(v);
	was[v] = true;
	while (!q.empty()) {
		int cur_vert = q.front();
		q.pop();
		for (auto j = graph[cur_vert].begin(); j != graph[cur_vert].end(); j++)
			if (!was[*j]) {
				was[*j] = true;
				tree[*j].deep = tree[cur_vert].deep + 1;
				tree[*j].parent = cur_vert;
				q.push(*j);
			}
	}

	max_deep = tree[0].deep, far_vert_ind = 0;
	for (int i = 0; i < n; i++)
		if (tree[i].deep > max_deep) {
			max_deep = tree[i].deep;
			far_vert_ind = i;
		}

	root_ind = far_vert_ind;
	for (int i = 0; i < max_deep / 2; i++)
		root_ind = tree[root_ind].parent;
}

typedef long long ll;
bool is_isomorph = false;
ll check_isomorph(int v, std::vector<bool> &was, bool is_root) {
	was[v] = true;

	std::vector<ll> child_hash;
	ll a = 1, b = 0;
	for (auto j = graph[v].begin(); j != graph[v].end(); j++) {
		if (!was[*j]) {
			child_hash.push_back(check_isomorph(*j, was, false));
			a *= child_hash.back();
			b += child_hash.back();
		}
	}
	if (is_root)
		if (child_hash.size() == 2 && child_hash[0] == child_hash[1])
			is_isomorph = true;
	return a + b;
}

int main(void) {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	std::cin >> n;
	graph.resize(n);

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		std::cin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}
	create_tree(0);
	create_tree(far_vert_ind);
	if (max_deep % 2 != 0 || graph[root_ind].size() != 2) {
		std::cout << "NO" << std::endl;
		return 0;
	}

	std::vector<bool> was(n);
	check_isomorph(root_ind, was, true);
	if (is_isomorph)
		std::cout << "YES" << std::endl;
	else
		std::cout << "NO" << std::endl;
	return 0;
}