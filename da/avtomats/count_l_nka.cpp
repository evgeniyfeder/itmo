#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
typedef std::pair <std::set<int>, int> pair;
static const int mod = 1000000007;

std::vector<std::vector<std::vector<int>>> scheme_nka;

std::vector<std::map<char, int>> scheme;

std::set<int> res_sost;
std::string file_name;

int finded_i;
bool check_exists(const std::vector<std::set<int>> &vec, const std::set<int> &set) {
	for (int i = 0; i < vec.size(); i++)
		if (vec[i] == set) {
			finded_i = i;
			return true;
		}
	return false;
}


int main(void) {
#ifdef _DEBUG
	file_name = "test";
#else
	file_name = "problem5";
#endif
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
	int n, m, k, l;
	std::cin >> n >> m >> k >> l;

	scheme_nka.resize(n);
	for (int i = 0; i < n; i++) {
		scheme_nka[i].resize(30);
	}

	for (int i = 0; i < k; i++) {
		int a;
		std::cin >> a;
		res_sost.insert(--a);
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		char key;
		std::cin >> a >> b >> key;
		scheme_nka[a - 1][key - 'a'].push_back(b - 1);
	}


	/* Create dka */
	std::queue<pair> q;
	std::set<int> s;
	std::vector<std::set<int>> cur_m;
	std::map<char, int> map;
	s.insert(0);
	cur_m.push_back(s);
	pair cur_pair(s, 0);
	q.push(cur_pair);
	scheme.push_back(map);
	std::set<int> res_sost_dka;
	if (res_sost.find(0) != res_sost.end())
		res_sost_dka.insert(0);
	while (!q.empty()) {
		cur_pair = q.front();
		q.pop();
		for (int c = 0; c < 26; c++) {
			std::set<int> end;
			bool is_terminal = false;
			for (auto p = cur_pair.first.begin(); p != cur_pair.first.end(); p++) {
				if (!scheme_nka[*p][c].empty()) {
					for (int i = 0; i < scheme_nka[*p][c].size(); i++) {
						end.insert(scheme_nka[*p][c][i]);
						if (res_sost.find(scheme_nka[*p][c][i]) != res_sost.end())
							is_terminal = true;
					}
				}
			}
			if (end.size() != 0 && !check_exists(cur_m, end)) {
				q.push(pair(end, cur_m.size()));
				scheme[cur_pair.second][c] = cur_m.size();
				if (is_terminal)
					res_sost_dka.insert(cur_m.size());
				cur_m.push_back(end);
				scheme.push_back(map);
			}
			else if (end.size() != 0) {
				scheme[cur_pair.second][c] = finded_i;
			}
		}
	}
	res_sost = res_sost_dka;
	n = scheme.size();
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