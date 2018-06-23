#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int64_t C(int64_t n, int64_t k) {
	int64_t res = 1;
	for (int i = n - k + 1; i <= n; ++i)
		res *= i;
	for (int i = 2; i <= k; ++i)
		res /= i;
	return res;
}

std::string line;
int cur_pos = 0;
static const int need_size = 7;

std::vector<int64_t> parse() {
	std::vector<int64_t> a, a1, res(need_size);
	switch (line[cur_pos]) {
	case 'B':
		cur_pos++;
		res = { 0, 1, 0, 0, 0, 0, 0 };
		break;
	case 'L':
		cur_pos += 2;
		a = parse();
		cur_pos++;
		res[0] = 1;
		for (int i = 1; i < need_size; i++) {
			int64_t sum = 0;
			for (int j = 1; j <= i; j++) {
				sum += a[j] * res[i - j];
			}
			res[i] = sum;
		}
		break;
	case 'S':
		cur_pos += 2;
		a = parse();
		cur_pos++;
		int64_t m[need_size][need_size];

		m[0][0] = 1;
		for (int i = 1; i < need_size; i++) {
			m[0][i] = 1;
			m[i][0] = 0;
		}

		res[0] = 1;
		for (int n = 1; n < need_size; n++) {
			for (int k = 1; k < need_size; k++) {
				int64_t sum = 0;
				for (int i = 0; i <= n / k ; i++) {
					sum += C(std::max(a[k] + i - 1, 0LL), i) * m[n - i * k][k - 1];
				}
				m[n][k] = sum;
			}
			res[n] = m[n][n];
		}
		break;
	case 'C':
		cur_pos += 2;
		a = parse();
		cur_pos++;

		int64_t b[need_size][need_size];
		for (int n = 0; n < need_size; n++) {
			b[n][1] = a[n];
			b[n][0] = 0;
			b[0][n] = 0;
		}

		for (int n = 1; n < need_size; n++) {
			for (int k = 2; k < need_size; k++) {
				int64_t sum = 0;
				for (int i = 1; i < n; i++) {
					sum += a[i] * b[n - i][k - 1];
				}
				b[n][k] = sum;
			}
		}
		res[0] = 0;
		for (int n = 1; n < need_size; n++) {
			int64_t sum = 0;
			for (int s = 1; s <= n; s++) {
				int64_t up = 0;
				for (int i = 0; i <= s - 1; i++) {
					int g = gcd(s, i);
					int64_t sti = (n % (s / g) != 0 ? 0 : b[(n * g) / s][g]);
					up += sti;
				}
				sum += up / s;
			}
			res[n] = sum;
		}
		break;
	case 'P':
		cur_pos += 2;
		a = parse();
		cur_pos++;
		a1 = parse();
		cur_pos++;
		for (int i = 0; i < need_size; i++) {
			int64_t sum = 0;
			for (int j = 0; j <= i; j++) {
				sum += a[j] * a1[i - j];
			}
			res[i] = sum;
		}
		break;
	}
	return res;
}
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	std::getline(std::cin, line);
	std::vector<int64_t> res = parse();
	for (int i = 0; i < need_size; i++) {
		std::cout << res[i] << " ";
	}
}
