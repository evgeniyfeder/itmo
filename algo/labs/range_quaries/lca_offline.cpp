#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define MAX_N 500010
typedef std::pair<int, int> pairii;
std::vector<int> tree[MAX_N];
std::vector<pairii> queries[MAX_N];
std::vector<pairii> answers;
struct dsu {
	int data[MAX_N], anc[MAX_N];

	int get(int cur_vert) {
		return data[cur_vert] == cur_vert ? cur_vert : data[cur_vert] = get(data[cur_vert]);
	}

	void union_dsu(int a, int b, int new_anc) {
		a = get(a);
		b = get(b);
		
		if (rand() & 1) 
			std::swap(a, b);
		data[a] = b;
		anc[b] = new_anc;
	}
} dsu;

bool was[MAX_N];
void dfs(int cur_vert) {
	dsu.data[cur_vert] = cur_vert;
	dsu.anc[cur_vert] = cur_vert;
	was[cur_vert] = true;

	for (auto to = tree[cur_vert].begin(); to != tree[cur_vert].end(); ++to) {
		if (!was[*to]) {
			dfs(*to);
			dsu.union_dsu(cur_vert, *to, cur_vert);
		}
	}
	for (auto q = queries[cur_vert].begin(); q != queries[cur_vert].end(); ++q) {
		if (was[q->first]) {
			answers.push_back(pairii(dsu.anc[dsu.get(q->first)], q->second));
		}
		else
			queries[q->first].push_back(pairii(cur_vert, q->second));
	}
}
std::string file_name = "lca";
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	int k;
	std::cin >> k;

	for (int i = 0; i < k; i++) {
		std::string str;
		int a, b;
		std::cin >> str;
		std::cin >> a >> b;
		a--;
		b--;
		if (str == "ADD") {
			tree[a].push_back(b);
		}
		else if (str == "GET") {
			if (a > b) std::swap(a, b);
			queries[b].push_back(pairii(a, i));
		}
	}
	dfs(0);
	std::sort(answers.begin(), answers.end(), [](const pairii &a, const pairii &b) {return a.second < b.second; });

	for (size_t i = 0; i < answers.size(); i++) {
		std::cout << answers[i].first + 1 << std::endl;
	}
	return 0;
}
