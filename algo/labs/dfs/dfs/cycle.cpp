#include <iostream>
#include <vector>
#include <list>
std::string file_name = "cycle";

std::vector<std::vector<int>> g;
std::vector<uint32_t> was;
std::list<uint32_t> result;

typedef std::pair<bool, int32_t> res_type;
res_type dfs(int32_t cur) {
	was[cur] = 1;

	for (size_t to = 0; to < g[cur].size(); to++) {
		if (was[g[cur][to]] == 0) {
			res_type res = dfs(g[cur][to]);

			if (res.first) {
				if (res.second != -1)
					result.push_front(cur);

				if (cur != res.second)
					return res;
				else
					return res_type(true, -1);
			}
		}
		else if (was[g[cur][to]] == 1) {
			result.push_front(cur);
			return res_type(true, g[cur][to]);
		}
	}

	was[cur] = 2;
	
	return res_type(false, 0);
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

	int32_t n, m;
	std::cin >> n >> m;

	g.resize(n);
	for (int32_t i = 0; i < m; ++i) {
		uint32_t from, to;
		std::cin >> from >> to;
		g[from - 1].push_back(to - 1);
	}

	was.resize(n);
	for (int32_t i = 0; i < n; i++) {
		if (was[i] == 0) {
			res_type res = dfs(i);
			if (res.first) {
				std::cout << "YES" << std::endl;
				for (auto e = result.begin(); e != result.end(); ++e)
					std::cout << *e + 1 << " ";
				return 0;
			}
		}
	}
	std::cout << "NO" << std::endl;
	return 0;
}
