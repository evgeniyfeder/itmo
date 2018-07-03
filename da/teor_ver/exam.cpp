#include <fstream>
#include <vector>

static std::string file_name;

/* The main function of program */
int main(void) {
#ifdef _DEBUG
	file_name = std::string("test");
#else
	file_name = std::string("exam");
#endif
	FILE *InF, *OutF;
	InF = fopen((file_name + ".in").data(), "r");
	OutF = fopen((file_name + ".out").data(), "w");
	int n, m;
	fscanf(InF, "%d%d", &n, &m);

	double prob = 0;
	for (int i = 0; i < n; i++) {
		int num_stud;
		double seccess;

		fscanf(InF, "%d%lf", &num_stud, &seccess);
		seccess /= 100;
		prob += (double)num_stud / m * seccess;
	}
	fprintf(OutF, "%.5lf", prob);
	return 0;
} /* End of 'main' function */