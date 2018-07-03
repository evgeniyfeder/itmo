#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

/* Common definitions */
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

#define MAX_N 21
ll num_brackets[2 * MAX_N][4 * MAX_N];

void get_brackets(std::string &result, int n, ll k) {
  int balance = 0;
  result.clear();

  for (int i = 0; i < 2 * n; i++) {
    if (num_brackets[2 * n - 1 - i][balance + 1] >= k) {
      result.push_back('(');
      balance++;
    }
    else {
      result.push_back(')');
      k -= num_brackets[2 * n - 1 - i][balance + 1];
      balance--;
    }
  }
} /* End of 'get_brackets' function */

ll get_order_number(const std::string &str) {
  int balance = 0;
  ll res = 0;
  int n = str.size() / 2;
  for (int i = 0; i < 2 * n; i++) {
    if (str[i] == '(')
      balance++;
    else {
      res += num_brackets[2 * n - 1 - i][balance + 1];
      balance--;
    }
  }
  return res;
} /* End of 'get_order_number' function */
/* Count number of brackets function */
ll count_num_brackets(int i, int j) {
  if (j < 0)
    return 0;

  if (num_brackets[i][j] != -1)
    return num_brackets[i][j];

  return num_brackets[i][j] =
    count_num_brackets(i - 1, j - 1) + count_num_brackets(i - 1, j + 1);
} /* End of 'count_num_brackets' function */

/* Print next bracket function */
void print_next(std::string bracket) {
  int open = 0, close = 0, n = bracket.size();
  for (int i = n - 1; i >= 0; i--) {
    if (bracket[i] == '(') {
      open++;
      if (close > open)
        break;
    }
    else
      close++;
  }
  if (close + open == n)
    printf("-");
  else {
    for (int i = 0; i < n - open - close; i++)
      printf("%c", bracket[i]);
    printf(")");
    for (int i = 0; i < open; i++)
      printf("(");
    for (int j = 0; j < close - 1; j++)
      printf(")");
    printf("\n");
  }
} /* End of 'print_next' function */

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else 
  freopen("nextbrackets.in", "r", stdin);
  freopen("nextbrackets.out", "w", stdout);
#endif
  /* Count dp */
  /*for (int i = 0; i < 2 * MAX_N; i++)
    for (int j = 0; j <= MAX_N; j++) {
      if (i == 0)
        num_brackets[i][j] = 0;
      else 
        num_brackets[i][j] = -1;
    }
  num_brackets[0][0] = 1;

  for (int i = 0; i < 2 * MAX_N; i++)
    for (int j = 0; j < MAX_N; j++)
      count_num_brackets(i, j);

  /*int n;
  ll k;
  scanf("%d%I64d", &n, &k);

  std::string res;
  get_brackets(res, n, k + 1);
  printf("%s", res.data());*/

  std::string in;
  std::cin >> in;
  print_next(in);
  return 0;
} /* End of 'main' function */