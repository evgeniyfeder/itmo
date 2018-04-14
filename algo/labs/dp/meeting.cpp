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

ll min(ll a, ll b) { if (a < b) return a; return b; }

std::vector<int> was;
/* Depth search function */
ll dfs(const dp_array_type &graph, int v, int n) {
  ll res = INT32_MAX;
  if (n == (int)graph.size())
    return 0;
  was[v] = 1;
  for (int i = 0; i < (int)graph[v].size(); i++) {
    if (was[graph[v][i].first] == 0) {
      res = min(res, dfs(graph, graph[v][i].first, n + 1) + graph[v][i].second);
    }
  }
  was[v] = 0;
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
  was.resize(n);
  dp_array_type dp(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    ll w;
    scanf("%d%d%I64d", &a, &b, &w);
    dp[a - 1].push_back(std::pair<int, ll>(b - 1, w));
    dp[b - 1].push_back(std::pair<int, ll>(a - 1, w));
  }

  ll max_res = INT32_MAX;
  for (int i = 0; i < n; i++)
    max_res = min(max_res, dfs(dp, i, 1));
  if (max_res == INT32_MAX)
    printf("-1");
  else
    printf("%I64d", max_res);
  return 0;
} /* End of 'main' function */