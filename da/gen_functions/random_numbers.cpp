#include <iostream>
#include <vector>

static const int64_t MOD = 104857601;

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	int k;
	int64_t n;
	std::cin >> k >> n;
	n--;
	std::vector<int64_t> begins(2 * k);
	std::vector<int64_t> q(k + 1);

	for (int i = 0; i < k; i++) {
		int64_t x;
		std::cin >> x;
		begins[i] = x;
	}

	q[0] = 1;
	for (int i = 1; i <= k; i++) {
		int64_t x;
		std::cin >> x;
		q[i] = (-x + MOD) % MOD;
	}

	std::vector<int64_t> r(k + 1);
	std::vector<int64_t> neg_q(k + 1);

	while (n >= k) {
		for (int i = k; i < 2 * k; i++) {
			begins[i] = 0;
			for (int j = 1; j <= k; j++) {
				begins[i] = (begins[i] - q[j] * begins[i - j]) % MOD;
				while (begins[i] < 0)
					begins[i] += MOD;
			}
		}

		for (int i = 0; i <= k; i++) {
			neg_q[i] = (i % 2 == 0 ? q[i] : (-q[i] + MOD) % MOD);
		}

		for (int i = 0; i <= 2 * k; i += 2) {
			int64_t coof = 0;
			for (int j = 0; j <= i; j++) {
				int64_t aj = (j > k ? 0 : q[j]);
				int64_t bij = (i - j > k ? 0 : neg_q[i - j]);
					
				coof = (coof + aj * bij + MOD) % MOD;
			}
			r[i / 2] = coof;
		}
		for (int i = 0; i <= k; i++) {
			q[i] = r[i];
		}

		int cur_free = 0;
		for (int i = 0; i < 2 * k; i++) {
			if (n % 2 == i % 2) {
				begins[cur_free] = begins[i];
				cur_free++;
			}
		}
		n = n / 2;
	}
	std::cout << begins[n];
}
