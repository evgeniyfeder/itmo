#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C" {
	void _cdecl print(char *out_buf, const char *format, const char *hex_number);
}

char getRandFlag() {
	int n = rand() % 4;
	switch (n) {
	case 0:
		return '-';
	case 1:
		return '+';
	case 2:
		return '0';
	case 3:
		return ' ';
	}
}

void test_all_formats(long long n, int max_width) {
	char flags[5] = "0+- ";
	char hex[100];
	if (n < 0) {
		sprintf(hex, "-%llx", -n);
	}
	else {
		sprintf(hex, "%llx", n);
	}
	char format[100];
	char expected[1000];
	char result[1000];
	char sprintf_format[100];
	sprintf_format[0] = '%';

	for (int width = 0; width <= max_width; width++) {
		for (int j = 0; j < 16; j++) {
			int len = 0;
			//int ll = rand() % 20 + 1;
			for (int k = 0; k < 4; k++) {
				//for (int k = 0; k < ll; k++) {
				if ((j >> k) & 1) {
					format[len++] = flags[k];
				}
				//format[len++] = getRandFlag();
			}
			if (width != 0) {
				sprintf(format + len, "%d", width);
			}
			else {
				format[len] = 0;
			}
		}
	}
}

long long getRandomLongLong() {
	long long res = 0;
	for (int i = 0; i < 5; i++) {
		res = res * RAND_MAX + rand();
	}
	return res;
}

void test_short() {
	for (int i = -1000; i < 1000; i++) {
		test_all_formats(i, 30);
	}
}

void test_long_long() {
	for (int i = 0; i < 1000; i++) {
		test_all_formats(getRandomLongLong(), 30);
	}
}

struct ttest {
	char format[100];
	char input[100];
	char output[100];
};

#define SZ 12
void test_large() {
	struct ttest tests[SZ] = {
		{ "", "-1", "-1" },
	{ "", "ffffffffffffffffffffffffffffffff", "-1" },
	{ " ", "ffffffffffffffffffffffffffffffff", "-1" },
	{ " 5", "ffffffffffffffffffffffffffffffff", "   -1" },
	{ " 05", "ffffffffffffffffffffffffffffffff", "-0001" },
	{ "", "00000000100000000000000000000000", "4951760157141521099596496896" },
	{ "", "7c5782b53d4170541a351b103ca4c213", "165278652376525684276592475285263532563" },
	{ "+", "7c5782b53d4170541a351b103ca4c213", "+165278652376525684276592475285263532563" },
	{ "+0", "7c5782b53d4170541a351b103ca4c213", "+165278652376525684276592475285263532563" },
	{ "-   -", "-00beaddf674722fd57ab3", "-56278563523974562937523" },
	{ "45", "-2a56db690e95c23f00fdfc847847ee73", "      -56278563523974562937527265865276845683" },
	{ "-5", "10", "16   " }
	};
	for (int i = 0; i < SZ; i++) {
		char res[100];
		print(res, tests[i].format, tests[i].input);
		if (strcmp(res, tests[i].output) != 0) {
			printf("format: %s, result: %s, expected: %s.\n", tests[i].format, res, tests[i].output);
		}
	}

}

void test() {
	printf("test_large\n");
	test_large();
	printf("test_large: ok\n\n");

	printf("test_short\n");
	test_short();
	printf("test_short: ok\n\n");

	printf("test_long_long\n");
	test_long_long();
	printf("test_long_long: ok\n\n");

}

void main() {
	//char buf[100];
	//print(buf, "", "00000000000000000000000000000000");
	//printf("%s\n", buf);
	//srand(100500);
	test();
}