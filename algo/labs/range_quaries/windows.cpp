#include <iostream>
#include <vector>
#include <algorithm>
std::string file_name = "windows";

class segment_tree {
	struct node {
		long long max, add;
		int max_ind;

		node() : max(0), add(0), max_ind(0) {
		}
	};
public:
	std::vector<node> heap;
	int n;

	void update_max(int cur_vert) {
		int need;
		if (heap[2 * cur_vert].max >= heap[2 * cur_vert + 1].max)
			need = 2 * cur_vert;
		else
			need = 2 * cur_vert + 1;

		heap[cur_vert].max = heap[need].max + heap[cur_vert].add;
		heap[cur_vert].max_ind = heap[need].max_ind;
	}
	void build_tree_rec(const std::vector<long long> &arr, int cur_ind, int left, int right) {
		if (left == right) {
			heap[cur_ind].max = 0;
			heap[cur_ind].max_ind = left;
		}
		else {
			int middle = left + (right - left) / 2;
			build_tree_rec(arr, 2 * cur_ind, left, middle);
			build_tree_rec(arr, 2 * cur_ind + 1, middle + 1, right);
			update_max(cur_ind);
		}

	}

	segment_tree(const std::vector<long long> &arr) : n(arr.size()) {
		heap.resize(4 * n);
		build_tree_rec(arr, 1, 0, n - 1);
	}

	std::pair<long long, int> get_recur(int cur_vert, int cur_left, int cur_right, int get_left, int get_right) {
		if (get_right < get_left)
			return std::pair<long long, int>(INT32_MIN, 0);
		if (cur_left == get_left && cur_right == get_right)
			return std::pair<long long, int>(heap[cur_vert].max, heap[cur_vert].max_ind);

		int middle = cur_left + (cur_right - cur_left) / 2;
		return std::max(get_recur(2 * cur_vert, cur_left, middle, get_left, std::min(get_right, middle)),
			get_recur(2 * cur_vert + 1, middle + 1, cur_right, std::max(get_left, middle + 1), get_right));
	}

	std::pair<long long, int> get(int left, int right) {
		return get_recur(1, 0, n - 1, left, right);
	}

	void add_recur(int cur_vert, int cur_left, int cur_right, int add_left, int add_right, long long x) {
		if (add_right < add_left)
			return;
		if (cur_left == add_left && cur_right == add_right) {
			heap[cur_vert].add += x;
			heap[cur_vert].max += x;
			return;
		}

		int middle = cur_left + (cur_right - cur_left) / 2;
		add_recur(2 * cur_vert, cur_left, middle, add_left, std::min(add_right, middle), x);
		add_recur(2 * cur_vert + 1, middle + 1, cur_right, std::max(add_left, middle + 1), add_right, x);
		update_max(cur_vert);
	}

	void add(int left, int right, long long x) {
		add_recur(1, 0, n - 1, left, right, x);
	}
};


struct rectangle {
	int left, right, top, bottom;
	rectangle(int left, int right, int top, int bottom) : left(left), right(right), top(top), bottom(bottom) {
		
	}
};
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif

	int n;
	std::cin >> n;
	int max_left = INT32_MAX, max_right = INT32_MIN, max_top = INT32_MAX, max_bottom = INT32_MIN;
	std::vector<rectangle> recs;
	for (int i = 0; i < n; i++) {
		int left, right, top, bottom;
		std::cin >> left >> top >> right >> bottom;
		if (right - left > 0 && bottom - top > 0) {
			recs.push_back(rectangle(left, right, top, bottom));
			max_left = std::min(max_left, recs[recs.size() - 1].left);
			max_right = std::max(max_right, recs[recs.size() - 1].right);
			max_top = std::min(max_top, recs[recs.size() - 1].top);
			max_bottom = std::max(max_bottom, recs[recs.size() - 1].bottom);
		}
	}
	std::vector<rectangle> recs_sort_right = recs;
	std::sort(recs.begin(), recs.end(), [](const rectangle &a, const rectangle &b) {return a.left < b.left; });
	std::sort(recs_sort_right.begin(), recs_sort_right.end(), [](const rectangle &a, const rectangle &b) {return a.right < b.right; });

	int max_h = 2 * (std::max(abs(max_top), abs(max_bottom)) + 1), max_w = 2 * (std::max(abs(max_left), abs(max_right)) + 1);
	std::vector<long long> v(max_h);
	segment_tree tree(v);
	int cur_begin = 0, cur_end = 0, max_x = -1, max_y = -1, max = INT32_MIN;
	for (int x = -max_w / 2; x < max_w / 2; x++) {
		while ((size_t)cur_begin < recs.size() && recs[cur_begin].left == x) {
			tree.add(recs[cur_begin].top + max_h / 2, recs[cur_begin].bottom + max_h / 2, 1);
			cur_begin++;
		}
		std::pair<long long, int> p = tree.get(0, max_h - 1);
		if (p.first > max) {
			max = int(p.first);
			max_x = x;
			max_y = p.second;
		}
		while ((size_t)cur_end < recs_sort_right.size() && recs_sort_right[cur_end].right == x) {
			tree.add(recs_sort_right[cur_end].top + max_h / 2, recs_sort_right[cur_end].bottom + max_h / 2, -1);
			cur_end++;
		}
	}
	std::cout << max << std::endl << max_x << " " << max_y - max_h / 2;
	return 0;
}
