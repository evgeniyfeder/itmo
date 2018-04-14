#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

/* Common typedefs */
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* Dynamic programming definition */
typedef std::pair<int, std::string> result; // first - min number, sec - string to out
typedef std::vector<std::vector<result>> dp_res;

/* Get minimum function */
int min(int a, int b) {
  if (a < b) return a;
  return b;
} /* End of 'min' function */

/* Matrix description */
struct matrix {
  int w, h;
private:
  /* Count recursive array of dinamic programming */
  static void count_dp( dp_res &dp,
    const std::vector<matrix> &matr, int left, int right) {
    if (dp[left][right].first == -1) {
      if (left == right - 1) {
        dp[left][right].first = 0;
        dp[left][right].second = "A";
      }
      else {
        dp[left][right].first = INT32_MAX;
        for (int i = left + 1; i < right; i++) {
          count_dp(dp, matr, left, i);
          count_dp(dp, matr, i, right);
          int cur_res = matr[left].w * matr[i - 1].h * matr[right - 1].h
            + dp[left][i].first + dp[i][right].first;

          if (dp[left][right].first > cur_res) {
            dp[left][right].first = cur_res;
            dp[left][right].second = "(" + dp[left][i].second + dp[i][right].second + ")";
          }
        }
      }
    }
  } /* End of 'count_dp' function */

public:
  /* Count multiply order function */
  static void count_order(
    const std::vector<matrix> &matr) {
    dp_res dp(matr.size() + 1);
    
    for (int i = 0; i <= (int)matr.size(); i++)
      dp[i].resize(matr.size() + 1);

    for (int i = 0; i <= (int)matr.size(); i++)
      for (int j = 0; j <= (int)matr.size(); j++)
        dp[i][j].first = -1;

    count_dp(dp, matr, 0, matr.size());
    printf("%s", dp[0][matr.size()].second.data());
  } /* End of 'count_order' function */
}; /* End of 'matrix' struct */

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else
  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);

  std::vector<matrix> matrices(n);
  for (int i = 0; i < n; i++) {
    int w, h;
    scanf("%d%d", &w, &h);
    matrices[i].w = w;
    matrices[i].h = h;
  }
  /*if (n == 3)
    printf("((AA)A)");*/
  matrix::count_order(matrices);
  return 0;
} /* End of 'main' function */