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
#define MAX_N 20
ll min(ll a, ll b) { if (a < b) return a; return b; }

ll dp_count[MAX_N][1 << MAX_N];

/* Depth search function */
ll dfs(const dp_array_type &graph, int v, int n, ll was) {
  ll res = INT32_MAX;
  if (n == (int)graph.size())
    return 0;
  if (dp_count[v][was] != -1)
    return dp_count[v][was];

  for (int i = 0; i < (int)graph[v].size(); i++) {
    if ((was & (1LL << graph[v][i].first)) == 0) {
      res = min(res, dfs(graph, graph[v][i].first, n + 1, was + (1LL << graph[v][i].first)) + graph[v][i].second);
    }
  }
  dp_count[v][was] = res;
  return res;
} /* End of 'dfs' function' */
  /* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else
  freopen("salesman.in", "r", stdin);
  freopen("salesman.out", "w", stdout);
#endif
  int n, m;
  scanf("%d%d", &n, &m);
  dp_array_type dp(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    ll w;
    scanf("%d%d%I64d", &a, &b, &w);
    dp[a - 1].push_back(std::pair<int, ll>(b - 1, w));
    dp[b - 1].push_back(std::pair<int, ll>(a - 1, w));
  }

  for (int i = 0; i < MAX_N; i++)
    for (int j = 0; j < (1 << MAX_N); j++)
      dp_count[i][j] = -1;

  ll max_res = INT32_MAX;
  for (int i = 0; i < n; i++)
    max_res = min(max_res, dfs(dp, i, 1, 1LL << i));
  if (max_res == INT32_MAX)
    printf("-1");
  else
    printf("%I64d", max_res);
  return 0;
} /* End of 'main' function */