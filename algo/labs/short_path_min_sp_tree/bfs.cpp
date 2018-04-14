#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> g;
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m;
	std::cin >> n >> m;
	g.resize(n);
	for (int i = 0, from, to; i < m; i++) {
		std::cin >> from >> to;
		g[from - 1].push_back(to - 1);
		g[to - 1].push_back(from - 1);
	}

	std::vector<int> d(n);
	for (int i = 0; i < n; i++)
		d[i] = -1;
	int begin_ind = 0;

	std::queue<int> q;
	q.push(begin_ind);
	d[begin_ind] = 0;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (auto to : g[cur]) {
			if (d[to] == -1) {
				d[to] = d[cur] + 1;
				q.push(to);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		std::cout << d[i] << ' ';
	}
}
