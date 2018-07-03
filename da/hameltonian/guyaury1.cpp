#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>

std::deque<int> cycle;
std::vector<int> order;

std::vector<std::vector<int>> g;
std::string file_name = "guyaury";

void search_place(int left, int right, int vase) {
	static std::string res;
	while (right - left > 1) {
		int mid = left + (right - left) / 2;

		auto elem_mid = cycle.begin();
		std::advance(elem_mid, mid);

		if (g[(*elem_mid)][vase])
			left = mid;
		else
			right = mid;
	}
	auto need_insert = cycle.begin();
	std::advance(need_insert, right);
	cycle.insert(need_insert, vase);
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
			g[j][i] = !flag;
		}
	}

	for (int i = 0; i < n; i++)
		order.push_back(i);

	bool found_cycle = false;
	while (!found_cycle) {
		cycle.push_back(order[0]);
		for (int i = 1; i < n; i++)
			search_place(-1, i, order[i]);

		if (g[*(cycle.end() - 1)][*cycle.begin()]) {
			found_cycle = true;
		}
		else {
			std::random_shuffle(order.begin(), order.end());
			cycle.clear();
		}
	}

	
	for (auto &i : cycle)
		std::cout << i + 1 << " ";

}
