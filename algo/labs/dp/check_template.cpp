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
typedef bool dp_type; // first - min number, sec - k
typedef std::vector<std::vector<dp_type>> dp_array_type;

/* Common functions */
#define MIN(A, B, RES) ((A) < (B) ? (RES) = (A) : (RES) = (B))
#define IS_LETTER(A) (((A) >= 'a' && (A) <= 'z') || (A) == '.' || (A) == '#' || (A) == '$')
#define MAX_NUM 10010
int max(int a, int b) { if (a > b) return a; return b; }

int max(int a, int b, int c) {
  if (a >= b && a >= c)
    return a;
  if (b >= a && b >= c)
    return b;
  return c;
}
bool dp[MAX_NUM][MAX_NUM];
/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif
  std::string a, b;
  std::cin >> a >> b;
  a = '#' + a + '$';
  b = '#' + b + '$';
  
  int n = a.size(), m = b.size();
  /*dp_array_type dp(n);
  for (int i = 0; i < n; i++)
    dp[i].resize(m + 1);*/

  dp[0][0] = true;

  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < m - 1; j++) {
      /* It's right template */
      if (dp[i][j] == 1) {
        /* Next - letter */
        if (IS_LETTER(a[i + 1])) {
          if (a[i + 1] == b[j + 1])
            dp[i + 1][j + 1] = dp[i][j];
        }
        else if (a[i + 1] == '?') {
          /* Bad case */
          if (b[i + 1] != '$')
            dp[i + 1][j + 1] = dp[i][j];
        }
        else if (a[i + 1] == '*') {
          if (b[j + 1] != '$')
            dp[i][j + 1] = dp[i][j];
          dp[i + 1][j] = dp[i][j];
        }
      }
    }
  if (dp[n - 1][m - 1] == 1)
    printf("YES");
  else
    printf("NO");
  return 0;
} /* End of 'main' function */