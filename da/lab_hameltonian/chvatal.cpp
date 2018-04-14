#include <iostream>
#include <deque>
#include <vector>
#include <string>

std::string file_name = "chvatal";
std::vector<std::vector<bool>> g;

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;

	g.resize(n);
	for (int i = 0; i < n; i++)
		g[i].resize(n);

	std::string str;
	for (int i = 1; i < n; i++) {
		std::cin >> str;
		for (int j = 0; j < i; j++) {
			bool flag = (str[j] == '1');
			g[i][j] = flag;
			g[j][i] = flag;
		}
	}

	std::deque<int> d;
	for (int i = 0; i < n; i++) {
		d.push_back(i);
	}

	for (int k = 0; k < n * (n - 1); k++) {
		auto first = d.at(0), second = d.at(1);
		if (!g[first][second]) {
			auto i = d.begin() + 2;
			while (i != d.end() - 1 && (!g[first][*i] || !g[second][*(i + 1)]))
				++i;
			if (i == d.end() - 1) {
				auto j = d.begin() + 2;

				while (j != d.end() && !g[first][*j])
					++j;
				std::reverse(d.begin() + 1, j + 1);
			}
			else {
				std::reverse(d.begin() + 1, i + 1);
			}
		}
		d.push_back(d.front());
		d.pop_front();
	}

	for (auto elem : d)
		std::cout << elem + 1 << " ";
}