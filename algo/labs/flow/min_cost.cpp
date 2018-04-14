#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#define INF 2000000000000000000LL

struct edge {
	int a, b;
	int64_t c, w, f;
	edge(int a, int b, int64_t c, int64_t w) : a(a), b(b), c(c), w(w), f(0) {}
};

std::vector<edge> edges;
std::vector<std::vector<int>> g;
int n, m;

void add_edge(int a, int b, int64_t c, int64_t w) {
	g[a].push_back((int)edges.size());
	edges.push_back(edge(a, b, c, w));

	g[b].push_back((int)edges.size());
	edges.push_back(edge(b, a, 0, -w));
}

std::vector<int64_t> d;
std::vector<int> p, used;
bool dijkstra(int start, int end) {
	for (int i = 0; i < n; i++)
		d[i] = INF;
	memset(p.data(), -1, sizeof(p[0]) * p.size());
	memset(used.data(), 0, sizeof(used[0]) * used.size());
	
	d[start] = 0;
	for (int i = 0; i < n; i++) {
		int min_v = -1;
		for (int j = 0; j < n; j++) {
			if (!(used[j] == 1) && (min_v == -1 || d[j] < d[min_v]))
				min_v = j;
		}
		if (d[min_v] == INF)
			break;
		used[min_v] = 1;

		for (auto to = g[min_v].begin(); to != g[min_v].end(); ++to) {
			if (edges[*to].c - edges[*to].f > 0 && d[min_v] + edges[*to].w < d[edges[*to].b]) {
				d[edges[*to].b] = d[min_v] + edges[*to].w;
				p[edges[*to].b] = *to;
			}
		}
	}
	return d[end] != INF;
}

int64_t min_flow(int start, int end) {
	int64_t flow = 0;
	int64_t cost = 0;
	d.resize(n);
	p.resize(n);
	used.resize(n);

	while (dijkstra(start, end)) {
		int cur = end;
		int64_t cur_flow = INF;
		while (cur != start) {
			int prev = cur;
			cur = edges[p[cur]].a;
			cur_flow = std::min(cur_flow, edges[p[prev]].c - edges[p[prev]].f);
		}
		flow += cur_flow;
		cur = end;
		while (cur != start) {
			int prev = cur;
			cur = edges[p[cur]].a;
			edges[p[prev]].f += cur_flow;
			edges[p[prev] + (p[prev] % 2 == 0 ? 1 : -1)].f -= cur_flow;
			cost += cur_flow * edges[p[prev]].w;
		}
	}

	return cost;
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::cin >> n >> m;

	g.resize(n);
	for (int i = 0, a, b; i < m; i++) {
		int64_t c, w;
		std::cin >> a >> b >> c >> w;
		add_edge(a - 1, b - 1, c, w);
	}

	std::cout << min_flow(0, n - 1);
	return 0;
}
