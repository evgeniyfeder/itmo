#include <iostream>
#include <cstddef>
#include <vector>
#include <set>
#include <unordered_set>

using Point = std::pair<int64_t, int64_t>;

int sign(int64_t sp) {
  if (sp > 0) return 1;
  if (sp < 0) return -1;
  return 0;
}

long long rotate_predicate(Point const & a, Point const & b, Point const & c) {
  return (b.first - a.first) * (c.second - a.second) - (c.first - a.first) * (b.second - a.second);
}

int sign_rotate_predicate(Point const & a, Point const & b, Point const & c) {
  return sign(rotate_predicate(a, b, c));
}

static std::set<Point> result;
void quick_hull(std::vector<Point> const & pts, Point const & L, Point const & R, int side) {
  int32_t maxInd = -1;
  int64_t maxDist = 0;

  std::vector<Point> next_pts;
  for (size_t i = 0; i < pts.size(); i++) {
    int64_t predicate = rotate_predicate(L, R, pts[i]);
    int64_t curDist = std::abs(predicate);
    int32_t sign_pr = sign(predicate);

    if (sign_pr == side)
        next_pts.emplace_back(pts[i]);
    if (sign(predicate) == side && curDist > maxDist) {
      maxDist = curDist;
      maxInd = static_cast<int32_t>(i);
    }
  }

  if (maxInd == -1) {
    result.insert(L);
    result.insert(R);
    return;
  }

  size_t index = static_cast<size_t>(maxInd);
  const int sign = sign_rotate_predicate(L, R, pts[index]);
  quick_hull(next_pts, L, pts[index], sign);
  quick_hull(next_pts, pts[index], R, sign);
}

int main(void) {
  //freopen("hull.in", "r", stdin);
  //freopen("hull.out", "w", stdout);
  std::ios_base::sync_with_stdio(0);

  std::set<Point> pts;
  size_t n;
  std::cin >> n;

  for (size_t i = 0; i < n; i++) {
    int64_t x, y;
    std::cin >> x >> y;
    pts.insert(Point(x, y));
  }

  std::vector<Point> hull;
  std::vector<Point> pts_vec(pts.begin(), pts.end());
  quick_hull(pts_vec, pts_vec[0], pts_vec[pts.size() - 1], 1);

  for (auto p = result.begin(); p != result.end(); ++p) {
    hull.push_back(*p);
  }
  result.clear();

  quick_hull(pts_vec, pts_vec[0], pts_vec[pts.size() - 1], -1);
  for (auto p = result.rbegin(); p != result.rend(); ++p) {
    if (*p == pts_vec[0] || *p == pts_vec[pts.size() - 1]) {
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
