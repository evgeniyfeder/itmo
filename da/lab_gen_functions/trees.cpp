#include <string>
#include <vector>
#include <iostream>

typedef std::vector<uint64_t> vec64;
static const int64_t MOD = 1000000007LL;
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	int k, m;
	std::cin >> k >> m;

	vec64 nodes(m + 1, 0);
	for (int i = 0; i < k; i++) {
		int x;
		std::cin >> x;
		nodes[x] = 1;
	}

	vec64 trees(m + 1);
	trees[0] = 1;
	
	vec64 prefix_sum(m + 1);
	prefix_sum[0] = 1;
	for (int i = 1; i <= m; i++) { // i - cur tree w
		int64_t sum = 0;
		for (int j = 1; j <= i; j++) { // j - cur root w
			if (nodes[j] == 0)
				continue;
			sum += prefix_sum[i - j] % MOD;
		}
		trees[i] = sum % MOD;

		for (int j = 0; j <= i; j++)
			prefix_sum[i] = (prefix_sum[i] + trees[j] * trees[i - j]) % MOD;

		std::cout << trees[i] << ' ';
	}

}
