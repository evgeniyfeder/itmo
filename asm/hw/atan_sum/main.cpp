#include <stdio.h>

extern "C" {  float __cdecl arctan(float x, unsigned int k); }

int main() {
	printf("%f", arctan(0.2, 2));
	return 0;
}