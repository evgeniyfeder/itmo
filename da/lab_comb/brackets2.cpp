#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <stack>

/* Common definitions */
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

#define MAX_N 21
ll num_brackets[2 * MAX_N][4 * MAX_N];
std::stack<char> brak_stack;

void get_brackets(std::string &result, int n, ll k) {
  int balance = 0;
  result.clear();

  for (int i = 0; i < 2 * n; i++) {
    /* Check for '(' */
    ll cur_num = num_brackets[2 * n - 1 - i][balance + 1] << ((2 * n - 1 - i - (balance + 1)) / 2);
    if (cur_num >= k) {
      result.push_back('(');
      balance++;
      brak_stack.push('(');
      continue;
    }
    k -= cur_num;

    /* Check for ')' */
    if (brak_stack.size() > 0 && brak_stack.top() == '(')
      cur_num = num_brackets[2 * n - 1 - i][balance - 1] << ((2 * n - 1 - i - (balance - 1)) / 2);
    else
      cur_num = 0;
    if (cur_num >= k) {
      result.push_back(')');
      balance--;
      brak_stack.pop();
      continue;
    }
    k -= cur_num;

    /* Check for '[' */
    cur_num = num_brackets[2 * n - 1 - i][balance + 1] << ((2 * n - 1 - i - (balance + 1)) / 2);
    if (cur_num >= k) {
      result.push_back('[');
      balance++;
      brak_stack.push('[');
      continue;
    }
    k -= cur_num;

    /* Check for ']' */
    result.push_back(']');
    brak_stack.pop();
    balance--;
  }
} /* End of 'get_brackets' function */

/* Get order number of sequence */
ll get_order_number(const std::string &str) {
  int balance = 0;
  ll res = 0;
  int n = str.size() / 2;
  for (int i = 0; i < 2 * n; i++) {
    ll cur_sum = 0, cur_num = 0;
    if (str[i] == '(') {
      balance++;
      brak_stack.push('(');
      continue;
    }
    cur_sum += num_brackets[2 * n - 1 - i][balance + 1] << ((2 * n - 1 - i - (balance + 1)) / 2);

    if (brak_stack.size() > 0 && brak_stack.top() == '(')
      cur_num = num_brackets[2 * n - 1 - i][balance - 1] << ((2 * n - 1 - i - (balance - 1)) / 2);
    else
      cur_num = 0;

    if (str[i] == ')') {
      balance--;
      res += cur_sum;
      brak_stack.pop();
      continue;
    }
    cur_sum += cur_num;

    if (str[i] == '[') {
      balance++;
      res += cur_sum;
      brak_stack.push('[');
      continue;
    }
    cur_sum += num_brackets[2 * n - 1 - i][balance + 1] << ((2 * n - 1 - i - (balance + 1)) / 2);
    balance--;
    res += cur_sum;
    brak_stack.pop();
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

  /* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else 
  freopen("brackets2num2.in", "r", stdin);
  freopen("brackets2num2.out", "w", stdout);
#endif
  /* Count dp */
  for (int i = 0; i < 2 * MAX_N; i++)
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
  /*int a;
  for (int i = 1; i < 10; i++)
    for (int j = 0; j < num_brackets[2 * i][0] << i; j++) {
      std::string str;
      get_brackets(str, i, j + 1);
      if (j != (a = get_order_number(str)))
        break;
    }*/
  std::string in;
  std::cin >> in;
  printf("%I64d", get_order_number(in));
  return 0;
} /* End of 'main' function */