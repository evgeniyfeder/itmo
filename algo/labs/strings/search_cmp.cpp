#include <string>
#include <iostream>
#include <set>
#include <vector>
std::string file_name = "search2";

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	std::string text, w;
	std::cin >> w >> text;

	std::string templ = w + char(1) + text;

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

	
	std::set<int> result;
	for (size_t i = w.size(); i < templ.size(); i++)
		if (prefix_function[i] == (int)w.size())
			result.insert((int)i - (int)w.size() * 2 + 1);

	std::cout << result.size() << std::endl;
	for (auto&& x : result) {
		std::cout << x << " ";
	} 
	return 0;
}
