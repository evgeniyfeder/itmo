#include <iostream>
#include <vector>
std::string file_name = "matching";

std::vector<std::vector<int>> g;
std::vector<int> match;
std::vector<int> used;

bool find_add_path(int cur) {
	if (used[cur])
		return false;

	used[cur] = true;
	for (const auto &to: g[cur]) {
		if (match[to] == -1 || find_add_path(match[to])) {
			match[to] = cur;
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
	
	int left, right, edges, first;
	std::cin >> left >> right >> edges;

	if (left < right) {
		first = left;
		
		g.resize(left);
		match.resize(right, -1);

		for (int i = 0, a, b; i < edges; i++) {
			std::cin >> a >> b;
			g[b - 1].push_back(a - 1);
		}
	}
	else {
		first = right;

		g.resize(right);
		match.resize(left, -1);

		for (int i = 0, a, b; i < edges; i++) {
			std::cin >> a >> b;
			g[b - 1].push_back(a - 1);
		}
	}

	used.resize(first);
	for (int i = 0; i < first; i++) {
		for (int j = 0; j < first; j++)
			used[j] = 0;
		find_add_path(i);
	}

	int res = 0;
	for (const auto &m : match)
		if (m != -1)
			res++;
	std::cout << res;
}
