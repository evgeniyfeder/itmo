#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common definitions */
typedef long long ll;
typedef unsigned long long ull;
typedef long long ll;

/* Get number by permutation */
ll get_number(const std::vector<int> &perm) {
  ll res = 0;
  std::vector<bool> mult(perm.size());
  for (int i = 0; i < mult.size(); i++)
    mult[i] = true;

  /* Get (n - 1) factorial */
  ll cur_fact = 1;
  for (ll i = 1; i <= mult.size() - 1; i++)
    cur_fact *= i;

  /* Get number of permutation */
  for (int i = 0; i < perm.size(); i++) {
    int cur_num_pos = 0;
    for (int j = 0; j < perm[i]; j++)
      if (mult[j])
        cur_num_pos++;
    mult[perm[i] - 1] = false;

    res += (cur_num_pos - 1) * cur_fact;
    if (perm.size() - i - 1 != 0)
      cur_fact /= (perm.size() - i - 1);
  }
  return res;
} /* End of 'get_number' function */

/* Get permutation by number k(0...n! - 1) */
std::vector<ll> get_perm(ll n, ll k) {
  std::vector<ll> result;
  std::vector<ll> mult(n);

  for (ll i = 0; i < mult.size(); i++)
    mult[i] = 1;

  /* Get (n-1)! */
  ll fact = 1;
  for (ll i = 1; i < n; i++)
    fact *= i;

  while (n > 0) {
    ll cur_fact = fact, cur_iter = 1;

    while (cur_fact <= k) {
      cur_fact += fact;
      cur_iter++;
    }

    ll cur_num = 0, i = 0;
    while (cur_num < cur_iter) {
      if (mult[i++] == 1)
        cur_num++;
    }

    result.push_back(i);
    mult[i - 1] = -1;

    if (k != 0)
      k -= (cur_iter - 1) * fact;

    n--;
    if (n != 0)
      fact /= n;
  }
  return result;
} /* End of 'get_perm' function */

/* Print next permutation function */
void print_next(std::vector<int> perm) {
  int n = perm.size();
  for (int i = n - 2; i >= 0; i--) {
    if (perm[i] < perm[i + 1]) {
      int min = i + 1;

      /* Search minimum */
      for (int j = i + 1; j < n; j++)
        if (perm[j] < perm[min] && perm[j] > perm[i])
          min = j;
      /* Swap */
      int cmp = perm[i]; perm[i] = perm[min]; perm[min] = cmp;

      /* Reverse */
      int num_steps = (n - 1 - (i + 1)) / 2 + 1;
      for (int j = 0; j < num_steps; j++) {
        cmp = perm[i + 1 + j];
        perm[i + 1 + j] = perm[n - 1 - j];
        perm[n - 1 - j] = cmp;
      }

      /* Out */
      for (int j = 0; j < n; j++)
        printf("%d ", perm[j]);
      printf("\n");
      return;
    }
  }
  for (int j = 0; j < n; j++)
    printf("0 ");
  printf("\n");
} /* End of 'print_next' function */

  /* Print next permutation function */
void print_prev(std::vector<int> perm) {
  int n = perm.size();
  for (int i = n - 2; i >= 0; i--) {
    if (perm[i] > perm[i + 1]) {
      int max = i + 1;

      /* Search maximum */
      for (int j = i + 1; j < n; j++)
        if (perm[j] > perm[max] && perm[j] < perm[i])
          max = j;
      /* Swap */
      int cmp = perm[i]; perm[i] = perm[max]; perm[max] = cmp;

      /* Reverse */
      int num_steps = (n - 1 - (i + 1)) / 2 + 1;
      for (int j = 0; j < num_steps; j++) {
        cmp = perm[i + 1 + j];
        perm[i + 1 + j] = perm[n - 1 - j];
        perm[n - 1 - j] = cmp;
      }

      /* Out */
      for (int j = 0; j < n; j++)
        printf("%d ", perm[j]);
      printf("\n");
      return;
    }
  }
  for (int j = 0; j < n; j++)
    printf("0 ");
  printf("\n");
} /* End of 'print_prev' function */


/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else 
  freopen("nextperm.in", "r", stdin);
  freopen("nextperm.out", "w", stdout);
#endif
  ll n, k;

  /// get perm by number
  /*scanf("%I64d%I64d", &n, &k);
  std::vector<ll> res;
  res = get_perm(n, k);
  for (ll i = 0; i < res.size(); i++) {
    printf("%I64d ", res[i]);
  }*/

  /// get number by perm
  scanf("%I64d", &n);
  std::vector<int> in(n);
  for (int i = 0; i < in.size(); i++)
    scanf("%d", &in[i]);
  print_prev(in);
  print_next(in);
  //printf("%I64d", get_number(in));
  return 0;
} /* End of 'main' function */