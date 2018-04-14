#include <iostream>
#include <vector>
#include <algorithm>
std::string file_name = "avia";

using pair = std::pair<int, int>;

std::vector<pair> vec_edges;
std::vector<std::vector<int>> edges;

std::vector<bool> used;
void dfs(int cur, const std::vector<std::vector<int>> &g) {
	used[cur] = true;
	for (auto to = g[cur].begin(); to != g[cur].end(); ++to)
		if (!used[*to])
			dfs(*to, g);
}

bool check(int middle, int n) {
	std::vector<std::vector<int>> g(n), reverse(n);

	for (int i = 0; i < middle; i++) {
		g[vec_edges[i].first].push_back(vec_edges[i].second);
		reverse[vec_edges[i].second].push_back(vec_edges[i].first);
	}

	for (int i = 0; i < n; i++)
		used[i] = 0;
	dfs(0, g);
	for (int i = 0; i < n; i++)
		if (!used[i])
			return false;

	for (int i = 0; i < n; i++)
		used[i] = 0;
	dfs(0, reverse);
	for (int i = 0; i < n; i++)
		if (!used[i])
			return false;

	return true;
}

bool compare(const pair &a, const pair &b) {
	return edges[a.first][a.second] < edges[b.first][b.second];
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

	int n;
	std::cin >> n;

	edges.resize(n);
	used.resize(n);
	for (int i = 0; i < n; i++) {
		edges[i].resize(n);
		for (int j = 0, x; j < n; j++) {
			std::cin >> x;
			if (i != j) {
				edges[i][j] = x;
				vec_edges.push_back(pair(i, j));
			}
		}
	}

	std::sort(vec_edges.begin(), vec_edges.end(), compare);

	int l = -1, r = n * (n - 1);
	while (r - l > 1) {
		int mid = l + (r - l) / 2;
		if (check(mid, n))
			r = mid;
		else
			l = mid;
	}

	if (n != 1)
		std::cout << edges[vec_edges[l].first][vec_edges[l].second];
	else
		std::cout << "0\n";
	return 0; 
}
