#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common typedefs */
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* Dynamic programming definition */
typedef ll dp_type; // first - min number, sec - k
typedef std::vector<std::vector<dp_type>> dp_array_type;
#define MAX_NUM 1000000000

/* Common functions */
#define MIN(A, B, RES) ((A) < (B) ? (RES) = (A) : (RES) = (B))
/* Find maximum of two numbers */
ll max(ll a, ll b) { if (a > b) return a; return b; }

/* Count dp result function */
dp_type count_dp(const std::vector<ll> &arr,
  dp_array_type &dp, int l, int r) {
  if (dp[l][r] != -1)
    return dp[l][r];

  if (arr[l] != arr[r])
    dp[l][r] = (count_dp(arr, dp, l + 1, r) +
      count_dp(arr, dp, l, r - 1) + MAX_NUM - count_dp(arr, dp, l + 1, r - 1)) % MAX_NUM;
  else 
    dp[l][r] = (count_dp(arr, dp, l + 1, r) +
    count_dp(arr, dp, l, r - 1) + 1) % MAX_NUM;
  return dp[l][r];
}

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);

  std::vector<ll> mas(n);
  for (int i = 0; i < n; i++)
    scanf("%I64d", &mas[i]);

  dp_array_type dp(n + 1);

  for (int i = 0; i < n; i++)
    dp[i].resize(n);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      if (i > j)
        dp[i][j] = 0;
      else if (i == j)
        dp[i][j] = 1;
      else
        dp[i][j] = -1;
    }
  count_dp(mas, dp, 0, n - 1);
  printf("%I64d", (dp[0][n - 1]) % MAX_NUM);
  return 0;
} /* End of 'main' function */