#include <iostream>
#include <vector>
#include <algorithm>

const int64_t INF = INT64_MAX / 4;
const int not_edge = 1000000000;

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;

	std::vector<std::vector<int>> g(n);
	for (int i = 0; i < n; i++) {
		g[i].resize(n);
		for (int j = 0; j < n; j++)
			std::cin >> g[i][j];
	}

	
	std::vector<int64_t> d(n, 0);
	std::vector<int> p(n, -1);

	for (int i = 0; i < n; i++) {
		for (int from = 0; from < n; from++)
			for (int to = 0; to < n; to++) {
				if (g[from][to] != not_edge && d[to] > d[from] + g[from][to]) {
					d[to] = d[from] + g[from][to];
					p[to] = from;
				}
			}
	}

	bool exit = false;
	std::vector<int> res;
	for (int from = 0; from < n; from++) {
		for (int to = 0; to < n; to++) {
			if (g[from][to] != not_edge && d[to] > d[from] + g[from][to]) {
				for (int i = 0; i < n; i++)
					to = p[to];
				from = to;

				res.push_back(to);
				while (from != p[to]) {
					to = p[to];
					res.push_back(to);
				}
				res.push_back(p[to]);
				std::reverse(res.begin(), res.end());
				
				exit = true;
				break;
			}
		}
		if (exit)
			break;
	}

	if (res.empty()) {
		std::cout << "NO";
	}
	else {
		std::cout << "YES\n" << res.size() << std::endl;

		for (auto i : res) {
			std::cout << i + 1 << " ";
		}
	}
}
