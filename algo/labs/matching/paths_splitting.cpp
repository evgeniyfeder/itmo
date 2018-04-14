#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <list>
std::string file_name = "paths";

static const int max_n = 20010;
std::vector<std::list<int>> g;
//int g[max_n][max_n];
std::vector<int> degree, added_edges;
//int degree[max_n];
//int added_edges[max_n];
int n, m;

std::vector<int> result;
/*void dfs(int cur, bool need_added) {
	for (int to = 0; to < n; to++) {
		if (!need_added && added_edges[cur] == to)
			continue;

		if (g[cur][to] != 0) {
			g[cur][to]--;
			g[to][cur]--;

			dfs(to, need_added);
		}
	}
	result.push_back(cur);
}*/

void find(int begin, bool need_added) {
	std::stack<int> s;
	s.push(begin);
	while (!s.empty()) {
		int cur = s.top();

		for (auto it = g[cur].begin(); it != g[cur].end();) {
			if (!need_added && added_edges[cur] == *it)
				continue;
			int to = *it;
			it = g[cur].erase(it);
			
			for (auto it_to = g[to].begin(); it_to != g[to].end(); ++it_to)
				if (*it_to == cur) {
					g[to].erase(it_to);
					break;
				}

			s.push(to);
			break;
		}
		if (cur == s.top()) {
			s.pop();
			result.push_back(cur);
		}
	}
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	std::cin >> n >> m;
	degree.resize(n);
	added_edges.resize(n, -1);
	g.resize(n);
	for (int i = 0, a, b; i < m; i++) {
		std::cin >> a >> b;
		g[a - 1].push_back(b - 1);
		g[b - 1].push_back(a - 1);
		degree[a - 1]++;
		degree[b - 1]++;
	}

	int prev = -1, num_odd = 0;
	for (int i = 0; i < n; i++)
		if (degree[i] % 2 == 1)
			num_odd++;

	int tmp = num_odd;
	int start = 0;
	for (int i = 0; i < n; i++) {
		if (num_odd > 2 && degree[i] % 2 == 1) {
			if (prev == -1)
				prev = i;
			else {
				g[prev].push_back(i);
				g[i].push_back(prev);
				num_odd -= 2;
				added_edges[prev] = i;
				added_edges[i] = prev;
				prev = -1;
			}
		}
		else if (num_odd <= 2 && degree[i] % 2 == 1)
			start = i;
	}

	if (tmp <= 2) {
		find(start, false);
		
		std::cout << 1 << std::endl;
		for (int i = 0; i < (int)result.size(); i++)
			std::cout << result[i] + 1 << " ";
	}
	else {
		find(start, true);
		std::cout << ((tmp % 2 == 0) ? tmp / 2 : tmp / 2 + 1) << std::endl;

		for (int i = 0; i < (int)result.size() - 1; i++) {
			std::cout << result[i] + 1 << " ";
			if (added_edges[result[i]] == result[i + 1]) {
				added_edges[result[i]] = -1;
				added_edges[result[i + 1]] = -1;
				std::cout << std::endl;
			}
		}
		std::cout << result[result.size() - 1] + 1;
	}
}
