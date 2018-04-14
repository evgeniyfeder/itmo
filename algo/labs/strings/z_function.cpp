#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
std::string file_name = "z";

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

	std::vector<int> z_function(text.size());
	z_function[0] = 0;

	for (int i = 1, l = 0, r = 0; i < (int)z_function.size(); i++) {
		/* First approximation */
		z_function[i] = std::max(0, std::min(r - i, z_function[i - l]));

		/* Increase z-function */
		while (i + z_function[i] < (int)text.size() && text[z_function[i]] == text[i + z_function[i]])
			z_function[i]++;

		/* Change segment */
		if (i + z_function[i] > r) {
			l = i;
			r = i + z_function[i];
		}
	}

	for (size_t ind = 1; ind < z_function.size(); ind++) {
		std::cout << z_function[ind] << " ";
	}
	return 0;
}
