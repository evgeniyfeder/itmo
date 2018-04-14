#include <iostream>
#include <vector>
std::string file_name = "vertexcover";

std::vector<std::vector<int>> left, right;
std::vector<int> match_l, match_r, used_l, used_r;


void dfs(int cur, bool is_left) {
	if (is_left) {
		if (used_l[cur])
			return;
		used_l[cur] = true;
		for (const auto &x : left[cur])
			if (x != match_l[cur])
				dfs(x, !is_left);
	}
	else {
		if (used_r[cur])
			return;
		used_r[cur] = true;
		for (const auto &x : right[cur])
			if (x == match_r[cur])
				dfs(x, !is_left);
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

	int m, n;
	std::cin >> m >> n;

	left.resize(m);
	right.resize(n);
	for (int i = 0; i < m; i++) {
		int edges;
		std::cin >> edges;

		for (int j = 0, r; j < edges; j++) {
			std::cin >> r;
			r--;

			left[i].push_back(r);
			right[r].push_back(i);
		}
	}

	match_l.resize(m, -1);
	match_r.resize(n, -1);
	for (int i = 0, r; i < m; i++) {
		std::cin >> r;
		r--;

		match_l[i] = r;

		if (r != -1)
			match_r[r] = i;
	}

	used_l.resize(m);
	used_r.resize(n);
	for (int i = 0; i < m; i++) {
		if (used_l[i] || match_l[i] != -1)
			continue;
		dfs(i, true);
	}

	int res_left = 0, res_right = 0;
	for (int i = 0; i < m; i++)
		if (!used_l[i])
			res_left++;

	for (int i = 0; i < n; i++)
		if (used_r[i])
			res_right++;

	std::cout << res_left + res_right << std::endl;
	std::cout << res_left << " ";
	for (int i = 0; i < m; i++)
		if (!used_l[i])
			std::cout << i + 1 << ' ';
	
	std::cout << std::endl << res_right << ' ';
	for (int i = 0; i < n; i++)
		if (used_r[i])
			std::cout << i + 1 << ' ';


	return 0;
}
