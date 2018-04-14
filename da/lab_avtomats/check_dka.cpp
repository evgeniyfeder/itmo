#include <iostream>
#include <string>
#include <vector>
#include <map>

std::vector<std::map<char, int>> scheme;
std::vector<int> res_sost;
std::string file_name;
int main(void) {
#ifdef _DEBUG
	file_name = "test";
#else
	file_name = "problem1";
#endif
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
	int n, m, k;
	std::string str;
	std::cin >> str >> n >> m >> k;
	scheme.resize(n);
	res_sost.resize(k);
	for (int i = 0; i < k; i++) {
		std::cin >> res_sost[i];
		res_sost[i]--;
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		char key;
		std::cin >> a >> b >> key;
		scheme[a - 1][key] = b - 1;
	}
	int cur_vert = 0;
	for (auto i = str.begin(); i != str.end(); ++i) {
		auto next = scheme[cur_vert].find(*i);
		if (next != scheme[cur_vert].end()) {
			cur_vert = next->second;
		}
		else {
			std::cout << "Rejects\n";
			return 0;
		}
	}
	for (int i = 0; i < k; i++)
		if (cur_vert == res_sost[i]) {
			std::cout << "Accepts\n";
			return 0;
		}
	std::cout << "Rejects\n";
	return 0;
}