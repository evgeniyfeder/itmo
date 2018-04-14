#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cmath>
std::string file_name = "fullham";
std::vector<std::vector<bool>> g;

const int max_n = 4000;
int arr[max_n * max_n + 5 * max_n];
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

	for (int i = 0; i < n; i++) {
		arr[i] = i;
	}

	int begin = 0, end = n;
	for (int k = 0; k < 2 * n; k++) {
		auto first = begin, second = begin + 1;
		if (!g[arr[first]][arr[second]]) {
			auto i = begin + 2;
			while (!g[arr[first]][arr[i]] || !g[arr[second]][arr[i + 1]])
				++i;

			for (int rev = 0; rev < (i - begin) / 2; rev++)
				std::swap(arr[begin + 1 + rev], arr[i - rev]);
		}
		arr[end] = arr[begin];
		begin++;
		end++;
	}

	for (int i = begin; i != end; i++)
		std::cout << arr[i] + 1 << " ";
}
