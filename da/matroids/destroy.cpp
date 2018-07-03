#include <iostream>
#include <vector>
#include <algorithm>
std::string file_name = "destroy";

const int max_n = 60000, max_m = 100010;
struct edge {
	int a = 0, b = 0;
	uint64_t w = 0;
};
bool operator<(const edge &a, const edge &b) {
	return a.w > b.w;
}

std::pair<edge, int> g[max_m];
int dsu[max_n];
int dsu_get(int v) {
	return (v == dsu[v]) ? v : (dsu[v] = dsu_get(dsu[v]));
}

inline void dsu_union(int a, int b) {
	a = dsu_get(a);
	b = dsu_get(b);
	if (rand() & 1)
		std::swap(a, b);
	if (a != b)
		dsu[a] = b;
}

int n, m;
uint64_t s;
char used[max_m];
inline uint64_t build_tree(int begin) {
	for (int i = 0; i < n; i++)
		dsu[i] = i;

	int num = 0, max_edge = 0;
	uint64_t res = 0;
	for (int i = begin; i < m; i++) {
		if (dsu_get(g[i].first.a) != dsu_get(g[i].first.b)) {
			num++;
			max_edge = i;
			used[i] = 1;
			res += g[i].first.w;
			dsu_union(g[i].first.a, g[i].first.b);
		}
	}
	return res;
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	scanf("%d%d%I64d", &n, &m, &s);
	uint64_t sum_edges = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%I64d", &g[i].first.a, &g[i].first.b, &g[i].first.w);
		g[i].first.a--;
		g[i].first.b--;
		g[i].second = i;
		sum_edges += g[i].first.w;
	}

	std::sort(g, g + m);

	uint64_t mm_dif = build_tree(0);
	int cur = 0;
	while (mm_dif + s < sum_edges) {
		if (used[cur] == 0) {
			used[cur] = 1;
			mm_dif += g[cur].first.w;
		}
		cur++;
	}

	std::vector<std::pair<edge, int>> res;
	for (int i = 0; i < m; i++) {
		if (used[i] == 0) {
			res.push_back(g[i]);
		}
	}

	std::sort(res.begin(), res.end(), [](const std::pair<edge, int> &a, const std::pair<edge, int> &b) {return a.second < b.second; });

	printf("%u\n", res.size());
	for (int i = 0; i < res.size(); i++) {
		printf("%d ", res[i].second + 1);
	}
}