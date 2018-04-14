#include <iostream>
#include <vector>
#include <stack>
std::string file_name = "euler";

static const int max_n = 1010;
int g[max_n][max_n];
int n;

std::vector<int> result;
void find(int begin) {
	std::stack<int> s;
	s.push(begin);
	while (!s.empty()) {
		int cur = s.top();

		for (int to = 0; to < n; to++) {
			if (g[cur][to] != 0) {
				g[cur][to]--;
				g[to][cur]--;
				s.push(to);
				break;
			}
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

	std::cin >> n;

	int odd_num = 0, start = -1;
	for (int i = 0; i < n; i++) {
		int num;
		std::cin >> num;

		if (num % 2 == 1) {
			odd_num++;
			start = i;
		}

		for (int j = 0, x; j < num; j++) {
			std::cin >> x;
			g[i][x - 1]++;
		}
	}
	if (odd_num > 2) {
		std::cout << -1;
		return 0;
	}

	if (odd_num != 0) {
		find(start);
	}
	else {
		find(0);
	}

	std::cout << result.size() - 1 << std::endl;

	for (auto it = result.begin(); it != result.end(); ++it) {
		std::cout << *it + 1 << " ";
	}
	
}
