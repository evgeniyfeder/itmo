#include <iostream>
#include <vector>
#include <algorithm>
std::string file_name = "shortpath";

typedef std::pair<int, int> pair_to;

std::vector<std::vector<pair_to>> g;
std::vector<int64_t> result;
std::vector<bool> used;
const int64_t INF = INT64_MAX / 2;

int64_t dfs(int cur, const int end) {
	if (used[cur])
		return result[cur];
	
	used[cur] = true;
	if (cur == end)
		return (result[cur] = 0);

	int64_t min = INF;
	for (auto to = g[cur].begin(); to != g[cur].end(); ++to) {
		int64_t res = dfs(to->first, end);
		if (res != INF)
			min = std::min(res + to->second, min);
	}
	result[cur] = min;
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

	int n, m, s, t;
	std::cin >> n >> m >> s >> t;

	g.resize(n);
	for (int i = 0; i < m; i++) {
		int from, to, w;
		std::cin >> from >> to >> w;
		g[from - 1].push_back(pair_to(to - 1, w));
	}

	result.resize(n);
	used.resize(n);
	for (int i = 0; i < n; i++)
		result[i] = INF;
	
	int64_t res = dfs(s - 1, t - 1);
	if (res != INF)
		std::cout << res;
	else
		std::cout << "Unreachable";
}
