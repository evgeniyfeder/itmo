#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define INF 2000000000

struct edge {
	int a, b, c, f;

	edge(int a, int b, int c) : a(a), b(b), c(c), f(0) {}
};
std::vector<edge> edges;
std::vector<std::vector<int>> g;
std::vector<int> deep, ptr;

int n, m, s, t;

bool layered_network() {
	memset(deep.data(), -1, deep.size() * sizeof(deep[0]));

	std::queue<int> q;
	q.push(s);
	deep[s] = 0;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (auto to = g[cur].begin(); to != g[cur].end(); ++to) {
			if (deep[edges[*to].b] == -1 && edges[*to].f < edges[*to].c) {
				deep[edges[*to].b] = deep[cur] + 1;
				q.push(edges[*to].b);
			}
		}
	}
	return deep[t] != -1;
}

int find_block(int cur, int flow) {
	if (flow == 0) return 0;
	if (cur == t) return flow;

	for (; ptr[cur] != (int)g[cur].size(); ++ptr[cur]) {
		int ind_e = g[cur][ptr[cur]];
		if (deep[edges[ind_e].b] != deep[cur] + 1) continue;
		
		int pushed = find_block(edges[ind_e].b, std::min(flow, edges[ind_e].c - edges[ind_e].f));
		if (pushed) {
			edges[ind_e].f += pushed;
			edges[ind_e ^ 1].f -= pushed;
			return pushed;
		}
	}
	return 0;
}
int dinic() {
	int flow = 0;

	while (true) {
		if (!layered_network()) break;

		memset(ptr.data(), 0, ptr.size() * sizeof(ptr[0]));
		while (int cur_flow = find_block(s, INF))
			flow += cur_flow;
	}
	return flow;
}

int main() {
#ifdef _DEBUG 
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	std::cin >> n >> m;

	g.resize(n);
	deep.resize(n);
	ptr.resize(n);
	for (int i = 0, a, b, cost; i < m; i++) {
		std::cin >> a >> b >> cost;
		a--; b--;

		g[a].push_back((int)edges.size());
		edges.push_back(edge(a, b, cost));
		
		g[b].push_back((int)edges.size());
		edges.push_back(edge(b, a, 0));
	}
	s = 0;
	t = n - 1;
	std::cout << dinic();

	return 0;
}