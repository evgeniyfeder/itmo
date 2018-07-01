#include <iostream>
#include <vector>
#include <list>
std::string file_name = "cond";

std::vector<std::vector<int>> g, reverse_g;
std::vector<uint32_t> was;
std::list<uint32_t> result;

void topsort(uint32_t cur) {
	was[cur] = 1;

	for (size_t to = 0; to < g[cur].size(); to++) {
		if (was[g[cur][to]] == 0)
			topsort(g[cur][to]);
	}
	result.push_front(cur);
}

std::vector<uint32_t> companents;
void make_component(uint32_t comp, uint32_t vert) {
	was[vert] = 1;
	companents[vert] = comp;
	for (size_t to = 0; to < reverse_g[vert].size(); to++) {
		if (was[reverse_g[vert][to]] == 0)
			make_component(comp, reverse_g[vert][to]);
	}
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
	reverse_g.resize(n);
	for (size_t i = 0; i < m; ++i) {
		uint32_t from, to;
		std::cin >> from >> to;
		g[from - 1].push_back(to - 1);
		reverse_g[to - 1].push_back(from - 1);
	}

	was.resize(n);
	for (uint32_t i = 0; i < n; i++) {
		if (was[i] == 0)
			topsort(i);
	}

	companents.resize(n);
	for (uint32_t i = 0; i < n; i++) {
		was[i] = 0;
	}

	uint32_t cur_comp = 1;
	for (auto i = result.begin(); i != result.end(); ++i) {
		if (was[*i] == 0)
			make_component(cur_comp++, *i);
	}

	std::cout << cur_comp - 1 << std::endl;
	for (uint32_t i = 0; i < n; i++)
		std::cout << companents[i] << " ";
	
	return 0;
}
