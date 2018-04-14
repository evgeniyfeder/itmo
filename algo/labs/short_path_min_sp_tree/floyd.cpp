#include <iostream>
#include <vector>
#include <algorithm>

using my_pair = std::pair<int, int64_t>;

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<my_pair>> g(n);
	std::vector<std::vector<int64_t>> d(n);
	for (int i = 0; i < n; i++) {
		d[i].resize(n);
		for (int j = 0; j < n; j++)
			d[i][j] = INT64_MAX / 4;
		d[i][i] = 0;
	}

	long long w;
	for (int i = 0, a, b; i < m; i++) {
		std::cin >> a >> b >> w;
		g[a - 1].push_back(my_pair(b - 1, w));

		d[a - 1][b - 1] = std::min(d[a - 1][b - 1], w);
	}

	for (int i = 0; i < n; i++)
		for (int v = 0; v < n; v++)
			for (int u = 0; u < n; u++) {
				d[v][u] = std::min(d[v][u], d[v][i] + d[i][u]);
			}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			std::cout << d[i][j] << " ";
		std::cout << "\n";
	}
}
