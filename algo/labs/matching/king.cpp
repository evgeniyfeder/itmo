#include <iostream>
#include <vector>
#include <list>
std::string file_name = "king";

std::vector<std::vector<uint64_t>> g, reverse_g;
std::vector<uint32_t> was, match;
std::list<uint64_t> result;

void topsort(uint64_t cur) {
	was[cur] = 1;

	for (size_t to = 0; to < g[cur].size(); to++) {
		if (was[g[cur][to]] == 0)
			topsort(g[cur][to]);
	}
	result.push_front(cur);
}

std::vector<uint32_t> companents;
void make_component(uint32_t comp, uint64_t vert) {
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

	size_t n;
	std::cin >> n;

	g.resize(2 * n);
	reverse_g.resize(2 * n);
	for (size_t i = 0; i < n; ++i) {
		uint32_t num;
		std::cin >> num;
		for (size_t j = 0; j < num; j++) {
			uint32_t to;
			std::cin >> to;
			g[n + to - 1].push_back(i);
			reverse_g[i].push_back(n + to - 1);
		}

	}
	for (size_t i = 0; i < n; i++) {
		uint32_t king;
		std::cin >> king;

		g[i].push_back(n + king - 1);
		reverse_g[n + king - 1].push_back(i);

		for (auto it = g[n + king - 1].begin(); it != g[n + king - 1].end(); ++it)
			if (*it == i) {
				g[n + king - 1].erase(it);
				break;
			}

		for (auto it = reverse_g[i].begin(); it != reverse_g[i].end(); ++it)
			if (*it == n + king - 1) {
				reverse_g[i].erase(it);
				break;
			}
	}
	n = 2 * n;
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

	/*std::cout << cur_comp - 1 << std::endl;
	for (uint32_t i = 0; i < n; i++)
		std::cout << companents[i] << " ";*/

	n = n / 2;
	for (size_t i = 0; i < n; i++) {
		int num = 0;

		for (auto man : reverse_g[i])
			if (companents[man] == companents[i])
				num++;

		std::cout << num + 1 << " ";
		std::cout << g[i][0] - n + 1 << " ";
		
		for (auto man : reverse_g[i])
			if (companents[man] == companents[i])
				std::cout << man - n + 1 << ' ';
		std::cout << std::endl;
	}
	return 0;
}
