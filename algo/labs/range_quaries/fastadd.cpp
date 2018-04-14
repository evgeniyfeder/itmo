#include <iostream>
#include <vector>
std::string file_name = "fastadd";

typedef unsigned int uint;
std::vector<uint32_t> sum_prefix;
std::vector<uint32_t> deriv;

uint a, b;
uint cur = 0;
uint nextRand() {
	cur = cur * a + b;
	return cur >> 8;
}

void nextAddition(uint &add, uint &l, uint &r) {
	add = nextRand();
	l = nextRand();
	r = nextRand();
	if (l > r) std::swap(l, r);
}

void nextSum(uint &l, uint &r) {
	l = nextRand();
	r = nextRand();
	if (l > r) std::swap(l, r);
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif

	uint add_cnt, sum_cnt;
	std::cin >> add_cnt >> sum_cnt >> a >> b;

	deriv.resize((1 << 24) + 1);
	//sum_prefix.resize(1 << 24);
	for (size_t i = 0; i < add_cnt; i++) {
		uint l, r, add;

		nextAddition(add, l, r);
		deriv[l] += add;
		deriv[r + 1] -= add;
	}

	for (size_t i = 1; i < deriv.size() - 1; i++) {
		deriv[i] += deriv[i - 1];
	}

	for (size_t i = 1; i < deriv.size() - 1; i++) {
		deriv[i] += deriv[i - 1];
	}

	/* int32_t prev = 0, prev_sum = 0;
	for (size_t i = 0; i < deriv.size(); i++) {
		int32_t cur = prev + deriv[i];
		sum_prefix[i] = cur + prev_sum;
		prev = cur;
		prev_sum = sum_prefix[i];
	} */

	uint32_t sum_res = 0;
	for (size_t i = 0; i < add_cnt; i++) {
		uint l, r;

		nextSum(l, r);
		sum_res += deriv[r] - (l ? deriv[l - 1] : 0);
	}
	std::cout << sum_res;
	return 0;
}