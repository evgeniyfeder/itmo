#include <bits/stdc++.h>

using namespace std;

const int N = 111;

long double a[N][N], b[N][N], spec[N][N];

int main()
{
	freopen("markchain.in", "r", stdin);
	freopen("markchain.out", "w", stdout);
	int n;
	scanf("%d", &n);
	double c;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%lf", &c);
			a[i][j] = c;
			spec[i][j] = c;
		}
	}
	double eps = 1e-5;
	while (true) {
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				b[i][j] = 0;
			}
		}
		for (int x = 0; x < n; ++x) {
			for (int y = 0; y < n; ++y) {
				for (int z = 0; z < n; ++z) {
					b[x][y] += a[x][z] * a[z][y];
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (abs(a[i][j] - b[i][j]) < eps) {
					cnt++;
				}
				a[i][j] = b[i][j];
			}
		}
		if (cnt == n * n) {
			break;
		}
	}
	
	for (int i = 0; i < n; ++i) {
		cout << setprecision(15) << fixed << (double)a[0][i] << '\n';
	}
}