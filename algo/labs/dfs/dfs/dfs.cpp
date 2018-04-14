#include <iostream>
#include <stack>
#include <vector>
#include <list>
std::string file_name = "dfs";

using pair = std::pair<int, int>;

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n, l;
	std::cin >> n >> l;

	std::list<int> s;
	std::vector<std::vector<bool>> res(n);
	for (int i = 0; i < n; i++)
		res[i].resize(n);

	std::vector<int> nodes, num_vert(n);
	for (int i = 0, x; i < l; i++) {
		std::cin >> x;
		nodes.push_back(x - 1);
		num_vert[x - 1]++;
	}

	int res_cnt = 0;
	for (int i = 0, x; i < l; i++) {
		x = nodes[i];
		num_vert[x]--;
		if (s.empty()) {
			s.push_back(x);
		}
		else if (res[x][s.back()]) {
			res[s.back()][x] = true;
			s.pop_back();
			if (num_vert[x] == 0 && s.size() == 1)
				s.pop_back();
		}
		else if (num_vert[x] == 0 && x == s.back() && s.size() == 1)
			s.pop_back();
		else {
			if (!s.empty()) {
				for (auto e = s.begin(); e != --s.end(); ++e) {
					res[*e][x] = true;
					res[x][*e] = true;
				}
				res[s.back()][x] = true;
				s.push_back(x);
			}
		}
	}

	res_cnt = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (res[i][j] && res[j][i])
				res_cnt++;
	std::cout << res_cnt << std::endl;

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (res[i][j] && res[j][i])
				std::cout << i + 1 << " " << j + 1 << std::endl;
	return 0;
}