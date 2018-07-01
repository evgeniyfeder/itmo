#include <iostream>
#include <vector>
std::string file_name = "components";

std::vector<std::vector<uint32_t>> g;
std::vector<bool> used;
std::vector<uint32_t> comp;

void dfs(uint32_t cur, uint32_t cur_comp) {
	used[cur] = true;
	comp[cur] = cur_comp;
	for (auto to = g[cur].begin(); to != g[cur].end(); ++to)
		if (!used[*to])
			dfs(*to, cur_comp);
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

	uint32_t n, m;
	std::cin >> n >> m;

	g.resize(n);
	used.resize(n);
	comp.resize(n);
	for (uint32_t i = 0; i < m; i++) {
		uint32_t from, to;
		std::cin >> from >> to;
		g[from - 1].push_back(to - 1);
		g[to - 1].push_back(from - 1);
	}

	uint32_t cur_comp = 1;
	for (uint32_t i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, cur_comp);
			cur_comp++;
		}
	}

	std::cout << cur_comp - 1 << std::endl;
	for (uint32_t i = 0; i < n; i++) {
		std::cout << comp[i] << " ";
	}
}
