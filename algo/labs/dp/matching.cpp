#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common typedefs */
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* Dynamic programming definition */
typedef std::pair<int, ll> dp_type; // first - min number, sec - k
typedef std::vector<std::vector<dp_type>> dp_array_type;

/* Common functions */
#define MIN(A, B, RES) ((A) < (B) ? (RES) = (A) : (RES) = (B))
#define MAX_N 100010
ll max(ll a, ll b) { if (a > b) return a; return b; }

int was[MAX_N][2];
ll dp_count[MAX_N][2];

/* Depth search function */
ll dfs(const dp_array_type &graph, int parent,
  int v, int need_take) {
  ll res = INT16_MIN;
  if (was[v][need_take] == 1)
    return dp_count[v][need_take];

  was[v][need_take] = 1;

  ll sum = 0;
  for (int i = 0; i < (int)graph[v].size(); i++) {
    if (graph[v][i].first != parent) {
      sum += max(dfs(graph, v, graph[v][i].first, 0),
        dfs(graph, v, graph[v][i].first, 1));
    }
  }

  if (need_take == 0) {
    dp_count[v][need_take] = sum;
    return dp_count[v][need_take];
  }

  for (int i = 0; i < (int)graph[v].size(); i++) {
    if (graph[v][i].first != parent) {
      res = max(res, sum - max(dfs(graph, v, graph[v][i].first, 0),
        dfs(graph, v, graph[v][i].first, 1)) + graph[v][i].second + dfs(graph, v, graph[v][i].first, 0));
    }
  }
  if (res == INT16_MIN)
    res = 0;

  dp_count[v][need_take] = res;
  return dp_count[v][need_take];
} /* End of 'dfs' function' */
/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else
  freopen("matching.in", "r", stdin);
  freopen("matching.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);

  dp_array_type dp(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    ll w;
    scanf("%d%d%I64d", &a, &b, &w);
    dp[a - 1].push_back(std::pair<int, ll>(b - 1, w));
    dp[b - 1].push_back(std::pair<int, ll>(a - 1, w));
  }
  
  for (int i = 0; i < MAX_N; i++)
    for (int j = 0; j < 2; j++) {
      dp_count[i][j] = 0;
      was[i][j] = 0;
    }

  ll max_res = max(dfs(dp, INT32_MAX, 0, 1), dfs(dp, INT32_MAX, 0, 0));
  //for (int i = 0; i < n; i++)
  //  max_res = max(max_res, max(dfs(dp, INT32_MAX, i, 1), dfs(dp, INT32_MAX, i, 0)));
  printf("%I64d", max_res);
  return 0;
} /* End of 'main' function */