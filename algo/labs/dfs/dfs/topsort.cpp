#include <iostream>
#include <vector>
#include <list>
std::string file_name = "topsort";

std::vector<std::vector<int>> g;
std::vector<uint32_t> was;
std::list<uint32_t> result;

bool topsort(uint32_t cur) {
	was[cur] = 1;

	bool res = false;
	for (size_t to = 0; to < g[cur].size(); to++) {
		if (was[g[cur][to]] == 0)
			res |= topsort(g[cur][to]);
		else if (was[g[cur][to]] == 1)
			return true;
	}

	was[cur] = 2;
	result.push_front(cur);
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
	for (size_t i = 0; i < m; ++i) {
		uint32_t from, to;
		std::cin >> from >> to;
		g[from - 1].push_back(to - 1);
	}
	
	was.resize(n);
	for (uint32_t i = 0; i < n; i++) {
		if (was[i] == 0)
			if (topsort(i)) {
				std::cout << "-1";
				return 0;
			}
	}
	
	for (std::list<uint32_t>::iterator it = result.begin(); it != result.end(); ++it)
		std::cout << *it + 1 << " ";
	return 0;
}
