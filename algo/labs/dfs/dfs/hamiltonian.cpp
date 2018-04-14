#include <iostream>
#include <vector>
#include <algorithm>
std::string file_name = "hamiltonian";

std::vector<std::vector<int>> g;
std::vector<uint32_t> result, in_cnt;
std::vector<bool> used;

uint32_t dfs(int cur) {
	if (used[cur])
		return result[cur];

	used[cur] = true;
	uint32_t res = 1;
	for (auto to = g[cur].begin(); to != g[cur].end(); ++to) {
		res = std::max(dfs(*to) + 1, res);
	}
	result[cur] = res;
	return res;
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

	size_t n, m;
	std::cin >> n >> m;

	g.resize(n);
	in_cnt.resize(n);
	for (size_t i = 0; i < m; ++i) {
		uint32_t from, to;
		std::cin >> from >> to;
		g[from - 1].push_back(to - 1);
		in_cnt[to - 1]++;
	}

	int start = -1;
	for (size_t i = 0; i < n; i++) {
		if (in_cnt[i] == 0)
			start = i;
	}

	used.resize(n);
	result.resize(n);
	std::cout << ((dfs(start) == n) ? "YES" : "NO");
	return 0;
}
