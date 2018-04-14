#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common typedefs */
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* Dynamic programming definition */
typedef std::pair<int, int> dp_type; // first - min number, sec - k
typedef std::vector<std::vector<dp_type>> dp_array_type;

/* Common functions */
#define MIN(A, B, RES) ((A) < (B) ? (RES) = (A) : (RES) = (B))

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif

  return 0;
} /* End of 'main' function */