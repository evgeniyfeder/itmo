#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
std::string file_name = "points";

typedef std::pair<uint32_t, int32_t> pair;
std::vector<std::vector<pair>> g;
std::vector<bool> used;
std::vector<uint32_t> d, up, result;

uint32_t dfs(uint32_t cur_vert, int32_t cur_edge, uint32_t cur_depth) {
	uint32_t min = cur_depth;
	used[cur_vert] = true;
	d[cur_vert] = cur_depth;
	bool is_point = false;
	int child_cnt = 0;
	for (auto to = g[cur_vert].begin(); to != g[cur_vert].end(); ++to) {
		if (!used[to->first]) {
			min = std::min(min, dfs(to->first, to->second, cur_depth + 1));
			is_point |= up[to->first] >= d[cur_vert];
			child_cnt++;
		}
		else if (cur_edge != to->second)
			min = std::min(min, d[to->first]);
	}
	if (cur_depth == 0 && child_cnt > 1)
		result.push_back(cur_vert + 1);
	else if (cur_depth != 0 && is_point)
		result.push_back(cur_vert + 1);
	up[cur_vert] = min;
	return min;	
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
	up.resize(n);
	d.resize(n);
	for (uint32_t i = 1; i <= m; i++) {
		uint32_t from, to;
		std::cin >> from >> to;
		g[from - 1].push_back(pair(to - 1, int32_t(i)));
		g[to - 1].push_back(pair(from - 1, int32_t(i)));
	}

	for (uint32_t i = 0; i < n; i++)
		if (!used[i])
			dfs(i, -1, 0);

	std::cout << result.size() << std::endl;
	std::sort(result.begin(), result.end());
	for (uint32_t i = 0; i < result.size(); i++) {
		std::cout << result[i] << " ";
	}
}