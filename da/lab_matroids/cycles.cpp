#include <iostream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <queue>
#include <functional>
std::string file_name = "cycles";

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n, m;
	std::cin >> n >> m;
	std::vector<bool> S(1 << n, false);

	std::vector<std::pair<int, int>> w(n);
	for (int i = 0; i < n; i++) {
		int wi;
		std::cin >> wi;
		w[i] = std::make_pair(wi, i);
	}
	std::queue<int> q;
	for (int i = 0; i < m; i++) {
		int cur = 0, size;
		std::cin >> size;

		for (int j = 0, shift; j < size; j++) {
			std::cin >> shift;
			cur |= 1 << (shift - 1);
		}
		S[cur] = true;
		q.push(cur);
	}

	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < n; i++) {
			if ((cur & (1 << i)) == 0) {
				cur |= 1 << i;
				if (!S[cur]) {
					S[cur] = true;
					q.push(cur);
				}
				cur = cur & ~(1 << i);
			}
		}
	}

	std::sort(w.begin(), w.end(), std::greater<std::pair<int, int>>());

	int cur_num = 0;
	int64_t res = 0;
	for (int i = 0; i < n; i++) {
		if (!S[cur_num | 1 << w[i].second]) {
			cur_num |= 1 << w[i].second;
			res += w[i].first;
		}
	}
	std::cout << res;
	return 0;
}
