#include <iostream>
#include <vector>
#include <algorithm>
std::string file_name = "lca_rmq";
int mod = 1000000000;

std::vector<std::vector<int>> tree;
int n;
std::vector<int> rmq, rmq_depth;
std::vector<int> first;

std::vector<bool> was;
void create_tree_rmq(int cur_vert, int cur_depth) {
	if (was[cur_vert])
		return;
	was[cur_vert] = true;
	rmq.push_back(cur_vert);
	rmq_depth.push_back(cur_depth);
	first[cur_vert] = rmq.size() - 1;
	for (auto to = tree[cur_vert].begin(); to != tree[cur_vert].end(); ++to) {
		create_tree_rmq(*to, cur_depth + 1);
		rmq.push_back(cur_vert);
		rmq_depth.push_back(cur_depth);
	}
}

std::vector<std::vector<std::pair<int, int>>> sparse;
std::vector<int> log_length;

std::pair<int, int> get_res(int left, int right) {
	if (left > right) std::swap(left, right);
	int l = right - left + 1;
	return std::min(sparse[left][log_length[l]], sparse[right - (1 << log_length[l]) + 1][log_length[l]]);
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	int n_prev;
	int m;
	std::cin >> n >> m;
	n_prev = n;
	tree.resize(n);
	for (int i = 1; i < n; i++) {
		int p;
		std::cin >> p;
		tree[p].push_back(i);
	}

	was.resize(n);
	first.resize(n);
	create_tree_rmq(0, 0);

	int n = rmq_depth.size();
	log_length.resize(n + 1);
	log_length[0] = -1;
	for (int i = 1; i <= n; i++) {
		log_length[i] = log_length[i - 1] + int((i & (i - 1)) == 0);
	}

	sparse.resize(n);
	uint32_t logn = log_length[n] + 1;
	for (int i = 0; i < n; i++) {
		sparse[i].resize(logn);
		sparse[i][0].first = rmq_depth[i];
		sparse[i][0].second = rmq[i];
	}

	for (size_t step = 1; step < logn; step++) {
		for (int i = 0; i < n; i++) {
			if (i + (1 << (step - 1)) >= n)
				break;
			sparse[i][step] = std::min(sparse[i][step - 1], sparse[i + (1 << (step - 1))][step - 1]);
		}
	}

	long long a1, a2;
	long long x, y, z;
	std::cin >> a1 >> a2 >> x >> y >> z;

	int last_ans = get_res(first[int(a1)], first[int(a2)]).second;
	long long ans = 0;
	ans = (ans + last_ans);
	for (int i = 1; i < m; i++) {
		int a3 = int((x * a1 + y * a2 + z) % n_prev);
		int a4 = int((x * a2 + y * a3 + z) % n_prev);
		last_ans = get_res(first[(a3 + last_ans) % n_prev], first[a4]).second;
		ans = (ans + last_ans);
		a1 = a3;
		a2 = a4;
	}
	std::cout << ans;
	return 0;
}
