﻿#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
std::string file_name = "biconv";

typedef std::pair<uint32_t, int32_t> pair;
std::vector<std::vector<pair>> g;
std::vector<bool> used;
std::vector<uint32_t> d, up;
std::vector<bool> result;

uint32_t dfs(uint32_t cur_vert, int32_t cur_edge, uint32_t cur_depth) {
	uint32_t min = cur_depth;
	used[cur_vert] = true;
	d[cur_vert] = cur_depth;
	bool is_point = false;
	int child_cnt = 0; 
	for (auto to = g[cur_vert].begin(); to != g[cur_vert].end(); ++to) {
		if (!used[to->first]) {
			min = std::min(min, dfs(to->first, to->second, cur_depth + 1));
			is_point |= up[to->first] >= d[cur_vert];
			child_cnt++;
		}
		else if (cur_edge != to->second)
			min = std::min(min, d[to->first]);
	}
	if (cur_depth == 0 && child_cnt > 1)
		result[cur_vert] = true;
	else if (cur_depth != 0 && is_point)
		result[cur_vert] = true;
	up[cur_vert] = min;
	return min;
}

std::vector<uint32_t> components;
int num_comp = 0;
void make_companent(uint32_t cur, uint32_t parent, uint32_t comp) {
	used[cur] = true;
	for (auto to = g[cur].begin(); to != g[cur].end(); ++to) {
		if (to->first == parent)
			continue;

		if (!used[to->first]) {
			if (result[cur]) {
				components[to->second] = ++num_comp;
				make_companent(to->first, cur, num_comp);
			}
			else {
				components[to->second] = comp;
				make_companent(to->first, cur, comp);
			}
		}
		else if (up[to->first] <= d[cur]) {
			components[to->second] = comp;
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

	uint32_t n, m;
	std::cin >> n >> m;

	g.resize(n);
	used.resize(n);
	up.resize(n);
	d.resize(n);
	for (uint32_t i = 0; i < m; i++) {
		uint32_t from, to;
		std::cin >> from >> to;
		g[from - 1].push_back(pair(to - 1, int32_t(i)));
		g[to - 1].push_back(pair(from - 1, int32_t(i)));
	}

	result.resize(n);
	for (uint32_t i = 0; i < n; i++)
		if (!used[i])
			dfs(i, -1, 0);

	for (uint32_t i = 0; i < n; i++)
		used[i] = 0;

	components.resize(m);
	for (uint32_t i = 0; i < n; i++)
		if (!used[i])
			make_companent(i, UINT32_MAX, ++num_comp);

	std::cout << num_comp << std::endl;
	for (uint32_t i = 0; i < result.size(); i++) {
		std::cout << components[i] << " ";
	}
}