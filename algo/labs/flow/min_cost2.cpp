#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
static const int64_t INF = 1000000000000000LL;
static const int64_t BEGIN_FLOW = 1000000000000LL;

struct edge {
	int a, b;
	int64_t c, f;

	edge(int a, int b, int64_t c) : a(a), b(b), c(c), f(0) {}
};
std::vector<edge> edges;
std::vector<std::vector<int>> g;
std::vector<int> deep, ptr;

int n, m, s, t;
int64_t cur_max_flow;

bool layered_network() {
	memset(deep.data(), -1, deep.size() * sizeof(deep[0]));

	std::queue<int> q;
	q.push(s);
	deep[s] = 0;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (auto to = g[cur].begin(); to != g[cur].end(); ++to) {
			if (deep[edges[*to].b] == -1 && (edges[*to].c - edges[*to].f) >= cur_max_flow) {
				deep[edges[*to].b] = deep[cur] + 1;
				q.push(edges[*to].b);
			}
		}
	}
	return deep[t] != -1;
}

int64_t find_block(int cur, int64_t flow) {
	if (flow == 0) return 0;
	if (cur == t) return flow;
	if (flow < cur_max_flow) return 0;

	for (; ptr[cur] != (int)g[cur].size(); ++ptr[cur]) {
		int ind_e = g[cur][ptr[cur]];
		if (deep[edges[ind_e].b] != deep[cur] + 1) continue;

		int64_t pushed = find_block(edges[ind_e].b, std::min(flow, edges[ind_e].c - edges[ind_e].f));
		if (pushed != 0) {
			edges[ind_e].f += pushed;
			edges[ind_e ^ 1].f -= pushed;
			return pushed;
		}
	}
	return 0;
}

int64_t dinic() {
	int64_t flow = 0;
	cur_max_flow = BEGIN_FLOW;
	while (cur_max_flow > 0) {
		while (true) {
			if (!layered_network()) break;

			memset(ptr.data(), 0, ptr.size() * sizeof(ptr[0]));
			while (int64_t cur_flow = find_block(s, INF))
				flow += cur_flow;
		}
		cur_max_flow /= 2;
	}
	return flow;
}

std::vector<bool> reach_v;
void dfs(int cur) {
	reach_v[cur] = true;

	for (auto e = g[cur].begin(); e != g[cur].end(); ++e)
		if (edges[*e].f < edges[*e].c && !reach_v[edges[*e].b])
			dfs(edges[*e].b);
}

void add_edge(int a, int b, int64_t cost) {
	g[a].push_back((int)edges.size());
	edges.push_back(edge(a, b, cost));

	g[b].push_back((int)edges.size());
	edges.push_back(edge(b, a, 0));
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
	for (int i = 0, a, b; i < m; i++) {
		int64_t cost;
		std::cin >> a >> b >> cost;
		a--; b--;

		add_edge(a, b, cost);
		add_edge(b, a, cost);
	}

	s = 0;
	t = n - 1;
	dinic();

	reach_v.resize(n, false);
	dfs(s);
	int num_a = 0;
	for (int i = 0; i < n; i++)
		if (reach_v[i])
			num_a++;

	std::cout << num_a << std::endl;
	for (int i = 0; i < n; i++)
		if (reach_v[i])
			std::cout << i + 1 << " ";

	return 0;
}