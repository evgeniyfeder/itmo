#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>


static const int64_t MOD = 998244353LL;
struct gen_func {
	std::vector<int64_t> data;

	int64_t get(size_t i) const {
		if (i >= data.size())
			return 0;
		return data[i];
	}

	gen_func(const std::vector<int64_t> &data) : data(data) {}

};

gen_func operator+(const gen_func &a, const gen_func &b) {
	size_t max = std::max(a.data.size(), b.data.size());

	std::vector<int64_t> res;
	for (size_t i = 0; i <= max; i++) {
		int64_t sum = 0;
		sum = (a.get(i) + b.get(i)) % MOD;
		res.push_back(sum);
	}
	return res;
}

gen_func operator*(const gen_func &a, const gen_func &b) {
	
}
int n, m;

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	std::cin >> n >> m;

	std::vector<int64_t> av, bv;
	std::vector<int64_t> b_revv;

	for (int i = 0; i <= n; i++) {
		uint64_t x;
		std::cin >> x;
		a.push_back(x);
	}

	for (int i = 0; i <= m; i++) {
		uint64_t x;
		std::cin >> x;
		b.push_back(x);
	}
	/* A + B */
	int max = std::max(n, m);
	std::cout << max << '\n';
	gen_func sum_res = a + b;
	for (int i = 0; i <= max; i++) {
		int sum = 0;
		sum = (get_a(i) + get_b(i)) % MOD;
		std::cout << sum << ' ';
	}
	std::cout << '\n';

	/* A * B */
	int sum_nm = n + m;
	std::cout << sum_nm << '\n';

	for (int i = 0; i <= sum_nm; i++) {
		int64_t coof = 0;
		for (int j = 0; j <= i; j++) {
			coof = (coof + get_a(j) * get_b(i - j)) % MOD;
		}
		std::cout << coof << ' ';
	}
	std::cout << '\n';

	/* A / B */
	/* B ^ (-1) */
	
	b_rev.push_back(1 / get_b(0));

	for (int i = 1; i <= 1000; i++) {
		int64_t coof = 0;
		for (int j = 1; j <= i; j++) {
			coof = (coof + get_b(j) * get_br(i - j) + MOD) % MOD;
		}
		b_rev.push_back((-coof / get_b(0) + MOD) % MOD);
	}

	for (int i = 0; i < 1000; i++) {
		int64_t coof = 0;
		for (int j = 0; j <= i; j++) {
			coof = (coof + get_a(j) * get_br(i - j)) % MOD;
		}
		std::cout << coof << ' ';
	}
}
