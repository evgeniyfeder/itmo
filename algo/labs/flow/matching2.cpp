#include <stdio.h>
#include <vector>
#include <string.h>
int n, m;

std::vector<std::vector<int>> g;
std::vector<int> match, match_l;
std::vector<int> used;

bool find_add_path(int cur) {
	if (used[cur])
		return false;

	used[cur] = true;
	for (const auto &to : g[cur]) {
		if (match[to] == -1) {
			match[to] = cur;
			match_l[cur] = to;
			return true;
		}
	}

	for (const auto &to : g[cur]) {
		if (find_add_path(match[to])) {
			match[to] = cur;
			match_l[cur] = to;
			return true;
		}
	}
	return false;
}

std::vector<bool> used_dfs;
void dfs(int cur) {
	if (used_dfs[cur])
		return;
	used_dfs[cur] = true;

	for (auto to = g[cur].begin(); to != g[cur].end(); ++to) {
		if (match[*to] != -1)
			dfs(match[*to]);
	}
}

int main() {
#ifdef _DEBUG 
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n1, n2, m;
	while (scanf("%d%d%d", &n2, &n1, &m)) {
		if (m == -1)
			break;

		g.resize(n1);
		for (int i = 0, a, b; i < m; i++) {
			scanf("%d%d", &a, &b);
			g[b - 1].push_back(a - 1);
		}

		match.resize(n2, -1);
		match_l.resize(n1, -1);
		used.resize(n1);
		for (int run = 1; run;) {
			run = 0;
			memset(used.data(), 0, used.size() * sizeof(used[0]));
			for (int i = 0; i < n1; i++) 
				if (match_l[i] == -1 && find_add_path(i)) 
					run = 1;
		}

		used_dfs.resize(n1);
		for (int i = 0; i < n1; i++) {
			if (match_l[i] == -1)
				dfs(i);
		}
		std::vector<int> res;
		for (int i = 0; i < n1; i++)
			if (used_dfs[i])
				res.push_back(i);

		int res_size = (int)res.size();
		printf("%d\n", res_size);
		for (auto i = res.begin(); i != res.end(); ++i)
			printf("%d ", *i + 1);
		printf("\n");

		g.clear();
		match.clear();
		match_l.clear();
		used.clear();
		used_dfs.clear();

		m = -1;
	}
	return 0;
}