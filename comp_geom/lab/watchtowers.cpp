#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <time.h>
#include <chrono>

double sqr(double a) { return a * a; }

struct Point {
   using point_type = double;

   point_type x, y;

   Point(point_type new_x = 0, point_type new_y = 0) : x(new_x), y(new_y) {}

   double len() const {
       return sqrt(sqr(x) + sqr(y));
   }

   double len2() const {
      return sqr(x) + sqr(y);
   }

   Point operator*(point_type a) const {
      return Point(a * x, a * y);
   }

   Point operator/(point_type a) const{
      return Point(x / a, y / a);
   }

   Point operator+(Point const & p) const {
      return Point(x + p.x, y + p.y);
   }

   Point operator-(Point const & p) const {
      return Point(x - p.x, y - p.y);
   }
};

struct Circle {
   Point center;
   double r2;

   Circle(std::vector<Point> && pts) {
      if (pts.size() == 2) {
         center = (pts[0] + pts[1]) / 2;
         r2 = ((pts[0] - pts[1]) / 2).len2();
      } else if (pts.size() == 3) {
         Point a = pts[0], b = pts[1], c = pts[2];

         double d = 0.5 / (a.x * (b.y - c.y) +
                           b.x * (c.y - a.y) +
                           c.x * (a.y - b.y));
         double xx = b.len2() - c.len2();
         double yy = c.len2() - a.len2();
         double zz = a.len2() - b.len2();

         center.x = -(a.y * xx + b.y * yy + c.y * zz) * d;
         center.y = (a.x * xx + b.x * yy + c.x * zz) * d;
         r2 = (center - a).len2();
      }
   }

   bool is_inside(Point const & p) {
      return (p - center).len2() <= r2;
   }
};

Circle stage2(std::vector<Point> const & pts, size_t n, size_t p0, size_t p1) {
   Circle c({pts[p0], pts[p1]});
   for (size_t i = 0; i < n; i++) {
      if (!c.is_inside(pts[i])) {
         c = Circle({pts[p0], pts[p1], pts[i]});
      }
   }
   return c;
}

Circle stage1(std::vector<Point> const & pts, size_t n, size_t p) {
   Circle c({pts[0], pts[p]});
   for (size_t i = 1; i < n; i++) {
      if (!c.is_inside(pts[i])) {
         c = stage2(pts, i, i, p);
      }
   }
   return c;
}

Circle stage0(std::vector<Point> const &pts) {
   Circle c({pts[0], pts[1]});
   for (size_t i = 2; i < pts.size(); i++) {
      if (!c.is_inside(pts[i])) {
         c = stage1(pts, i, i);
      }
   }
   return c;
}

/*bool check_circle(Point const & a, Point const & b, Point const & c, Point const & q) {
    static const size_t size = 4;

    std::vector<std::vector<double>> matr = {
            {static_cast<double>(a.x), static_cast<double>(a.y), static_cast<double>(a.len2()), 1},
            {static_cast<double>(b.x), static_cast<double>(b.y), static_cast<double>(b.len2()), 1},
            {static_cast<double>(c.x), static_cast<double>(c.y), static_cast<double>(c.len2()), 1},
            {static_cast<double>(q.x), static_cast<double>(q.y), static_cast<double>(q.len2()), 1}
    };

    double res = 0;
    for (size_t i = 0; i < size; i++) {
        size_t k = i;

        for (size_t j = i + 1; j < size; j++) {
            if (std::abs(matr[j][i]) > std::abs(matr[k][i])) {
                k = j;
            }
        }
        if (std::abs(matr[k][i]) < EPS) {
            res = 0;
            break;
        }
        if (k != i) {
            std::swap(matr[k], matr[i]);
            res = -res;
        }
        res *= matr[i][i];
        for (size_t j = i + 1; j < size; j++) {
            matr[i][j] /= matr[i][i];
        }
        for (size_t j = 0; j < size; ++j)
                if (j != i && std::abs(matr[j][i]) > EPS)
                    for (size_t k = i + 1; k < size; ++k)
                        matr[j][k] -= matr[i][k] * matr[j][i];
    }
    return res <= EPS;
} */


int main() {
   size_t n = 0;
   std::cin >> n;
   srand(unsigned(time(nullptr)));
   std::vector<Point> points;
   points.reserve(n);
   std::ios_base::sync_with_stdio(false);
   for (size_t i = 0; i < n; i++) {
     double x, y;
     std::cin >> x >> y;
     points.emplace_back(x, y);
   }

   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine e(seed);
   std::shuffle(std::begin(points), std::end(points), e);

   std::cout.precision(std::numeric_limits<double>::max_digits10);

   if (n == 1) {
    std::cout << "0\n" << points[0].x << ' ' << points[0].y;
   } else if (n == 2) {
    Circle c({points[0], points[1]});
    std::cout << sqrt(c.r2) << '\n' << c.center.x << ' ' << c.center.y;
   } else {
      Circle c = stage0(points);
      std::cout << sqrt(c.r2) << '\n' << c.center.x << ' ' << c.center.y;
   }
   return 0;
}
