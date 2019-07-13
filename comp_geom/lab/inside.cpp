#include <iostream>
#include <vector>
#include <algorithm>
using Point = std::pair<int32_t, int32_t>;

int64_t rotate_predicate(Point const & a, Point const & b, Point const & c) {
  return static_cast<int64_t>(b.first - a.first) * (c.second - a.second) -
          static_cast<int64_t>(c.first - a.first) * (b.second - a.second);
}

// 0 - left point
int32_t inside(std::vector<Point> const &hull, Point const &Q) {
    if (rotate_predicate(hull[0], hull[1], Q) > 0
            || rotate_predicate(hull[0], hull[hull.size() - 1], Q) < 0) return -1;

    size_t left_index = 1, right_index = hull.size() - 1;
    while (left_index + 1 < right_index) {
        size_t med = left_index + (right_index - left_index) / 2;
        if (rotate_predicate(hull[0], hull[med], Q) < 0) {
            left_index = med;
        } else {
            right_index = med;
        }
    }

    Point A = hull[left_index];
    Point B = hull[left_index + 1];
    int64_t predicate = rotate_predicate(A, B, Q);
    if (predicate < 0) {
        if (left_index == 1 && rotate_predicate(hull[0], hull[1], Q) == 0)
            return 0;
        else if (left_index == hull.size() - 2
                 && rotate_predicate(hull[hull.size() - 1], hull[0], Q) == 0)
            return 0;
        return 1;
    } else if (predicate == 0) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    size_t n;
    std::cin >> n;

    std::vector<Point> hull;
    hull.reserve(n);

    size_t left_index = 0;
    for (size_t i = 0; i < n; i++) {
        int32_t x, y;
        std::cin >> x >> y;
        hull.emplace_back(x, y);

        if (hull[i] < hull[left_index])
            left_index = i;
    }

    std::vector<Point> correct_hull; // 0 - left
    correct_hull.reserve(n);

    for (size_t i = left_index; i < n; i++) {
        correct_hull.emplace_back(hull[i]);
    }

    for (size_t i = 0; i < left_index; i++) {
        correct_hull.emplace_back(hull[i]);
    }
    if (rotate_predicate(hull[0], hull[1], hull[2]) > 0)
        std::reverse(correct_hull.begin() + 1, correct_hull.end());

    size_t k;
    std::cin >> k;
    for (size_t i = 0; i < k; i++) {
        int32_t x, y;
        std::cin >> x >> y;
        Point p(x, y);

        int32_t is_inside = inside(correct_hull, p);
        if (is_inside == 1) {
            std::cout << "INSIDE";
        } else if (is_inside == 0) {
            std::cout << "BORDER";
        } else {
            std::cout << "OUTSIDE";
        }
        std::cout << std::endl;
    }
}
