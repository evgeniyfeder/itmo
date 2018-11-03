#include <iostream>
#include <cstddef>
#include <vector>
#include <set>

using Point = std::pair<long long, long long>;

int sign(long long sp) {
  if (sp > 0) return 1;
  if (sp < 0) return -1;
  return 0;
}

long long rotate_predicate(Point a, Point b, Point c) {
  return (b.first - a.first) * (c.second - a.second) - (c.first - a.first) * (b.second - a.second);
}

int sign_rotate_predicate(Point a, Point b, Point c) {
  return sign(rotate_predicate(a, b, c));
}

std::set<Point> result;
void quick_hull(const std::vector<Point>& pts, Point L, Point R, int side) {
  int maxInd = -1;
  long long maxDist = 0;

  for (size_t i = 0; i < pts.size(); i++) {
    long long curDist = std::abs(rotate_predicate(L, R, pts[i]));

    if (sign_rotate_predicate(L, R, pts[i]) == side && curDist > maxDist) {
      maxDist = curDist;
      maxInd = (int)i;
    }
  }

  if (maxInd == -1) {
    result.insert(L);
    result.insert(R);
    return;
  }

  const int sign = sign_rotate_predicate(L, R, pts[maxInd]);
  quick_hull(pts, L, pts[maxInd], sign);
  quick_hull(pts, pts[maxInd], R, sign);
}

int main(void) {
  freopen("hull.in", "r", stdin);
  freopen("hull.out", "w", stdout);
  std::ios_base::sync_with_stdio(0);

  std::vector<Point> pts;
  size_t n;
  std::cin >> n;

  size_t leftInd = 0, rightInd = 0;
  for (size_t i = 0; i < n; i++) {
    long long x, y;
    std::cin >> x >> y;
    pts.emplace_back(x, y);

    if (pts[i] < pts[leftInd]) {
      leftInd = i;
    } if (pts[rightInd] < pts[i]) {
      rightInd = i;
    }
  }

  std::vector<Point> hull;
  quick_hull(pts, pts[leftInd], pts[rightInd], 1);

  for (auto p = result.begin(); p != result.end(); ++p) {
    hull.push_back(*p);
  }
  result.clear();

  quick_hull(pts, pts[leftInd], pts[rightInd], -1);
  for (auto p = result.rbegin(); p != result.rend(); ++p) {
    if (*p == pts[leftInd] || *p == pts[rightInd]) {
      continue;
    }
    hull.push_back(*p);
  }

  std::cout << hull.size() << '\n';
  for (auto it = hull.begin(); it != hull.end(); ++it) {
    std::cout << it->first << ' ' << it->second << '\n';
  }

  return 0;
}
