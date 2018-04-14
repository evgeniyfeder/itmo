#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common definitions */
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

std::vector<ll> factorials;
/* Get factorial function */
ll get_fact(int x) {
  ll res = 1;

  for (int i = 1; i <= x; i++)
    res *= i;
  return res;
} /* End of 'get_fact' function */

/* Get choose function */
ll get_c(int n, int k) {
  return get_fact(n) / (get_fact(k) * get_fact(n - k));
} /* End of 'get_c' function */

/* Get m choose(n,k) */
std::vector<ll> get_choose(int n, int k, ll m) {
  std::vector<ll> res;
  int begin_num = 1;
  while (k > 0) {
    ll cur_c = get_c(n - 1, k - 1);
    if (m < cur_c) {
      res.push_back(begin_num);
      k--;
    }
    else
      m -= cur_c;
    n--;
    begin_num++;
  }
  return res;
} /* End of 'get_choose' function */

/* Print next choose function */
void print_next(std::vector<int> choose, int n, int k) {
  choose.push_back(n + 1);
  int i = k - 1;
  while (i >= 0 && choose[i + 1] - choose[i] < 2)
    i--;

  if (i < 0)
    printf("-1");
  else {
    choose[i]++;
    for (int next = i + 1; next < k; next++)
      choose[next] = choose[next - 1] + 1;
    choose.pop_back();
    for (int i = 0; i < choose.size(); i++)
      printf("%d ", choose[i]);
    printf("\n");
  }
} /* End of 'print_next' function */

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else 
  freopen("nextchoose.in", "r", stdin);
  freopen("nextchoose.out", "w", stdout);
#endif
  int n, k;
  /*ll m;
  scanf("%d%d%I64d", &n, &k, &m);
  get_fact(n);
  std::vector<ll> res;
  res = get_choose(n, k, m);
  for (int i = 0; i < (int)res.size(); i++)
    printf("%I64d ", res[i]); */
  scanf("%d%d", &n, &k);
  std::vector<int> in(k);
  for (int i = 0; i < k; i++)
    scanf("%d", &in[i]);
  print_next(in, n, k);

  return 0;
} /* End of 'main' function */