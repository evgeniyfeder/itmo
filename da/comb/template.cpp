#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common definitions */
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else 
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif


  return 0;
} /* End of 'main' function */