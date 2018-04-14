#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

std::vector<std::vector<std::vector<int>>> scheme;
std::set<int> res_sost;
std::string file_name;
int main(void) {
#ifdef _DEBUG
	file_name = "test";
#else
	file_name = "problem2";
#endif
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
	int n, m, k;
	std::string str;
	std::cin >> str >> n >> m >> k;
	scheme.resize(n);
	for (int i = 0; i < n; i++) {
		scheme[i].resize(30);
	}
	for (int i = 0; i < k; i++) {
		int a;
		std::cin >> a;
		res_sost.insert(--a);
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		char key;
		std::cin >> a >> b >> key;
		scheme[a - 1][key - 'a'].push_back(b - 1);
	}
	std::set<int> cur_vert;
	std::set<int> new_cur_vert;
	cur_vert.insert(0);
	for (int i = 0; i != str.size(); ++i) {
		for (auto j = cur_vert.begin(); j != cur_vert.end(); ++j) {
			for (int l = 0; l < scheme[*j][str[i] - 'a'].size(); l++) {
				new_cur_vert.insert(scheme[*j][str[i] - 'a'][l]);
			}
		}
		cur_vert = new_cur_vert;
		new_cur_vert.clear();
	}
	for (auto j = cur_vert.begin(); j != cur_vert.end(); ++j) {
		if (res_sost.find(*j) != res_sost.end()) {
			std::cout << "Accepts\n";
			return 0;
		}
	}
	std::cout << "Rejects\n";
	return 0;
}