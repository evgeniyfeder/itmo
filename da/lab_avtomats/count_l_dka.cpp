#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

static const int mod = 1000000007;

std::vector<std::map<char, int>> scheme;
std::set<int> res_sost;
std::string file_name;
int main(void) {
#ifdef _DEBUG
	file_name = "test";
#else
	file_name = "problem4";
#endif
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
	int n, m, k, l;
	std::cin >> n >> m >> k >> l;
	scheme.resize(n);
	for (int i = 0; i < k; i++) {
		int a;
		std::cin >> a;
		res_sost.insert(--a);
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		char key;
		std::cin >> a >> b >> key;
		scheme[a - 1][key] = b - 1;
	}
	std::vector<long long> res(n), new_res(n);
	std::set<int> cur_vert;
	std::set<int> new_cur_vert;
	cur_vert.insert(0);
	for (int i = 0; i < l; ++i) {
		for (auto j = cur_vert.begin(); j != cur_vert.end(); ++j) {
			for (auto u = scheme[*j].begin(); u != scheme[*j].end(); ++u) {
				if (res[*j] == 0)
					new_res[u->second] = (new_res[u->second] + 1) % mod;
				else
					new_res[u->second] = (new_res[u->second] + res[*j]) % mod;

				new_cur_vert.insert(u->second);
			}
		}
		for (int j = 0; j < n; j++) {
			res[j] = new_res[j];
			new_res[j] = 0;
		}
		cur_vert = new_cur_vert;
		new_cur_vert.clear();
	}
	long long res_count = 0;
	for (auto j = cur_vert.begin(); j != cur_vert.end(); ++j) {
		auto ind = res_sost.find(*j);
		if (ind != res_sost.end()) {
			res_count = (res_count + res[*ind]) % mod;
		}
	}
	std::cout << res_count << std::endl;
	return 0;
}