#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common typedefs */
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* Struct of one dp element */
struct dp_type {
  int var, ind, prev;
}; /* End of 'dp_type' struct */

/* Dynamic programming definition */
typedef std::vector<dp_type> dp_array_type;

/* Common functions */
#define MIN(A, B, RES) ((A) < (B) ? (RES) = (A) : (RES) = (B))

/* Binary search function */
int binary_search(const dp_array_type &arr, int x, int l, int r) {
  int med = l + (r - l) / 2;
  if (l == r - 1)
    return r;
  if (arr[med].var > x)
    return binary_search(arr, x, l, med);
  else if (arr[med].var == x)
    return med;
  else
    return binary_search(arr, x, med, r);
} /* End of 'binary_search' function */

/* Find lis function */
void findLIS(const std::vector<int> &sequence) {
  int n = sequence.size(), max_len = 0;
  dp_array_type dp(n + 1);
  
  dp[0].var = INT32_MIN;
  dp[0].ind = -1;
  for (int i = 1; i <= n; i++) {
    dp[i].var = INT32_MAX;
    dp[i].prev = -1;
  }

  for (int i = 0; i < n; i++) {
    int j = binary_search(dp, sequence[i], 0, n);
    if (dp[j - 1].var < sequence[i] && sequence[i] < dp[j].var) {
      dp[j].var = sequence[i];
      dp[j].ind = i;
      dp[i].prev = dp[j - 1].ind;
      
      if (max_len < j)
        max_len = j;
    }
  }
  printf("%d\n", max_len);

  int p = dp[max_len].ind;
  std::vector<int> ans;
  while (p != -1) {
    ans.push_back(sequence[p]);
    p = dp[p].prev;
  }

  for (int i = 0; i < max_len; i++)
    printf("%d ", ans[max_len - 1 - i]);
} /* End of 'FindLIS' function */


/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else
  freopen("lis.in", "r", stdin);
  freopen("lis.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);
  //n = 300000;
  std::vector<int> seq(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &seq[i]);
    //seq[i] = 999999999 - n + i;
  }
  findLIS(seq);
  return 0;
} /* End of 'main' function */