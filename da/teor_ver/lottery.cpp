#include <fstream>
#include <vector>
#include <cmath>

static std::string file_name;

/* The main function of program */
int main(void) {
#ifdef _DEBUG
	file_name = std::string("test");
#else
	file_name = std::string("lottery");
#endif
	FILE *InF, *OutF;
	InF = fopen((file_name + ".in").data(), "r");
	OutF = fopen((file_name + ".out").data(), "w");
	int n, m;
	fscanf(InF, "%d%d", &n, &m);

	double math_expect = 0, cur_prob = 1, prev_res = 0;
	for (int i = 1; i <= m; i++) {
		int num, res;

		fscanf(InF, "%d%d", &num, &res);

		math_expect += (double)prev_res * cur_prob * (1 - 1 / (double)num);
		prev_res = res;
		cur_prob /= num;
	}
	math_expect += (double)prev_res * cur_prob;

	fprintf(OutF, "%.10lf", n - math_expect);
	return 0;
} /* End of 'main' function */