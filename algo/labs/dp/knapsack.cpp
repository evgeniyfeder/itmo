#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common typedefs */
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* Dynamic programming definition */
typedef int dp_type; // first - min number, sec - k
typedef std::vector<std::vector<dp_type>> dp_array_type;

/* Common functions */
#define MIN(A, B, RES) ((A) < (B) ? (RES) = (A) : (RES) = (B))
int max(int a, int b) { if (a > b) return a; return b; }

/* One thing class */
struct thing {
  int weight, cell;

  /* Count dp function array function */
  static dp_type count_dp(const std::vector<thing> &things, dp_array_type &dp,
                   int num_thing, int cur_weight) {
    if (num_thing <= 0 || cur_weight <= 0)
      return 0;
    else if (dp[num_thing][cur_weight] != -1)
      return dp[num_thing][cur_weight];
    else {
      if (things[num_thing - 1].weight <= cur_weight)
        dp[num_thing][cur_weight] = max(
          count_dp(things, dp, num_thing - 1, cur_weight),
          count_dp(things, dp, num_thing - 1, cur_weight
            - things[num_thing - 1].weight) + things[num_thing - 1].cell);
      else
        dp[num_thing][cur_weight] = count_dp(things, dp, num_thing - 1, cur_weight);
    }
    return dp[num_thing][cur_weight];
  } /* End of 'count_dp' function */

  /* Start and out dp function */
  static void count_backpack(const std::vector<thing> &things, int max_weight) {
    int n = things.size();
    dp_array_type dp(n + 1);

    for (int i = 0; i <= n; i++)
      dp[i].resize(max_weight + 1);

    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= max_weight; j++)
        dp[i][j] = (i == 0 || j == 0 ? 0 : -1);

    //count_dp(things, dp, n, max_weight);
    for (int t = 1; t <= n; t++)
      for (int w = 1; w <= max_weight; w++)
        if (things[t - 1].weight <= w)
          dp[t][w] = max(dp[t - 1][w],
            dp[t - 1][w - things[t - 1].weight] + things[t - 1].cell);
        else
          dp[t][w] = dp[t - 1][w];

    std::vector<int> res;
    for (int i = n; i > 0; i--)
      if (dp[i][max_weight] != dp[i - 1][max_weight])
        res.push_back(i), max_weight -= things[i - 1].weight;

    printf("%d\n", res.size());

    for (int i = 0; i < (int)res.size(); i++)
      printf("%d ", res[res.size() - i - 1]);
  } /* End of 'count_backpack' function */
}; /* End of 'thing' struct */

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else
  freopen("knapsack.in", "r", stdin);
  freopen("knapsack.out", "w", stdout);
#endif
  int n, max_w;
  scanf("%d%d", &n, &max_w);

  std::vector<thing> things(n);

  for (int i = 0; i < n; i++)
    scanf("%d", &things[i].weight);

  for (int i = 0; i < n; i++)
    scanf("%d", &things[i].cell);

  thing::count_backpack(things, max_w);
  return 0;
} /* End of 'main' function */