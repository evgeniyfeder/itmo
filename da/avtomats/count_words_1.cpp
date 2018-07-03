#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#define MAX_N 100000
static const int mod = 1000000007;

std::vector<int> scheme[MAX_N];
std::vector<int> reverse_scheme[MAX_N];
int count_in[MAX_N], dp[MAX_N];
bool active_start[MAX_N], active_end[MAX_N];
std::set<int> res_sost;


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

	for (int i = 0; i < k; i++) {
		int a;
		std::cin >> a;
		res_sost.insert(--a);
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		char key;
		std::cin >> a >> b >> key;
		scheme[a - 1].push_back(b - 1);
		reverse_scheme[b - 1].push_back(a - 1);
		count_in[b - 1]++;
	}

	std::queue<int> q;
	q.push(0);

	/* Fill get from start */
	while (!q.empty()) {
		int cur_elem = q.front();
		q.pop();

		if (active_start[cur_elem])
			continue;

		active_start[cur_elem] = true;
		for (auto u = scheme[cur_elem].begin(); u != scheme[cur_elem].end(); ++u)
			q.push(*u);
	}

	/* Fill get from end */
	for (auto i : res_sost)
		q.push(i);

	while (!q.empty()) {
		int cur_elem = q.front();
		q.pop();

		if (active_end[cur_elem])
			continue;

		active_end[cur_elem] = true;
		for (auto u = reverse_scheme[cur_elem].begin(); u != reverse_scheme[cur_elem].end(); ++u)
			q.push(*u);
	}

	for (int i = 0; i < n; i++) {
		if (!active_start[i] || !active_end[i]) {
			for (auto j : scheme[i])
				count_in[j]--;
			scheme[i].clear();
		}
	}

	/* Count dp */
	if (!active_end[0]) {
		std::cout << 0 << std::endl;
		return 0;
	}

	if (count_in[0] == 0) {
		q.push(0);
		count_in[0]++;
	}
	else {
		std::cout << -1 << std::endl;
		return 0;
	}

	while (!q.empty()) {
		int cur_elem = q.front();
		q.pop();
		if (--count_in[cur_elem] == 0) {
			int sum = 0;
			for (int u = 0; u != reverse_scheme[cur_elem].size(); ++u) {
				if (active_start[reverse_scheme[cur_elem][u]] && active_end[reverse_scheme[cur_elem][u]]) {
					if (dp[reverse_scheme[cur_elem][u]] == 0)
						sum = (sum + 1) % mod;
					else
						sum = (sum + dp[reverse_scheme[cur_elem][u]]) % mod;
				}
			}
			dp[cur_elem] = sum;

			for (auto u = scheme[cur_elem].begin(); u != scheme[cur_elem].end(); ++u) {
				q.push(*u);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (active_start[i] && active_end[i] && count_in[i] != 0) {
			std::cout << -1 << std::endl;
			return 0;
		}
	}

	dp[0] = 1;
	long long res_count = 0;
	for (auto j = res_sost.begin(); j != res_sost.end(); ++j) {
		res_count = (res_count + dp[*j]) % mod;
	}
	std::cout << res_count << std::endl;
	return 0;
}