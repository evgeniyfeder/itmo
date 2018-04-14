#include <iostream>
#include <vector>
#include <queue>
std::string file_name = "game";

std::vector<std::vector<int>> reverse_g;
const int32_t WIN = 1;
const int32_t LOSE = 2;

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	int n, m, start;
	std::cin >> n >> m >> start;

	start--;
	std::vector<int> out_cnt(n);
	reverse_g.resize(n);
	for (int i = 0; i < m; ++i) {
		uint32_t from, to;
		std::cin >> from >> to;
		reverse_g[to - 1].push_back(from - 1);
		out_cnt[from - 1]++;
	}

	std::queue<uint32_t> q;
	std::vector<int32_t> result(n);
	
	for (int i = 0; i < n; i++)
		if (out_cnt[i] == 0) {
			result[i] = LOSE;
			q.push(i);
		}

	while (!q.empty()) {
		int32_t cur = q.front();
		q.pop();

		for (auto to = reverse_g[cur].begin(); to != reverse_g[cur].end(); ++to) {
			if (result[*to] == 0) {
				if (result[cur] == LOSE) {
					result[*to] = WIN;
					q.push(*to);
				}
				else if (--out_cnt[*to] == 0) {
					result[*to] = LOSE;
					q.push(*to);
				}
			}
		}
	}

	if (result[start] == WIN)
		std::cout << "First player wins";
	else if (result[start] == LOSE)
		std::cout <<  "Second player wins";
	return 0;
}
