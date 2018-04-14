#include <iostream>
#include <vector>
#include <algorithm>
std::string file_name = "minonpath";

#define MAX_VERTS 200001
struct node { int p, val, d; };
std::vector<node> tree;
struct {
	int v, min;
} sparse[MAX_VERTS][32];

void add_vert(int cur, int p, int val) {
	tree[cur].p = p;
	tree[cur].val = val;
	tree[cur].d = tree[p].d + 1;
	
	sparse[cur][0].v = p;
	sparse[cur][0].min = val;
	for (int i = 1; i < 32; i++) {
		if (sparse[cur][i - 1].v == -1) {
			sparse[cur][i].v = -1;
			sparse[cur][i].min = INT_MAX;
		}
		else {
			sparse[cur][i].v = sparse[sparse[cur][i - 1].v][i - 1].v;
			sparse[cur][i].min = std::min(sparse[cur][i - 1].min, sparse[sparse[cur][i - 1].v][i - 1].min);
		}
	}
}

int get_min(int a, int b) {
	int result = INT_MAX;
	if (a == b)
		return result;

	/* Set d(a) == d(b) */
	if (tree[a].d < tree[b].d) std::swap(a, b);
	for (int i = 31; i >= 0; i--) {
		if (sparse[a][i].v != -1 && tree[sparse[a][i].v].d >= tree[b].d) {
			result = std::min(result, sparse[a][i].min);
			a = sparse[a][i].v;
		}
	}
	if (a == b)
		return result;

	for (int i = 31; i >= 0; i--) {
		if (sparse[a][i].v != sparse[b][i].v) {
			result = std::min(result, std::min(sparse[a][i].min, sparse[b][i].min));
			a = sparse[a][i].v;
			b = sparse[b][i].v;
		}
	}
	result = std::min(result, std::min(sparse[a][0].min, sparse[b][0].min));
	return result;
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	int n;
	std::cin >> n;
	tree.resize(n);

	tree[0].d = 0;
	tree[0].p = 0;
	tree[0].val = INT_MAX;
	for (int i = 0; i < 32; i++) {
		sparse[0][i].v = -1;
		sparse[0][i].min = INT_MAX;
	}

	for (int i = 0; i < n - 1; i++) {
		int parent, value;
		std::cin >> parent >> value;
		add_vert(i + 1, parent - 1, value);
	}

	int m;
	std::cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		std::cin >> a >> b;
		std::cout << get_min(a - 1, b - 1) << std::endl;
	}
	return 0;
}
