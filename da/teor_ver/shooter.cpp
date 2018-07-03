#include <fstream>
#include <vector>
#include <cmath>

static std::string file_name;

/* The main function of program */
int main(void) {
#ifdef _DEBUG
	file_name = std::string("test");
#else
	file_name = std::string("shooter");
#endif
	FILE *InF, *OutF;
	InF = fopen((file_name + ".in").data(), "r");
	OutF = fopen((file_name + ".out").data(), "w");
	int n, m, k;
	fscanf(InF, "%d%d%d", &n, &m, &k);

	double complete = 0, prob_k_shooter = 0;
	for (int i = 1; i <= n; i++) {
		double seccess;

		fscanf(InF, "%lf", &seccess);

		if (i == k)
			prob_k_shooter = pow(1 - seccess, m) / n;

		complete += pow(1 - seccess, m) / n;
	}
	fprintf(OutF, "%.13lf", prob_k_shooter / complete);
	return 0;
} /* End of 'main' function */