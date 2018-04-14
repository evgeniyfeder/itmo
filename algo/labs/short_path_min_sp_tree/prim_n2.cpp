#include <iostream>
#include <vector>
#include <cmath>

using ppair = std::pair<int, int>;
using min_pair = std::pair<double, int>;
std::vector<std::vector<double>> g;
std::vector<ppair> points;
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;
	for (int i = 0, a, b; i < n; i++) {
		std::cin >> a >> b;
		points.push_back(ppair(a, b));	
	}

	g.resize(n);
	for (int i = 0; i < n; i++) {
		g[i].resize(n);
		for (int j = 0; j < n; j++) {
			g[i][j] = sqrt((points[i].first - points[j].first) * (points[i].first - points[j].first)
				+ (points[i].second - points[j].second) * (points[i].second - points[j].second));
		}
		
	}

	std::vector<double> min_edge(n, 10000000);
	min_edge[0] = 0;
	double sum = 0;
	std::vector<bool> used(n);
	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j = 0; j < n; j++) {
			if (!used[j] && (v == -1 || min_edge[j] < min_edge[v]))
				v = j;
		}
		used[v] = true;
		sum += min_edge[v];

		for (int to = 0; to < n; to++) {
			if (g[v][to] < min_edge[to])
				min_edge[to] = g[v][to];
		}
	}

	std::cout.precision(15);
	std::cout << sum;
}
