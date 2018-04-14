#include <iostream>
#include <vector>
#include <algorithm>

struct edge {
	int from, to;
	int64_t w;
	edge(int from, int to, int64_t w) : from(from), to(to), w(w) {}
};

std::vector<edge> g_edge;
std::vector<std::vector<int>> g;
const int64_t INF = 8000000000000000000ll;
const int64_t NEGINF = -8000000000000000000ll;


void dfs(int cur, std::vector<bool> &used) {
	used[cur] = true;
	for (auto to : g[cur]) {
		if (!used[to])
			dfs(to, used);
	}
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n, m, start;
	std::cin >> n >> m >> start;
	start--;

	g.resize(n);

	
	for (int i = 0, from, to; i < m; i++) {
		int64_t w;
		std::cin >> from >> to >> w;
		from--; to--;

		g[from].push_back(to);
		g_edge.push_back(edge(from, to, w));
	}

	std::vector<bool> existed(n);
	dfs(start, existed);

	std::vector<int64_t> d(n, INF + 100000000000000000ll);
	d[start] = 0;
	for (int i = 0; i < n; i++)
		for (auto e : g_edge) {
			if (existed[e.to] && d[e.from] < INF && d[e.to] > d[e.from] + e.w) {
				d[e.to] = std::max(NEGINF, d[e.from] + e.w);
			}
		}

	std::vector<int64_t> last_move(n);
	for (int i = 0; i < n; i++)
		last_move[i] = d[i];

	for (auto e : g_edge)
		if (existed[e.to] && last_move[e.from] < INF && last_move[e.to] > last_move[e.from] + e.w) {
			last_move[e.to] = last_move[e.from] + e.w;
		}

	std::vector<bool> used(n, false);
	for (int i = 0; i < n; i++)
		if (existed[i] && last_move[i] != d[i])
			dfs(i, used);

	for (int i = 0; i < n; i++) {
		if (d[i] >= INF)
			std::cout << "*";
		else if (used[i])
			std::cout << "-";
		else
			std::cout << d[i];
		std::cout << std::endl;
	}
}
