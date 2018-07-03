#include <iostream>
#include <vector>
#include <queue>

using segm_type = std::pair<int, int>;
std::vector<segm_type> edges;
std::vector<std::vector<int>> edges_g;

std::vector<int> coord;

bool segm_intersect(const segm_type &a, const segm_type &b) {
	return (coord[b.second] > coord[a.first] && coord[b.second] < coord[a.second] && coord[b.first] < coord[a.first]) ||
		(coord[a.second] > coord[b.first] && coord[a.second] < coord[b.second] && coord[a.first] < coord[b.first]);
}

std::vector<char> part;
bool check_bigraph() {
	bool is_bigraph = true;
	part.resize(edges_g.size(), 0);
	for (int i = 0; i < (int)edges_g.size(); i++) {
		if (part[i] == 0) {
			std::queue<int> q;
			q.push(i);
			part[i] = 1;
			
			while (!q.empty()) {
				int from = q.front();
				q.pop();
				for (int j = 0; j < (int)edges_g[from].size(); j++) {
					int to = edges_g[from][j];

					if (part[to] == 0) {
						part[to] = part[from] * (-1);
						q.push(to);
					}
					else {
						is_bigraph &= (part[to] != part[from]);
					}
				}
			}
		}
	}
	return is_bigraph;
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "rt", stdin);
	freopen("test.out", "wt", stdout);
#endif
	int n, m;
	std::cin >> n >> m;

	edges.resize(m);
	for (int i = 0, a, b; i < m; i++) {
		std::cin >> a >> b;
		edges[i] = std::make_pair(a - 1, b - 1);
	}

	coord.resize(n);
	for (int i = 0, x; i < n; i++) {
		std::cin >> x;
		coord[x - 1] = i;
	}

	for (int i = 0; i < m; i++) {
		if (coord[edges[i].first] > coord[edges[i].second])
			std::swap(edges[i].first, edges[i].second);
	}

	edges_g.resize(m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i != j && segm_intersect(edges[i], edges[j])) {
				edges_g[i].push_back(j);
			}
		}
	}
	
	if (check_bigraph()) {
		std::cout << "YES\n";

		for (int i = 0; i < n; i++) {
			std::cout << 2 * coord[i] << " " << 0 << " ";
		}
		std::cout << std::endl;

		for (int i = 0; i < m; i++) {
			std::cout << (coord[edges[i].first] + coord[edges[i].second])
				<< " " << abs(coord[edges[i].first] - coord[edges[i].second]) * part[i] << std::endl;
		}
	}
	else {
		std::cout << "NO";
	}
}
