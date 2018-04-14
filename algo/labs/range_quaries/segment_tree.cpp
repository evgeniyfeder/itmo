#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
std::string file_name = "crypto";
long long r;
template <typename T>
class segment_tree {
public:
	std::vector<T> heap;
	int n;
	T neutral_elem;
	T(*operation)(const T&, const T&);

	void build_tree_rec(const std::vector<T> &arr, int cur_ind, int left, int right) {
		if (left == right) {
			heap[cur_ind] = arr[left];
		}
		else {
			int middle = left + (right - left) / 2;
			build_tree_rec(arr, 2 * cur_ind, left, middle);
			build_tree_rec(arr, 2 * cur_ind + 1, middle + 1, right);
			heap[cur_ind] = operation(heap[2 * cur_ind], heap[2 * cur_ind + 1]);
		}

	}

	segment_tree(const std::vector<T> &arr, T(*f)(const T &, const T &), const T &neutral_elem) :
		n(arr.size()), neutral_elem(neutral_elem), operation(f) {
		heap.resize(4 * n);
		for (size_t i = 0; i < heap.size(); i++)
			heap[i] = neutral_elem;
		build_tree_rec(arr, 1, 0, n - 1);
	}

	T get_recur(int cur_vert, int cur_left, int cur_right, int get_left, int get_right) {
		if (get_right < get_left)
			return neutral_elem;
		if (cur_left == get_left && cur_right == get_right)
			return heap[cur_vert];

		int middle = cur_left + (cur_right - cur_left) / 2;
		return operation(get_recur(2 * cur_vert, cur_left, middle, get_left, std::min(get_right, middle)),
			get_recur(2 * cur_vert + 1, middle + 1, cur_right, std::max(get_left, middle + 1), get_right));
	}

	T get(int left, int right) {
		return get_recur(1, 0, n - 1, left, right);
	}

	void set_recur(int cur_vert, int left, int right, int ind, const T &x) {
		if (left == right)
			heap[cur_vert] = x;
		else {
			int middle = left + (right - left) / 2;
			if (middle >= ind)
				set_recur(2 * cur_vert, left, middle, ind, x);
			else
				set_recur(2 * cur_vert + 1, middle + 1, right, ind, x);
			heap[cur_vert] = operation(heap[2 * cur_vert], heap[2 * cur_vert + 1]);
		}
	}
	void set(int ind, const T &x) {
		set_recur(1, 0, n - 1, ind, x);
	}
};
struct matrix {
	long long data[2][2];
	matrix(long long a = 1, long long b = 0, long long c = 0, long long d = 1) {
		data[0][0] = a;
		data[0][1] = b;
		data[1][0] = c;
		data[1][1] = d;
	}
};
matrix f(const matrix &a, const matrix &b) {
	return matrix(
		(a.data[0][0] * b.data[0][0] + a.data[0][1] * b.data[1][0]) % r,
		(a.data[0][0] * b.data[0][1] + a.data[0][1] * b.data[1][1]) % r,
		(a.data[1][0] * b.data[0][0] + a.data[1][1] * b.data[1][0]) % r,
		(a.data[1][0] * b.data[0][1] + a.data[1][1] * b.data[1][1]) % r);
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
	int n, m;
	//std::cin >> r >> n >> m;
	scanf("%lld%d%d", &r, &n, &m);
	std::vector<matrix> arr(n);
	for (int i = 0; i < n; i++) {
		long long a, b, c, d;
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		//std::cin >> a >> b >> c >> d;
		arr[i] = matrix(a, b, c, d);
	}

	segment_tree<matrix> tree(arr, f, matrix());
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		//std::cin >> a >> b;
		matrix res = tree.get(a - 1, b - 1);
		printf("%lld %lld\n%lld %lld\n\n", res.data[0][0], res.data[0][1], res.data[1][0], res.data[1][1]);
		//std::cout << res.data[0][0] << " " << res.data[0][1] << std::endl << res.data[1][0] << " " << res.data[1][1] << std::endl << std::endl;
	}
}