#include <iostream>
#include <vector>
#include <queue>
#include <set>
using my_pair = std::pair<int64_t, int>;
const int64_t INF = INT64_MAX / 4;

std::vector<std::vector<my_pair>> g;
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n, m;
	std::cin >> n >> m;

	g.resize(n);
	for (int i = 0, a, b, w; i < m; i++) {
		std::cin >> a >> b >> w;
		g[a - 1].push_back(my_pair(w, b - 1));
		g[b - 1].push_back(my_pair(w, a - 1));
	}

	std::vector<uint64_t> d(n);
	std::vector<bool> used(n);
	for (int i = 0; i < n; i++) {
		d[i] = INF;
		used[i] = false;
	}

	int begin = 0;
	d[begin] = 0;

	std::set<my_pair> s;
	s.insert(my_pair(d[begin], begin));
	while (!s.empty()) {
		int cur = s.begin()->second;
		s.erase(s.begin());

		for (auto to : g[cur]) {
			if (d[to.second] > d[cur] + to.first) {
				s.erase(my_pair(d[to.second], to.second));
				d[to.second] = d[cur] + to.first;
				s.insert(my_pair(d[to.second], to.second));
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (d[i] != INF)
			std::cout << d[i];
		else
			std::cout << "-1";
		std::cout << " ";
	}
}
