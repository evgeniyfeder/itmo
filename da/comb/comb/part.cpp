#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

/* Common definitions */
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

#define MAX_N 105
ll num_part[MAX_N][MAX_N];

/* Count minimum of two numbers */
ll min(ll a, ll b) { if (a < b) return a; return b; }

/* Count number of particles function */
void count_part_num(void) {
  num_part[0][0] = 1;

  for (int i = 1; i < MAX_N; i++) {
    for (int j = 1; j <= i; j++) {
      num_part[i][j] = num_part[i - j][0];

      for (int k = j; k + j <= i; k++)
        num_part[i][j] += num_part[i - j][k];
    }
  }
} /* End of 'count_part_num' function */

/* Count k-th partition function */
void partition_by_number(std::string &res_str, ll n, ll k) {
  ll cur_number = 1;
  char number[100];
  while (n > 0) {
    ll left_side = 0LL, num_steps = min(n, cur_number);

    for (ll i = cur_number; i <= n; i++) {
      if (left_side + num_part[n][i] > k) {
        n -= i; k -= left_side; cur_number = i;
        
        /* Add number to string */
        res_str += std::to_string(i) + '+';
        break;
      }
      left_side += num_part[n][i];
    }
  }
  res_str.pop_back();
} /* End of 'partition_by_number' function */

/* Get order number of partition function */
ll get_number_by_partition(std::string in_str) {
  std::vector<ll> in_vec;
  ll n = 0;
  /* Parse exspression */
  for (int i = 0; i < in_str.size(); i++) {
    int cur_num = 0;
    while (i < in_str.size() && in_str[i] != '+') {
      cur_num = cur_num * 10 + (in_str[i] - '0');
      i++;
    }
    n += cur_num;
    in_vec.push_back(cur_num);
  }

  ll res = 0;
  int cur_num = 1;
  for (int i = 0; i < in_vec.size(); i++) {
    for (int skip = cur_num; skip < in_vec[i]; skip++)
      res += num_part[n][skip];
    n -= in_vec[i];
    cur_num = in_vec[i];
  }
  return res;
} /* End of 'get_number_by_partition' function */

/* Print next partition of number function */
void print_next(std::vector<int> part, int n) {
  int num_elem = part.size();

  if (num_elem == 1) {
    printf("No solution\n");
    return;
  }

  part[num_elem - 1]--;
  part[num_elem - 2]++;
  if (part[num_elem - 2] > part[num_elem - 1]) {
    part[num_elem - 2] += part[num_elem - 1];
    part.pop_back();
  }
  else {
    while (part[part.size() - 2] * 2 <= part[part.size() - 1]) {
      part.push_back(part[part.size() - 1] - part[part.size() - 2]);
      part[part.size() - 2] = part[part.size() - 3];
    }
  }
  printf("%d=", n);
  for (int i = 0; i < part.size(); i++)
    printf((i != part.size() - 1 ? "%d+" : "%d\n"), part[i]);
}

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else 
  freopen("nextpartition.in", "r", stdin);
  freopen("nextpartition.out", "w", stdout);
#endif
  /*ll n, k;
  scanf("%I64d%I64d", &n, &k);*/

  /* Fill default dp function */
  //count_part_num();

  /*std::string res;
  partition_by_number(res, n, k);
  printf("%s", res.data()); */
  // printf("%I64d", get_number_by_partition(in));
  std::string in_str;
  std::cin >> in_str;
  std::vector<int> in_vec;
  int n = 0, cur_elem = 0;

  /* Parse sum number */
  while (in_str[cur_elem] != '=') {
    n = n * 10 + (in_str[cur_elem] - '0');
    cur_elem++;
  }


  for (int i = cur_elem + 1; i < in_str.size(); i++) {
    int cur_num = 0;
    while (i < in_str.size() && in_str[i] != '+') {
      cur_num = cur_num * 10 + (in_str[i] - '0');
      i++;
    }
    in_vec.push_back(cur_num);
  }

  print_next(in_vec, n);
  return 0;
} /* End of 'main' function */