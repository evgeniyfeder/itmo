#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>

static const int mod = 1000000007;

std::vector<std::map<char, int>> scheme;
std::vector<std::vector<std::set<char>>> reverse_scheme;
std::vector<int> count_in;
std::set<int> res_sost;
std::vector<int> dp;
std::set<int> get_from_start, get_from_end;


std::string file_name;
int main(void) {
#ifdef _DEBUG
	file_name = "test";
#else
	file_name = "problem3";
#endif
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
	int n, m, k;
	std::cin >> n >> m >> k;
	scheme.resize(n);
	reverse_scheme.resize(n);
	for (int i = 0; i < n; i++)
		reverse_scheme[i].resize(n);

	count_in.resize(n);
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
		reverse_scheme[b - 1][a - 1].insert(key);
		count_in[b - 1]++;
	}
	dp.resize(n);

	std::set<int> cur_vert;
	std::set<int> new_cur_vert;
	cur_vert.insert(0);
	
	/* Fill get from start */
	while (!cur_vert.empty()) {
		for (auto j = cur_vert.begin(); j != cur_vert.end(); ++j) {
			if (get_from_start.find(*j) != get_from_start.end())
				continue;

			get_from_start.insert(*j);
			for (auto u = scheme[*j].begin(); u != scheme[*j].end(); ++u) 
				new_cur_vert.insert(u->second);

		}
		cur_vert = new_cur_vert;
		new_cur_vert.clear();
	}

	for (int i = 0; i < n; i++) {
		if (get_from_start.find(i) == get_from_start.end()) {
			for (auto u : scheme[i]) {
				reverse_scheme[u.second][i].clear();
				count_in[u.second]--;
			}
			scheme[i].clear();
		}
	}
	
	/* Fill get from end */
	for (auto i : res_sost)
		cur_vert.insert(i);

	while (!cur_vert.empty()) {
		for (auto j = cur_vert.begin(); j != cur_vert.end(); ++j) {
			if (get_from_end.find(*j) != get_from_end.end()) {
				continue;
			}

			get_from_end.insert(*j);
			for (int u = 0; u < n; u++)
				if (!reverse_scheme[*j][u].empty())
					new_cur_vert.insert(u);

		}
		cur_vert = new_cur_vert;
		new_cur_vert.clear();
	}

	for (int i = 0; i < n; i++) {
		if (get_from_end.find(i) == get_from_end.end()) {
			for (auto u : scheme[i]) {
				reverse_scheme[u.second][i].clear();
				count_in[u.second]--;
			}
			scheme[i].clear();
		}
	}

	/* Count dp */
	if (get_from_end.find(0) == get_from_end.end()) {
		std::cout << 0 << std::endl;
		return 0;
	}

	std::queue<int> q;
	if (count_in[0] == 0) {
		q.push(0);
		count_in[0]++;
	}
	else {
		std::cout << -1 << std::endl;
		return 0;
	}

	while(!q.empty()) {
		int cur_elem = q.front();
		q.pop();

		if (--count_in[cur_elem] == 0) {
			int sum = 0;
			for (int u = 0; u != reverse_scheme[cur_elem].size(); ++u) {
				if (!reverse_scheme[cur_elem][u].empty()) {
					for (int s = 0; s < reverse_scheme[cur_elem][u].size(); s++) {
						if (dp[u] == 0)
							sum = (sum + 1) % mod;
						else
							sum = (sum + dp[u]) % mod;
					}
				}
			}
			dp[cur_elem] = sum;

			for (auto u = scheme[cur_elem].begin(); u != scheme[cur_elem].end(); ++u) {
				q.push(u->second);
			}
		}
	}
	for (auto j = get_from_end.begin(); j != get_from_end.end(); ++j) {
		if (count_in[*j] != 0) {
			std::cout << -1 << std::endl;
			return 0;
		}
	}

	std::set<int> availible;
	for (int i = 0; i < n; i++)
		if (get_from_start.find(i) != get_from_start.end() && get_from_end.find(i) != get_from_end.end())
			availible.insert(i);

	for (auto i = availible.begin(); i != availible.end(); ++i)
		if (count_in[*i] != 0) {
			std::cout << -1 << std::endl;
			return 0;
		}

	dp[0] = 1;
	long long res_count = 0;
	for (auto j = res_sost.begin(); j != res_sost.end(); ++j) {
		res_count = (res_count + dp[*j]) % mod;
	}
	std::cout << res_count << std::endl;
	return 0;
}