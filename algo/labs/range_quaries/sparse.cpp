#include <iostream>
#include <vector>
#include <algorithm>
std::string file_name = "sparse";

std::vector<std::vector<int32_t>> sparse;
std::vector<int32_t> arr;
std::vector<int> log_length;

int get_res(int left, int right) {
	left--, right--;
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

	uint32_t n, m;

	std::cin >> n >> m;

	arr.resize(n);
	std::cin >> arr[0];

	for (size_t i = 1; i < n; i++) {
		arr[i] = (23 * arr[i - 1] + 21563) % 16714589;
	}

	log_length.resize(n + 1);
	log_length[0] = -1;
	for (size_t i = 1; i <= n; i++) {
		log_length[i] = log_length[i - 1] + int((i & (i - 1)) == 0);
	}

	sparse.resize(n);
	uint32_t logn = log_length[n] + 1;
	for (size_t i = 0; i < n; i++) {
		sparse[i].resize(logn);
		sparse[i][0] = arr[i];
	}

	for (size_t step = 1; step < logn; step++) {
		for (size_t i = 0; i < n; i++) {
			if (i + (1 << (step - 1)) >= n)
				break;
			sparse[i][step] = std::min(sparse[i][step - 1], sparse[i + (1 << (step - 1))][step - 1]);
		}
	}

	int left, right, ans = 0;
	std::cin >> left >> right;
	ans = get_res(left, right);
	for (size_t i = 1; i < m; i++) {
		left = ((17 * left + 751 + ans + 2 * i) % n) + 1;
		right = ((13 * right + 593 + ans + 5 * i) % n) + 1;
		ans = get_res(left, right);
	}
	std::cout << left << " " << right << " " << ans;
}
