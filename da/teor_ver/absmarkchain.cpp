#include <fstream>
#include <iostream>
#include <iomanip>

#define MAX_N 400
#define MAX_M 160000

static std::string file_name;

double input[MAX_M][3];
bool absorbing[MAX_N];

double Q[MAX_N][MAX_N], R[MAX_N][MAX_N], N[MAX_N][MAX_N], E[MAX_N][MAX_N], G[MAX_N][MAX_N];
int position[MAX_N];

/* The main function of program */
int main(void) {
#ifdef _DEBUG
	file_name = std::string("test");
#else
	file_name = std::string("absmarkchain");
#endif
	freopen((file_name + ".in").data(), "r", stdin);
	freopen((file_name + ".out").data(), "w", stdout);

	int n, m;
	scanf("%d%d", &n, &m);
	int abs_count = 0;

	/* Read input and count absorbing points */
	for (int i = 0; i < m; i++) {
		scanf("%lf%lf%lf", &input[i][0], &input[i][1], &input[i][2]);
		input[i][0]--;
		input[i][1]--;

		if (input[i][0] == input[i][1] && input[i][2] == 1) {
			absorbing[(int)input[i][0]] = true;
			abs_count++;
		}
	}

	/* Count Q and R matrix */
	int not_abs = n - abs_count, num_q = 0, num_r = 0;
	for (int i = 0; i < n; i++) {
		if (absorbing[i])
			position[i] = num_r++;
		else
			position[i] = num_q++;
	}
	
	for (int i = 0; i < m; i++) {
		if (absorbing[(int)input[i][1]]) {
			if (!absorbing[(int)input[i][0]])
				R[position[(int)input[i][0]]][position[(int)input[i][1]]] = input[i][2];
		}
		else
			Q[position[(int)input[i][0]]][position[(int)input[i][1]]] = input[i][2];
	}

	/* Count E = I - Q and reate N */
	for (int i = 0; i < not_abs; i++) {
		N[i][i] = 1;
		E[i][i] = 1;
		for (int j = 0; j < not_abs; j++)
			E[i][j] -= Q[i][j];
	}

	/* Count N^(-1) */
	for (int i = 0; i < not_abs; i++) {
		double mul = 0;
		if (E[i][i] != 1) {
			mul = E[i][i];
			for (int j = 0; j < not_abs; j++) {
				E[i][j] /= mul;
				N[i][j] /= mul;
			}
		}
		for (int j = 0; j < not_abs; j++) {
			if (i != j) {
				mul = E[j][i];
				for (int k = 0; k < not_abs; k++) {
					E[j][k] -= mul * E[i][k];
					N[j][k] -= mul * N[i][k];
				}
			}
		}
	}

	/* G = N * R */
	for (int i = 0; i < not_abs; i++) {
		for (int j = 0; j < abs_count; j++) {
			G[i][j] = 0;
			for (int k = 0; k < not_abs; k++) {
				G[i][j] += N[i][k] * R[k][j];
			}
		}
	}

	/* Print result */
	for (int i = 0; i < n; i++) {
		double p = 0;
		if (absorbing[i]) {
			for (int j = 0; j < not_abs; j++) {
				p += G[j][position[i]];
			}
			p++;
			p /= n;
		}
		printf("%.5lf\n", p);
	}
	return 0;
} /* End of 'main' function */