#include "tests.h"
#include <iostream>
#include <cstddef>
#include <gmpxx.h>

int sign_rotate_predicate(double a_xd, double a_yd, double b_xd, double b_yd, double c_xd, double c_yd) {
  int sign_abc = 0;
  double
    E = abs(8 * std::numeric_limits<double>::epsilon() * ((b_xd - a_xd) * (c_yd - a_yd) + (c_xd - a_xd) * (b_yd - a_yd))),
    V = (b_xd - a_xd) * (c_yd - a_yd) - (c_xd - a_xd) * (b_yd - a_yd);

  if (V > E) {
    sign_abc = 1;
  } else if (V < -E) {
    sign_abc = -1;
  } else {
    mpq_class a_x(a_xd);
    mpq_class a_y(a_yd);

    mpq_class b_x(b_xd);
    mpq_class b_y(b_yd);

    mpq_class c_x(c_xd);
    mpq_class c_y(c_yd);

    sign_abc = sgn((b_x - a_x) * (c_y - a_y) - (c_x - a_x) * (b_y - a_y));
  }
  return sign_abc;
}

bool check_bbox(double a, double b, double c, double d) {
  if (a > b) swap(a, b);
	if (c > d) swap(c, d);

	return max(a,c) <= min(b,d);
}

int main() {
    int test_id;
    std::cin >> test_id;

    std::vector<double> v = genTest(test_id);
    for (size_t i = 0; i < v.size();) {
      double a_xd = v[i++], a_yd = v[i++];
      double b_xd = v[i++], b_yd = v[i++];
      double c_xd = v[i++], c_yd = v[i++];
      double d_xd = v[i++], d_yd = v[i++];

      int
        sign_abc = sign_rotate_predicate(a_xd, a_yd, b_xd, b_yd, c_xd, c_yd),
        sign_abd = sign_rotate_predicate(a_xd, a_yd, b_xd, b_yd, d_xd, d_yd),
        sign_cda = sign_rotate_predicate(c_xd, c_yd, d_xd, d_yd, a_xd, a_yd),
        sign_cdb = sign_rotate_predicate(c_xd, c_yd, d_xd, d_yd, b_xd, b_yd);

      int
        sign_ab = sign_abc * sign_abd,
        sign_cd = sign_cda * sign_cdb;
      if (check_bbox(a_xd, b_xd, c_xd, d_xd) && check_bbox(a_yd, b_yd, c_yd, d_yd)
          && (sign_ab <= 0 && sign_cd <= 0)) {
          std::cout << "Y";
      } else {
          std::cout << "N";
      }
    }
}
