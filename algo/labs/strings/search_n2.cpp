#include <string>
#include <iostream>
#include <set>
std::string file_name = "search1";

bool check(const std::string& text, const std::string& w, int pos_begin) {
	for (size_t j = 0; j < w.size(); j++) {
		if (text[pos_begin + j] != w[j]) {
			return false;
		}
	}
	return true;
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

	std::string text, w;
	std::cin >> w >> text;

	std::set<size_t> result;
	const int size = (int)text.size() - (int)w.size() + 1;
	for (int i = 0; i < size; i++) {
		if (text[i] == w[0]) {
			if (check(text, w, i))
				result.insert(i + 1);
		}
	}

	std::cout << result.size() << std::endl;
	for (auto&& x : result) {
		std::cout << x << " ";
	}
	return 0;
}