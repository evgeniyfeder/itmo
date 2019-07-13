#include <iostream>
#include <cstddef>
#include <vector>
#include <set>
#include <unordered_set>
#include <cmath>
#include <limits>

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

int64_t sqr(int64_t a) { return a * a; }


int64_t len2(Point const & x) {
    return sqr(x.first) + sqr(x.second);
}

Point sub(Point const & a, Point const & b) {
    return Point(a.first - b.first,
                 a.second - b.second);
}

Point add(Point const & a, Point const & b) {
    return Point(a.first + b.first,
                 a.second + b.second);
}

Point neg(Point const & a) {
    return Point(-a.first, -a.second);
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

std::vector<Point> convex_hull(std::vector<Point> const &pts) {
    std::vector<Point> hull;
    quick_hull(pts, pts[0], pts[pts.size() - 1], 1);

    for (auto p = result.begin(); p != result.end(); ++p) {
        hull.push_back(*p);
    }
    result.clear();

    quick_hull(pts, pts[0], pts[pts.size() - 1], -1);
    for (auto p = result.rbegin(); p != result.rend(); ++p) {
        if (*p == pts[0] || *p == pts[pts.size() - 1]) {
            continue;
        }
        hull.push_back(*p);
    }
    return hull;
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

    std::vector<Point> pts_vec(pts.begin(), pts.end());
    std::vector<Point> hull = convex_hull(pts_vec);

    size_t left_ind = 0, right_ind = 0;
    for (size_t i = 0; i < hull.size(); i++) {
        if (hull[i] < hull[left_ind])
            left_ind = i;
        else if (hull[i] > hull[right_ind])
            right_ind = i;
    }

    size_t coliper_1 = left_ind, coliper_2 = right_ind;
    int64_t distance = 0;

    while (coliper_2 != left_ind || coliper_1 != right_ind) {
        distance = std::max(distance, len2(sub(hull[coliper_1], hull[coliper_2])));

        int64_t predicate = rotate_predicate(hull[coliper_1], hull[(coliper_1 + 1) % hull.size()],
                                                add(hull[coliper_1],
                                                    neg(sub(hull[coliper_2], hull[(coliper_2 + 1) % hull.size()]))));
        if (predicate == 0) {
            coliper_1 = (coliper_1 + 1) % hull.size();
            coliper_2 = (coliper_2 + 1) % hull.size();
        } else if (predicate < 0) {
            coliper_2 = (coliper_2 + 1) % hull.size();
        } else {
            coliper_1 = (coliper_1 + 1) % hull.size();
        }
    }
    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << sqrt(static_cast<double>(distance));
    return 0;
}
