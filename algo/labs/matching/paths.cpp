#include <iostream>
#include <vector>
std::string file_name = "paths";

std::vector<std::vector<int>> g;
std::vector<int> match;
std::vector<int> used;

bool find_add_path(int cur) {
	if (used[cur])
		return false;

	used[cur] = true;
	for (const auto &to : g[cur]) {
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

	int n, m;
	std::cin >> n >> m;
	g.resize(n);
	match.resize(n, -1);

	for (int i = 0, a, b; i < m; i++) {
		std::cin >> a >> b;
		g[b - 1].push_back(a - 1);
	}

	used.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			used[j] = 0;
		find_add_path(i);
	}

	for (int j = 0; j < n; j++)
		used[j] = 0;

	int res = 0;
	for (int j = 0; j < n; j++) {
		if (used[j] || match[j] == -1)
			continue;

		bool flag = false;
		
		int next = j;
		while (match[next] != -1) {
			if (used[next]) {
				flag = true;
				break;
			}

			used[next] = true;
			next = match[next];
		}
		used[next] = true;

		if (!flag)
			res++;
	}
	for (int j = 0; j < n; j++) {
		if (!used[j])
			res++;
	}
	std::cout << res;
}
