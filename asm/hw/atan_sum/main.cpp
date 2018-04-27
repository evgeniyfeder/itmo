#include <stdio.h>

extern "C" {  
	float __cdecl arctan(float x, unsigned int k);
	float __cdecl arctan_simd(float x, unsigned int k);
}

int main() {
	printf("%f\n", 4 * arctan_simd(1, 100000000));
	printf("%f", 4 * arctan(1, 100000000));
	return 0;
}