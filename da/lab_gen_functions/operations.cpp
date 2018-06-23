#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int64_t> a, b;
std::vector<int64_t> b_rev;

int n, m;
static const int64_t MOD = 998244353LL;
int64_t get_a(int i) {
	if (i > n)
		return 0;
	return a[i];
}

int64_t get_b(int i) {
	if (i > m)
		return 0;
	return b[i];
}

int64_t get_br(int i) {
	if (i >= (int)b_rev.size())
		return 0;
	return b_rev[i];
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	std::cin >> n >> m;


	for (int i = 0; i <= n; i++) {
		int64_t x;
		std::cin >> x;
		a.push_back(x);
	}

	for (int i = 0; i <= m; i++) {
		int64_t x;
		std::cin >> x;
		b.push_back(x);
	}
	/* A + B */
	int max = std::max(n, m);
	std::cout << max << '\n';
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