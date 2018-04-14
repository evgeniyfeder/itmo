#include <string>
#include <iostream>
#include <set>
#include <vector>
std::string file_name = "prefix";

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	std::string text;
	std::cin >> text;

	std::string templ = text;

	std::vector<int> prefix_function(templ.size());

	prefix_function[0] = 0;
	for (int i = 1; i < (int)templ.size(); i++) {
		int j = prefix_function[i - 1];

		while (j > 0 && templ[j] != templ[i]) {
			j = prefix_function[j - 1];
		}

		if (templ[j] == templ[i])
			j++;

		prefix_function[i] = j;
	}

	for (auto&& x : prefix_function) {
		std::cout << x << " ";
	}
	return 0;
}
