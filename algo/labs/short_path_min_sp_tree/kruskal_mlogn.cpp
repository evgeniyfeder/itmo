#include <iostream>
#include <vector>
#include <algorithm>

const int max_n = 20000, max_m = 100010;
struct edge {
	int a = 0, w = 0, b = 0;
};
bool operator<(const edge &a, const edge &b) {
	return a.w < b.w;
}

edge g[max_m];
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
inline int build_tree(int begin) {
	for (int i = 0; i < n; i++)
		dsu[i] = i;

	int num = 0, max_edge = 0;
	for (int i = begin; i < m; i++) {
		if (dsu_get(g[i].a) != dsu_get(g[i].b)) {
			num++;
			max_edge = i;
			dsu_union(g[i].a, g[i].b);
		}
	}
	return (num == n - 1) ? g[max_edge].w - g[begin].w : INT32_MAX;
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &g[i].a, &g[i].b, &g[i].w);
		g[i].a--;
		g[i].b--;
	}

	std::sort(g, g + m);

	int mm_dif = INT32_MAX;
	for (int i = 0; i <= m - n + 1; i++) {
		mm_dif = std::min(mm_dif, build_tree(i));
	}
	if (mm_dif != INT32_MAX)
		printf("YES\n%d", mm_dif);
	else
		printf("NO");
}
