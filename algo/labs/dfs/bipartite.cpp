#include <iostream>
#include <vector>
std::string file_name = "bipartite";


std::vector<std::vector<int>> g;
enum dfs_type { EMPTY, RED, BLUE };
std::vector<dfs_type> was;

dfs_type next_color(dfs_type cur) {
	return cur == BLUE ? RED : BLUE;
}
bool dfs(uint32_t cur_vert, dfs_type cur_color) {
	was[cur_vert] = cur_color;
	bool res = false;
	for (auto to = g[cur_vert].begin(); to != g[cur_vert].end(); ++to) {
		if (was[*to] == EMPTY)
			res |= dfs(*to, next_color(cur_color));
		else if (was[*to] == cur_color)
			return true;
	}
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
	was.resize(n);
	for (size_t i = 0; i < m; ++i) {
		uint32_t from, to;
		std::cin >> from >> to;
		g[from - 1].push_back(to - 1);
		g[to - 1].push_back(from - 1);
	}

	const dfs_type begin = RED;
	for (uint32_t i = 0; i < n; i++)
		if (was[i] == EMPTY)
			if (dfs(i, begin)) {
				std::cout << "NO" << std::endl;
				return 0;
			}
	std::cout << "YES" << std::endl;
	return 0;
}
