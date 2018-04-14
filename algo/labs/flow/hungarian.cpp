#include <iostream>
#include <string.h>
static const int max_n = 350, inf = 1000000000;

int A[max_n][max_n];
int size;

int pcol[max_n], prow[max_n]; // potential
int match[max_n];			  // matching
int minv[max_n], way[max_n];  // helpful

char used[max_n];

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	std::cin >> size;
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
			std::cin >> A[i][j];

	for (int i = 1; i <= size; i++) {
		match[0] = i;

		//memset(minv, inf, sizeof(minv[0]) * (size + 1));
		for (int j = 0; j <= size; j++)
			minv[j] = inf;
		memset(used, 0, sizeof(used[0]) * (size + 1));
		int end = 0;

		/* Find upper path */
		do {
			used[end] = 1;
			int new_min = inf, new_min_j = 0, next_v = match[end];

			for (int to = 1; to <= size; to++) {
				if (used[to] == 0) {
					int cur_m = A[next_v][to] - pcol[next_v] - prow[to];

					if (cur_m < minv[to]) {
						minv[to] = cur_m;
						way[to] = end;
					}
					if (minv[to] < new_min) {
						new_min = minv[to];
						new_min_j = to;
					}
				}
			}

			for (int to = 0; to <= size; to++) {
				if (used[to] == 1)
					pcol[match[to]] += new_min, prow[to] -= new_min;
				else
					minv[to] -= new_min;
			}
			end = new_min_j;
		} while (match[end] != 0);
		do {
			int next = way[end];
			match[end] = match[next];
			end = next;
		} while (end != 0);
	}

	std::cout << -prow[0] << std::endl;
	for (int i = 1; i <= size; i++) {
		std::cout << match[i] << " " << i << std::endl;
	}

	return 0;
}