#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <string.h>
std::string file_name = "matching";

std::vector<std::vector<int>> g;
std::vector<int> match, match_l;
std::vector<int> used;

bool find_add_path(int cur) {
	if (used[cur])
		return false;

	used[cur] = true;
	for (const auto &to : g[cur]) {
		if (match[to] == -1 || find_add_path(match[to])) {
			match[to] = cur;
			match_l[cur] = to;
			return true;
		}
	}
	return false;
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
	std::vector<std::pair<int, int>> vertex_w;
	for (int i = 0; i < n; i++) {
		int w;
		std::cin >> w;
		vertex_w.emplace_back(w, i);
	}

	std::sort(vertex_w.begin(), vertex_w.end(), std::greater<std::pair<int, int>>());
	g.resize(n);
	for (int i = 0; i < n; i++) {
		int m;
		std::cin >> m;
		for (int j = 0; j < m; j++) {
			int to;
			
			std::cin >> to;
			g[i].push_back(to - 1);
		}
	}

	match.resize(n, -1);
	match_l.resize(n, -1);
	used.resize(n);
	for (int i = 0; i < n; i++) {
		memset(used.data(), 0, used.size() * sizeof(used[0]));
		find_add_path(vertex_w[i].second);
	}
	for (int i = 0; i < n; i++) {
		std::cout << match_l[i] + 1 << " ";
	}
}
