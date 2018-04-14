#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

/* Common typedefs */
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* Dynamic programming definition */
typedef int dp_type; // first - min number, sec - k
typedef std::vector<std::vector<dp_type>> dp_array_type;

/* Common functions */
#define MIN(A, B, RES) ((A) < (B) ? (RES) = (A) : (RES) = (B))

int min(int a, int b, int c) {
  if (a <= b && a <= c)
    return a;
  if (b <= a && b <= c)
    return b;
  return c;
}

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else
  freopen("levenshtein.in", "r", stdin);
  freopen("levenshtein.out", "w", stdout);
#endif
  std::string a, b;
  std::cin >> a >> b;

  int n = a.size(), m = b.size();
  dp_array_type dp(n + 1);

  for (int i = 0; i <= n; i++)
    dp[i].resize(m + 1);
  
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++) {
      if (i == 0)
        dp[i][j] = j;
      else if (j == 0)
        dp[i][j] = i;
      else
        dp[i][j] = -1;
    }
  
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (dp[i][j] == -1)
        dp[i][j] = min(dp[i - 1][j] + 1,
          dp[i][j - 1] + 1, dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
    }
  printf("%d", dp[n][m]);
  return 0;
} /* End of 'main' function */