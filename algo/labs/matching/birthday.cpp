#include <iostream>
#include <vector>
std::string file_name = "birthday";

bool find_adding_path(int cur, const std::vector<std::vector<bool>> &g, 
	std::vector<int> &math, std::vector<bool> &used) {
	if (used[cur])
		return false;
	used[cur] = true;
	for (int to = 0; to < (int)g[cur].size(); to++) {
		if (g[cur][to]) {
			if (math[to] == -1 || find_adding_path(math[to], g, math, used)) {
				math[to] = cur;
				return true;
			}
		}
	}
	return false;
}

void dfs(int cur, int cur_part, const std::vector<std::vector<bool>> g[2], 
	const std::vector<int> math_r, std::vector<bool> used[2]) {
	if (used[cur_part][cur])
		return;
	used[cur_part][cur] = true;

	for (int to = 0; to < (int)g[cur_part][cur].size(); to++) {
		if (g[cur_part][cur][to]) {
			if (cur_part == 0 && math_r[to] != cur)
				dfs(to, 1, g, math_r, used);
			else if (cur_part == 1 && math_r[cur] == to) {
				dfs(to, 0, g, math_r, used);
			}
		}
	}
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

	int k = 0;
	std::cin >> k;

	for (int num = 0; num < k; num++) {
		int a_size, b_size;
		std::cin >> a_size >> b_size;

		std::vector<std::vector<bool>> g[2];
		
		g[0].resize(a_size);
		for (int i = 0; i < a_size; i++)
			g[0][i].resize(b_size, true);

		g[1].resize(b_size);
		for (int i = 0; i < b_size; i++)
			g[1][i].resize(a_size, true);

		for (int i = 0, x; i < a_size; i++) {
			std::cin >> x;
			while (x != 0) {
				g[0][i][x - 1] = false;
				g[1][x - 1][i] = false;
				
				std::cin >> x;
			}
		}

		// Find matching
		std::vector<int> matching(b_size, -1);

		std::vector<bool> used(a_size);
		for (int i = 0; i < a_size; i++) {
			for (int j = 0; j < a_size; j++)
				used[j] = 0;
			find_adding_path(i, g[0], matching, used);
		}
		
		//Find vertices in a
		std::vector<bool> math_a(a_size);
		for (int i = 0; i < b_size; i++)
			if (matching[i] != -1)
				math_a[matching[i]] = true;

		// Find minimum vertex cover
		std::vector<bool> used_[2];
		used_[0].resize(a_size);
		used_[1].resize(b_size);

		for (int i = 0; i < a_size; i++) {
			if (!used_[0][i] && !math_a[i])
				dfs(i, 0, g, matching, used_);
		}

		// Count result size
		int res[2] = {0};
		for (int i = 0; i < a_size; i++)
			if (used_[0][i])
				res[0]++;

		for (int i = 0; i < b_size; i++)
			if (!used_[1][i])
				res[1]++;

		std::cout << res[0] + res[1] << std::endl;
		std::cout << res[0] << " " << res[1] << std::endl;

		for (int i = 0; i < a_size; i++)
			if (used_[0][i])
				std::cout << i + 1 << " ";
		std::cout << std::endl;

		for (int i = 0; i < b_size; i++)
			if (!used_[1][i])
				std::cout << i + 1 << " ";
		std::cout << std::endl << std::endl;
	}
}
