#include <stdio.h>
#include <stdint.h>
#include <cassert>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void dbl2str(double in, char *out_buf);

int is_shortest(double res, char* buf) {
	if (strcmp(buf, "NaN") == 0 || strcmp(buf, "+Inf") == 0 || strcmp(buf, "-Inf") == 0) {
		return 1;
	}
	char str[1000];
	strcpy(str, buf);
	int len = strlen(str);
	for (int i = 0; i < len - 1; i++) {
		if (str[i + 1] == 'e') {
			if (str[i - 1] != '.') {
				for (int j = i; j < len - 1; j++) {
					str[j] = str[j + 1];
				}
				str[len - 1] = 0;
				double less_accurate;
				sscanf(str, "%lf", &less_accurate);
				if (less_accurate == res) {
					return 0;
				}
				if (str[i - 1] != '9') {
					str[i - 1]++;
					sscanf(str, "%lf", &less_accurate);
					if (less_accurate == res) {
						return 0;
					}
				}
				if (str[i - 1] != '1') {
					str[i - 1] -= 2;
					sscanf(str, "%lf", &less_accurate);
					if (less_accurate == res) {
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int is_correct(double res, char* buf) {
	double expect;
	sscanf(buf, "%lf", &expect);
	if (!isnan(res) && res != expect || isnan(res) != isnan(expect)) {
		printf("correctness fail: res = %lf expect = %lf buf = %s\n", res, expect, buf);
		return 0;
	}
	return 1;
}

struct test_case {
	double v;
	char* expect;
};

int test_cases(void(*fun)(const double*, char*)) {
	printf("test_cases...\n");
	struct test_case a[] = {
		{ 22345678987654323.0, "+0.22345678987654324e17" },
	{ 0.0, "+0.0e0" },
	{ -0.0, "-0.0e0" },
	{ NAN, "NaN" },
	{ INFINITY, "+Inf" },
	{ -INFINITY, "-Inf" },
	{ 0.7e-323, "+0.7e-323" }
	};

	char buf[1000];
	for (int i = 0; i < 7; i++) { // <------------------------ arr_sz !!!!!
		fun(&(a[i].v), buf);
		if (strcmp(buf, a[i].expect) != 0) {
			printf("fail test_case #%d: v = %lf buf = %s expect = %s\n", i, a[i].v, buf, a[i].expect);
		}
	}
	fflush(stdout);
	return 1;
}

double toDouble(uint64_t v) {
	return *(double*)&v;
}

uint64_t getRand64() {
	uint64_t res = 0;
	for (int i = 0; i < 5; i++) {
		res = res * RAND_MAX + rand();
	}
	return res;
}

int hhh = 0;

void random(void(*fun)(const double*, char*)) {
	printf("random...\n");
	clock_t t = clock();
	int n = 1000000; // test_sz
	int k = 0;
	for (int i = 0; i < n; i++) {
		double x = toDouble(getRand64());
		char buf[1000];
		fun(&x, buf);
		if (strlen(buf) > hhh) {
			hhh = strlen(buf);
		}
		if (!is_correct(x, buf)) {
			printf("is not correct\n");
		}
		if (!is_shortest(x, buf)) {
			k++;
		}
	}
	printf("time: %fs\n", (clock() - t) / (float)CLOCKS_PER_SEC);
	printf("not shortest: %.2lf%%\n", 100 * k / (double)n);
	fflush(stdout);
}

void denormals(void(*fun)(const double*, char*)) {
	printf("denormals...\n");
	char buf[1000];
	int k = 0;
	int n = 1000000; // test_sz
	for (uint64_t x = 1; x < n; x++) { // <--- todo from 1
		double d = toDouble(x);
		fun(&d, buf);
		if (strlen(buf) > hhh) {
			hhh = strlen(buf);
		}
		if (!is_correct(d, buf)) {
			printf("is not correct\n");
		}
		if (!is_shortest(d, buf)) {
			k++;
		}
	}
	printf("not shortest: %.2lf%%\n", 100 * k / (double)n);
	fflush(stdout);
}

void edge_cases(void(*fun)(const double*, char*)) {
	printf("edge_cases...\n");
	char buf[1000];
	for (uint64_t exp = 1; exp < 2048; exp++) {
		double val = toDouble(exp << 52);
		fun(&val, buf);
		if (!is_correct(val, buf)) {
			printf("is not correct: %.16llx\n", val);
		}
	}
	for (uint64_t exp = 1; exp < 2048; exp++) {
		double val = toDouble((exp << 52) | 0x0001111111111111);
		fun(&val, buf);
		if (!is_correct(val, buf)) {
			printf("is not correct: %.16llx\n", val);
		}
	}
	fflush(stdout);
}

void test_asm() {
	//test_cases(dbl2str);
	random(dbl2str);
	//denormals(dbl2str);
	edge_cases(dbl2str);
	printf("max_ans_len = %d\n", hhh);
}

int main() {
	double a = -1.4224536348818210e-188;
	char buf[1000];
	dbl2str(a, buf);
	test_asm();
}