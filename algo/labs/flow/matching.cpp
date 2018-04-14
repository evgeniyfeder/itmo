#include <stdio.h>
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

inline bool layered_network() {
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
inline int dinic() {
	int flow = 0;

	while (true) {
		if (!layered_network()) break;

		memset(ptr.data(), 0, ptr.size() * sizeof(ptr[0]));
		while (int cur_flow = find_block(s, INF))
			flow += cur_flow;
	}
	return flow;
}

inline void add_edge(int a, int b, int cost) {
	g[a].push_back((int)edges.size());
	edges.push_back(edge(a, b, cost));

	g[b].push_back((int)edges.size());
	edges.push_back(edge(b, a, 0));
}

std::vector<bool> used_dfs;
void dfs(int cur, bool is_right, const int n) {
	used_dfs[cur] = true;

	const int need_edges = (is_right == true ? 0 : 1);
	for (auto to = g[cur].begin(); to != g[cur].end(); ++to) {
		if (edges[*to].f == need_edges && 
			edges[*to].b != 0 && edges[*to].b != n
			&& !used_dfs[edges[*to].b])
			dfs(edges[*to].b, !is_right, n);
	}
}

int main() {
#ifdef _DEBUG 
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	int begin_n1, begin_n2, begin_m = -1;
	while (scanf("%d%d%d", &begin_n1, &begin_n2, &begin_m)) {

		if (begin_m == -1)
			break;

		n = begin_n1 + begin_n2 + 2;
		m = begin_m + 2 * (begin_n1 + begin_n2);

		g.resize(n);
		deep.resize(n);
		ptr.resize(n);
		for (int i = 0, a, b; i < begin_m; i++) {
			scanf("%d%d", &a, &b);
			add_edge(a, b + begin_n1, 1);
		}

		for (int i = 1; i <= begin_n1; i++) {
			add_edge(0, i, 1);
		}
		for (int i = begin_n1; i <= begin_n1 + begin_n2; i++) {
			add_edge(i, n - 1, 1);
		}
		s = 0;
		t = n - 1;
		dinic();

		std::vector<char> not_in_m(begin_n2, 0);
		for (int i = 0; i < begin_m; i++) {
			if (edges[2 * i].f == 1)
				not_in_m[edges[2 * i].b - begin_n1 - 1] = 1;
		}

		used_dfs.resize(n);
		for (int i = 0; i < begin_n2; i++) {
			if (not_in_m[i])
				dfs(begin_n1 + 1 + i, true, n);
		}

		std::vector<int> res;
		
		res.reserve(begin_n2);
		for (int i = begin_n1 + 1; i < n - 1; i++)
			if (used_dfs[i])
				res.push_back(i - begin_n1);

		int res_size = (int)res.size();
		printf("%d\n", res_size);
		for (auto i = res.begin(); i != res.end(); ++i)
			printf("%d ", *i);
		printf("\n");
		/*edges.clear();
		g.clear();
		deep.clear();
		ptr.clear();
		used_dfs.clear();*/
		begin_m = -1;
	}
	return 0;
}