#include <vector>
#include <string>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
/* Matrix type function */
struct matrix {
private:
	double **matr;
	int size;

public:
	/* Class consttructor */
	matrix(int size) : size(size) {
		matr = (double **)malloc(sizeof(double *) * size);

		for (int i = 0; i < size; i++)
			matr[i] = (double *)malloc(sizeof(double) * size);
	} /* End of 'matrix' constructor */

	  /* Class destructor */
	~matrix() {
		for (int i = 0; i < size; i++)
			free(matr[i]);
		free(matr);
	} /* End of 'matrix' destructor */

	  /* Set matrix to identity form */
	matrix &identity() {
		for (int y = 0; y < size; y++) {
			memset(matr[y], 0, sizeof(double) * y);
			matr[y][y] = 1;
			memset(matr[y] + y + 1, 0, sizeof(double) * (size - y - 1));
		}

		return *this;
	}
	/* Set number to matrix */
	matrix &set(int x, int y, double data) {
		matr[y][x] = data;
		return *this;
	} /* End of 'set' function */

	  /* Get number from matrix */
	double get(int x, int y) const {
		return matr[y][x];
	} /* End of 'get' function */

	  /* Define operator * for matrix */
	matrix operator*(matrix const &matr) {
		matrix res(size);

		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				double sum = 0;
				for (int k = 0; k < size; k++)
					sum += matr.get(x, k) * get(k, y);
				res.set(x, y, sum);
			}
		}
		return res;
	} /* End of 'operator*' function */

	  /* Define operator = for matrix */
	matrix &operator=(matrix const &matrix) {
		for (int y = 0; y < size; y++)
			memcpy(matr[y], matrix.matr[y], sizeof(double) * size);
		return *this;
	} /* End of 'operator=' function */

	  /* Copyng constructor */
	matrix(matrix const &matrix) {
		size = matrix.get_size();
		matr = (double **)malloc(sizeof(double *) * size);

		for (int i = 0; i < size; i++)
			matr[i] = (double *)malloc(sizeof(double) * size);

		for (int y = 0; y < size; y++)
			memcpy(matr[y], matrix.matr[y], sizeof(double) * size);
	} /* End of 'matrix' constructor */

	  /* Set matrix to n stepen */
	matrix pow(int n) {
		matrix res(size), deg(size);
		res.identity();
		deg = *this;

		for (int i = 0; n > 0; i++) {
			if (n & 1)
				res = res * deg;
			deg = deg * deg;
			n >>= 1;
		}
		return res;
	} /* End of 'pow' function */

	  /* Check for equils function */
	bool operator==(matrix const &matr) {
		for (int y = 0; y < size; y++)
			for (int x = 0; x < size; x++)
				if (abs(get(x, y) - matr.get(x, y)) > 0.00001)
					return false;
		return true;
	}

	/* Get size function */
	int get_size() const { return size; }
}; /* End of 'matrix' function */

   /* My pow function */
static std::string file_name;

#define N 100
long double a[N][N], b[N][N];
int size;
const double eps = 1e-5;

void sqr() {
	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++) {
			b[y][x] = 0;
			for (int k = 0; k < size; k++)
				b[y][x] += a[y][k] * a[k][x];
		}
}

bool is_equil() {
	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			if (abs(a[y][x] - b[y][x]) > eps)
				return false;
	return true;
}

void copy() {
	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			a[y][x] = b[y][x];
}
/* The main function of program */
int main(void) {
#ifdef _DEBUG
	file_name = std::string("test");
#else
	file_name = std::string("markchain");
#endif
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);

	std::cin >> size;

	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++) {
			std::cin >> a[y][x];
		}

	while (true) {
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				b[y][x] = 0;
				for (int z = 0; z < size; z++) {
					b[y][x] += a[y][z] * a[z][x];
				}
			}
		}

		int equils_count = 0;

		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				if (abs(a[y][x] - b[y][x]) < eps) {
					equils_count++;
				}
				a[y][x] = b[y][x];
			}
		}
		if (equils_count == size * size)
			break;
	}
	
	for (int x = 0; x < size; x++) {
		std::cout << std::setprecision(10) << std::fixed  << (double)b[0][x] << std::endl;
	}

	return 0;
} /* End of 'main' function */