#include <fstream>

static std::string file_name;

/* The main function of program */
int main(void) {
#ifdef _DEBUG
	file_name = std::string("test");
#else
	file_name = std::string("");
#endif
	FILE *InF, *OutF;
	InF = fopen((file_name + ".in").data(), "r");
	OutF = fopen((file_name + ".out").data(), "r");

	return 0;
} /* End of 'main' function */