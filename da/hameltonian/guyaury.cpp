#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <deque>
std::string file_name = "guyaury";
std::vector<std::vector<bool>> g;

std::deque<int> cycle;
std::vector<std::set<int>> in_e, out_e;

std::vector<int> used;
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;

	used.resize(n);
	g.resize(n);
	for (int i = 0; i < n; i++)
		g[i].resize(n);

	std::string str;
	for (int i = 1; i < n; i++) {
		std::cin >> str;
		for (int j = 0; j < i; j++) {
			bool flag = (str[j] == '1');
			g[i][j] = flag;
			g[j][i] = !flag;

			if (flag) {
				in_e[j].insert(i);
				out_e[i].insert(j);
			}
			else {
				out_e[j].insert(i);
				in_e[i].insert(j);
			}
		}
	}

	int begin = 0;
	cycle.push_back(begin);

	bool flag = false;
	for (auto &a : out_e[begin]) {
		for (auto &b : out_e[a])
			if (g[b][begin]) {
				cycle.push_back(a);
				cycle.push_back(b);

				used[0] = 1;
				used[a] = 2;
				used[b] = 3;
				flag = true;
				break;
			}
		if (flag)
			break;
	}

	while (cycle.size() != n) {
		flag = false;
		for (auto &c: cycle) {
			for (auto x = out_e[c].begin(); x != out_e[c].end(); ++x)
				for (auto y = out_e[*x].begin(); y != out_e[*x].end(); ++y)
					if (used[*y] != 0) {
						cycle.insert(, *x);
					}
		}

	}
}
