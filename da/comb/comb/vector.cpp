#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

/* Common definitions */
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

/* print next vector */
void print_next(std::vector<int> vec) {
  int i = vec.size() - 1;
  for (; i >= 0 && vec[i] != 0; i--)
    vec[i] = 0;

  if (i == -1)
    printf("-\n");
  else {
    vec[i] = 1;
    for (int i = 0; i < vec.size(); i++)
      printf("%d", vec[i]);
    printf("\n");
  }
} /* End of 'printf_next' function */

  /* print next vector */
void print_prev(std::vector<int> vec) {
  int i = vec.size() - 1;
  for (; i >= 0 && vec[i] != 1; i--)
    vec[i] = 1;

  if (i == -1)
    printf("-\n");
  else {
    vec[i] = 0;
    for (int i = 0; i < vec.size(); i++)
      printf("%d", vec[i]);
    printf("\n");
  }
} /* End of 'print_prev' function */

/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else 
  freopen("nextvector.in", "r", stdin);
  freopen("nextvector.out", "w", stdout);
#endif
  std::vector<int> in;
  std::string in_str;
  std::cin >> in_str;
  /* Read vector */
  for (int i = 0; i < in_str.size(); i++) {
    in.push_back(in_str[i] - '0');
  }
  print_prev(in);
  print_next(in);
  return 0;
} /* End of 'main' function */