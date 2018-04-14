#include <iostream>
#include <vector>
#include <stack>
std::string file_name = "codelock";

int base, len;
std::vector<std::vector<int>> g;
std::vector<int> first_exist;

std::vector<int> result;
void find(int begin) {
	std::stack<int> s;
	s.push(begin);
	while (!s.empty()) {
		int cur = s.top();

		for (auto it = g[cur].begin(); it != g[cur].end(); ++it) {
			/*if (!deleted[cur][*it]) {
				s.push(*it);
				deleted[cur][*it] = true;
				break;
			}*/
		}
		if (cur == s.top()) {
			s.pop();
			result.push_back(cur);
		}
	}
}

void dfs(int cur) {
	while (first_exist[cur] < (int)g[cur].size())
		dfs(g[cur][first_exist[cur]++]);
	result.push_back(cur);
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
	std::cin >> base >> len;

	if (len == 1) {
		for (int i = 0; i < base; i++)
			std::cout << i;
		return 0;
	}

	int n = 1;
	for (int i = 0; i < len - 1; i++)
		n *= base;

	g.resize(n);
	first_exist.resize(n);
	int last_digit = n / base;
	
	for (int i = 0; i < n; i++) {
		int div = (i % last_digit) * base;
		for (int j = 0; j < base; j++) {
			g[i].push_back(div + j);
		}
	}
	dfs(0);

	for (int i = 0; i < len - 1; i++) {
		std::cout << "0";
	}

	for (int i = (int)result.size() - 2; i >= 0; i--)
		std::cout << result[i] % base;
}
