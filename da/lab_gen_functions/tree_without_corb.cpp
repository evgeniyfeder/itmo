#include <iostream>
#include <vector>

std::vector<int64_t> a, b;
std::vector<int64_t> b_rev;
static const int64_t MOD = 998244353;

int64_t get_a(int i) {
	if (i >= a.size())
		return 0;
	return a[i];
}

int64_t get_b(int i) {
	if (i >= b.size())
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
	int k, n;

	std::cin >> k >> n;

	std::vector<std::vector<uint64_t>> C(k + 1, std::vector<uint64_t>(k + 1));

	for (int n = 0; n <= k; ++n) {
		C[n][0] = C[n][n] = 1;
		for (int k = 1; k < n; ++k) {
			C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % MOD;
			while (C[n][k] < 0)
				C[n][k] += MOD;
		}
	}

	int a_end = ((k - 1) % 2 != 0 ? (k - 1) / 2 + 1 : (k - 1) / 2);
	int b_end = (k % 2 != 0 ? k / 2 + 1 : k / 2);

	for (int i = 0; i < a_end; i++) {
		a.push_back(C[k - 1 - i - 1][i] * (i % 2 == 0 ? 1 : -1));
	}
	for (int i = 0; i < b_end; i++) {
		b.push_back(C[k - i - 1][i] * (i % 2 == 0 ? 1 : -1));
	}

	b_rev.push_back(1 / get_b(0));

	for (int i = 1; i <= n; i++) {
		int64_t coof = 0;
		for (int j = 1; j <= i; j++) {
			coof = (coof + get_b(j) * get_br(i - j)) % MOD;
			while (coof < 0)
				coof += MOD;
		}
		b_rev.push_back((-coof / get_b(0) + MOD) % MOD);
		while (b_rev[b_rev.size() - 1] < 0)
			b_rev[b_rev.size() - 1] += MOD;
	}

	for (int i = 0; i < n; i++) {
		int64_t coof = 0;
		for (int j = 0; j <= i; j++) {
			coof = (coof + get_a(j) * get_br(i - j)) % MOD;
			while (coof < 0)
				coof += MOD;
		}
		std::cout << coof << '\n';
	}
}
