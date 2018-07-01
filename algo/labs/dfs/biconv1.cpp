#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stack>
std::string file_name = "biconv";

typedef std::pair<uint32_t, int32_t> pair;
std::vector<std::vector<pair>> g;
std::vector<bool> used;
std::vector<uint32_t> d, up;
std::vector<bool> result;
std::vector<uint32_t> components;

int num_comp = 0;
int time = 0;
std::stack<int> blocks;
void make_companent(uint32_t cur, uint32_t parent) {
	d[cur] = time;
	up[cur] = time;
	used[cur] = true;
	time++;
	for (auto to = g[cur].begin(); to != g[cur].end(); ++to) {
		if (to->first == parent)
			continue;

		if (!used[to->first]) {
			blocks.push(to->second);
			make_companent(to->first, cur);

			if (up[to->first] >= d[cur]) {
				int comp = num_comp++;
				while (blocks.top() != to->second) {
					components[blocks.top()] = comp;
					blocks.pop();
				}
				components[to->second] = comp;
				blocks.pop();
			}
			if (up[to->first] < up[cur])
				up[cur] = up[to->first];
		}
		else if (d[to->first] < d[cur])
			blocks.push(to->second);
		else if (up[cur] > d[to->first])
			up[cur] = d[to->first];

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
	components.resize(m);
	for (uint32_t i = 0; i < n; i++)
		if (!used[i]) {
			time = 0;
			num_comp++;
			make_companent(i, -1);
		}

	std::cout << num_comp << std::endl;
	for (uint32_t i = 0; i < components.size(); i++) {
		std::cout << components[i] << " ";
	}
}