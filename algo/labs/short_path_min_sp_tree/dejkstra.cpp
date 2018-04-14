#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> g;
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;

	int begin, end;
	std::cin >> begin >> end;

	g.resize(n);
	for (int i = 0; i < n; i++) {
		g[i].resize(n);
		for (int j = 0; j < n; j++) {
			std::cin >> g[i][j];
		}
	}

	std::vector<uint64_t> d(n);
	std::vector<bool> used(n);
	for (int i = 0; i < n; i++) {
		d[i] = INT64_MAX;
		used[i] = false;
	}

	
	d[begin - 1] = 0;

	for (int i = 0; i < n; i++) {
		int cur = -1;
		for (int j = 0; j < n; j++)
			if (!used[j] && (cur == -1 || d[cur] > d[j])) {
				cur = j;
			}
		if (d[cur] == INT64_MAX)
			break;

		used[cur] = true;
		for (int to = 0; to < n; ++to) {
			if (g[cur][to] != -1 && d[to] > d[cur] + g[cur][to]) {
				d[to] = d[cur] + g[cur][to];
			}
		}
	}

	if (d[end - 1] != INT64_MAX)
		std::cout << d[end - 1];
	else
		std::cout << "-1";
}
