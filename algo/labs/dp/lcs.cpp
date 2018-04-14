#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#define LEFT 1
#define UP 2
#define DIAG 3
#define BOTH 4
/* Common typedefs */
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

struct dp_type {
  int first;
  char second;
};
/* Dynamic programming definition */
typedef std::vector<std::vector<dp_type>> dp_array_type;

/* Common functions */
#define MIN(A, B, RES) ((A) < (B) ? (RES) = (A) : (RES) = (B))
#define IS_LETTER(A) (((A) >= 'a' && (A) <= 'z') || (A) == '.')

/* Find maximum of two numbers */
int max(int a, int b) { if (a > b) return a; return b; }

/* Out result function */
void out_string(const dp_array_type &dp, int n, int m,
                       const std::string &a, const std::string &b) {
  if (dp[n][m].second == 0)
    return;

  if (dp[n][m].second == DIAG) {
    out_string(dp, n - 1, m - 1, a, b);
    printf("%c", a[n - 1]);
  }
  else if (dp[n][m].second == UP)
    out_string(dp, n - 1, m, a, b);
  else if (dp[n][m].second == LEFT || dp[n][m].second == BOTH)
    out_string(dp, n, m - 1, a, b);
}

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif
  std::string a, b;
  std::cin >> a >> b;
  int n = a.size(), m = b.size();

  dp_array_type dp(n + 1);
  for (int i = 0; i <= n; i++)
    dp[i].resize(m + 1);

  /* Fill dp[i][0] dp[0][j] */
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      if (i == 0 || j == 0)
        dp[i][j].first = 0;
      else
        dp[i][j].first = -1;

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (dp[i][j].first == -1) {
        if (a[i - 1] == b[j - 1]) {
          dp[i][j].first = dp[i - 1][j - 1].first + 1;
          dp[i][j].second = DIAG;
        }
        else {
          if (dp[i][j - 1].first > dp[i - 1][j].first) {
            dp[i][j].first = dp[i][j - 1].first;
            dp[i][j].second = LEFT;
          }
          else if (dp[i][j - 1].first == dp[i - 1][j].first) {
            dp[i][j].first = dp[i][j - 1].first;
            dp[i][j].second = BOTH;
          }
          else {
            dp[i][j].first = dp[i - 1][j].first;
            dp[i][j].second = UP;
          }
        }
      }
    }
  //out_string(dp, n, m, a, b);

  std::string out_str;
  while (dp[n][m].second != 0) {
    if (dp[n][m].second == DIAG) {
      out_str.push_back(a[n - 1]);
      n--; m--;
    }
    else if (dp[n][m].second == UP)
      n--;
    else if (dp[n][m].second == LEFT || dp[n][m].second == BOTH)
      m--;
  }

  for (int i = 0; i < (int)out_str.size(); i++) 
    printf("%c", out_str[out_str.size() - i - 1]);

  return 0;
} /* End of 'main' function */