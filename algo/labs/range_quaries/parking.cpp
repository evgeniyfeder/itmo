#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
std::string file_name = "parking";

class parking_tree {
private:
	void update(int cur_ind) {
		if (heap[2 * cur_ind + 1] != NOT_EXIST) {
			heap[cur_ind] = heap[2 * cur_ind + 1];
		}
		else if (heap[2 * cur_ind] != NOT_EXIST)
			heap[cur_ind] = heap[2 * cur_ind];
		else
			heap[cur_ind] = NOT_EXIST;
	}
public:
	std::vector<long long> heap;
	int n;
	static const int NOT_EXIST = INT_MAX;

	void build_tree_rec(const std::vector<long long> &arr, int cur_ind, int left, int right) {
		if (left == right) {
			heap[cur_ind] = (arr[left] == 0 ? left : NOT_EXIST);
		}
		else {
			int middle = left + (right - left) / 2;
			build_tree_rec(arr, 2 * cur_ind, left, middle);
			build_tree_rec(arr, 2 * cur_ind + 1, middle + 1, right);
			update(cur_ind);
		}
	}

	parking_tree(const std::vector<long long> &arr) :
		n(arr.size()) {
		heap.resize(4 * n);
		build_tree_rec(arr, 1, 0, n - 1);
	}

	int enter_recur(int cur_vert, int left, int right, int ind) {
		if (left == right) {
			heap[cur_vert] = NOT_EXIST;
			return left;
		}
		else {
			int middle = left + (right - left) / 2, res = NOT_EXIST;
			if (heap[2 * cur_vert + 1] == NOT_EXIST)
				res = enter_recur(2 * cur_vert, left, middle, ind);
			else if (heap[2 * cur_vert] == NOT_EXIST)
				res = enter_recur(2 * cur_vert + 1, middle + 1, right, ind);
			else if (ind <= heap[2 * cur_vert])
				res = enter_recur(2 * cur_vert, left, middle, ind);
			else if (heap[2 * cur_vert] < ind && ind <= heap[2 * cur_vert + 1])
				res = enter_recur(2 * cur_vert + 1, middle + 1, right, ind);
			else if (heap[2 * cur_vert + 1] < ind)
				res = enter_recur(2 * cur_vert, left, middle, ind);
			update(cur_vert);
			return res;
		}
	}
	int enter(int ind) {
		return enter_recur(1, 0, n - 1, ind);
	}

	void exit_recur(int cur_vert, int left, int right, int ind) {
		if (left == right) {
			heap[cur_vert] = left;
		}
		else {
			int middle = left + (right - left) / 2;

			if (middle >= ind)
				exit_recur(2 * cur_vert, left, middle, ind);
			else
				exit_recur(2 * cur_vert + 1, middle + 1, right, ind);
			update(cur_vert);
		}
	}
	void exit(int ind) {
		exit_recur(1, 0, n - 1, ind);
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
	int n, m;
	std::cin >> n >> m;
	std::vector<long long> arr(n);
	parking_tree tree(arr);
	std::string key_word;
	for (int i = 0; i < m; i++) {
		int a;
		std::cin >> key_word >> a;
		if (key_word == "enter")
			std::cout << tree.enter(a - 1) + 1 << std::endl;
		else if (key_word == "exit")
			tree.exit(a - 1);
		key_word.clear();
	}
}