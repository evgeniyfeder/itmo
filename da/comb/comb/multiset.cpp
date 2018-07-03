#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <string>

/* Common definitions */
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

/* Print next multiset function */
void next_multiset(std::vector<int> set) {
  int n = set.size(), i = set.size() - 2;
  while (i >= 0 && set[i] >= set[i + 1])
    i--;

  if (i >= 0) {
    /* Search max */
    int j = i + 1;
    while (j < n - 1 && set[j + 1] > set[i])
      j++;
    int cmp = set[i]; set[i] = set[j]; set[j] = cmp;

    /* Reverse */
    int num_steps = (n - 1 - (i + 1)) / 2 + 1;
    for (int j = 0; j < num_steps; j++) {
      cmp = set[i + 1 + j];
      set[i + 1 + j] = set[n - 1 - j];
      set[n - 1 - j] = cmp;
    }

    /* Out */
    for (int j = 0; j < n; j++)
      printf("%d ", set[j]);
    printf("\n");
    return;
  }
  for (int i = 0; i < n; i++)
    printf("0 ");
  printf("\n");

} /* End of 'next_multiset' function */
/* The main function of programme */
int main(void) {
#ifdef _DEBUG
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#else 
  freopen("nextmultiperm.in", "r", stdin);
  freopen("nextmultiperm.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);

  std::vector<int> in(n);
  for (int i = 0; i < n; i++)
    scanf("%d", &in[i]);

  next_multiset(in);
  return 0;
} /* End of 'main' function */