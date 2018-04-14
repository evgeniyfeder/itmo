#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
std::string file_name = "rmq2";
unsigned long long mod = 1000000000000000000LL;
class segment_tree {
	struct node {
		long long add, set;
		long long min;

		node() : add(0), set(NOT_SET), min(NOT_SET) {
		}
	};

	void push(int cur) {
		int left = 2 * cur, right = 2 * cur + 1;
		if (heap[cur].set != NOT_SET) {
			if (heap[left].add != NOT_SET)
				heap[left].add = NOT_SET;
			if (heap[right].add != NOT_SET)
				heap[right].add = NOT_SET;

			heap[left].set = heap[cur].set;
			heap[right].set = heap[cur].set;

			heap[left].min = heap[cur].min;
			heap[right].min = heap[cur].min;
		}
		else {
			if (heap[left].add != NOT_SET)
				heap[left].add += heap[cur].add;
			else
				heap[left].set += heap[cur].add;
			heap[left].min += heap[cur].add;

			if (heap[right].add != NOT_SET)
				heap[right].add += heap[cur].add;
			else
				heap[right].set += heap[cur].add;
			heap[right].min += heap[cur].add;
		}
		heap[cur].set = NOT_SET;
		heap[cur].add = 0;
	}

public:
	std::vector<node> heap;
	int n;
	static const long long NOT_SET = 1ULL << 60;

	void build_tree_rec(const std::vector<long long> &arr, int cur_ind, int left, int right) {
		if (left == right) {
			heap[cur_ind].min = arr[left];
			heap[cur_ind].set = arr[left];
			heap[cur_ind].add = NOT_SET;
		}
		else {
			int middle = left + (right - left) / 2;
			build_tree_rec(arr, 2 * cur_ind, left, middle);
			build_tree_rec(arr, 2 * cur_ind + 1, middle + 1, right);
			heap[cur_ind].min = std::min(heap[2 * cur_ind].min, heap[2 * cur_ind + 1].min);
		}

	}

	explicit segment_tree(const std::vector<long long> &arr) :
		heap(4 * arr.size()), n(arr.size()) {
		build_tree_rec(arr, 1, 0, n - 1);
	}

	void set_recur(int cur_vert, int left, int right, int ind_left, int ind_right, long long x) {
		if (ind_right < ind_left)
			return;

		if (left == ind_left && right == ind_right) {
			heap[cur_vert].set = x;
			heap[cur_vert].min = x;
			heap[cur_vert].add = NOT_SET;
		}
		else {
			int middle = left + (right - left) / 2;
			push(cur_vert);
			set_recur(2 * cur_vert, left, middle, ind_left, std::min(ind_right, middle), x);
			set_recur(2 * cur_vert + 1, middle + 1, right, std::max(ind_left, middle + 1), ind_right, x);
			heap[cur_vert].min = std::min(heap[2 * cur_vert].min, heap[2 * cur_vert + 1].min);
		}
	}
	void set(int ind_left, int ind_right, long long x) {
		set_recur(1, 0, n - 1, ind_left, ind_right, x);
	}

	void add_recur(int cur_vert, int left, int right, int ind_left, int ind_right, long long x) {
		if (ind_right < ind_left)
			return;

		if (left == ind_left && right == ind_right) {
			if (heap[cur_vert].set == NOT_SET)
				heap[cur_vert].add += x;
			else
				heap[cur_vert].set += x;
			heap[cur_vert].min += x;
		}
		else {
			int middle = left + (right - left) / 2;
			push(cur_vert);
		    add_recur(2 * cur_vert, left, middle, ind_left, std::min(ind_right, middle), x);
			add_recur(2 * cur_vert + 1, middle + 1, right, std::max(ind_left, middle + 1), ind_right, x);
			heap[cur_vert].min = std::min(heap[2 * cur_vert].min, heap[2 * cur_vert + 1].min);
		}
	}
	void add(int left, int right, long long x) {
		add_recur(1, 0, n - 1, left, right, x);
	}

	long long min_recur(int cur_vert, int left, int right, int ind_left, int ind_right) {
		if (ind_right < ind_left)
			return NOT_SET;
		if (left == ind_left && right == ind_right)
			return heap[cur_vert].min;
		
		push(cur_vert);
		int middle = left + (right - left) / 2;
		return std::min(min_recur(2 * cur_vert, left, middle, ind_left, std::min(ind_right, middle)),
			min_recur(2 * cur_vert + 1, middle + 1, right, std::max(ind_left, middle + 1), ind_right));
	}

	long long min(int left, int right) {
		return min_recur(1, 0, n - 1, left, right);
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
	std::ios_base::sync_with_stdio(false);
	int n;
	std::cin >> n;
	std::vector<long long> arr(n);
	for (int i = 0; i < n; i++) {
		long long a;
		std::cin >> a;
		arr[i] = a;
	}
	segment_tree tree(arr);
	std::string key_word;
	while (std::cin >> key_word) {
		if (key_word == "min") {
			int a, b;
			std::cin >> a >> b;
			std::cout << tree.min(a - 1, b - 1) << std::endl;
		}
		else if (key_word == "set") {
			int left, right;
			long long b;
			std::cin >> left >> right >> b;
			tree.set(left - 1, right - 1, b);
		}
		else if (key_word == "add") {
			int left, right;
			long long b;
			std::cin >> left >> right >> b;
			tree.add(left - 1, right - 1, b);
		}
		key_word.clear();
	}
}