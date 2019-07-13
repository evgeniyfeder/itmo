#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using Point = std::pair<int32_t, int32_t>;

int64_t sqr(int64_t a) { return a * a; }

double len(Point const & x) {
    return sqrt(static_cast<double>(sqr(x.first) + sqr(x.second)));
}

Point sub(Point const & a, Point const & b) {
    return Point(a.first - b.first,
                 a.second - b.second);
}

static double min_dist = 1E11;
static Point min_a, min_b;

void update_dist(Point const &a, Point const &b) {
    double dist = len(sub(a, b));
    if (dist < min_dist) {
        min_dist = dist;
        min_a = a;
        min_b = b;
    }
}

bool cmp_y(Point const &a, Point const &b) {return a.second < b.second;};

static std::vector<Point> merged;
void rec(std::vector<Point> & vec, size_t l, size_t r) {
    if (r - l <= 3) {
        for (size_t i = l; i <= r; i++) {
            for (size_t j = i + 1; j <= r; j++) {
                update_dist(vec[i], vec[j]);
            }
        }
        std::sort(vec.begin() + l, vec.begin() + r + 1, &cmp_y);
        return;
    }

    size_t m = l + (r - l) / 2;
    int32_t med_x = vec[m].first;

    rec(vec, l, m);
    rec(vec, m + 1, r);


    std::merge(vec.begin() + l, vec.begin() + m + 1,
               vec.begin() + m + 1, vec.begin() + r + 1, merged.begin(), &cmp_y);
    std::copy(merged.begin(), merged.begin() + r - l + 1, vec.begin() + l);

    size_t temp_size = 0;
    for (size_t i = l; i <=r; i++) {
        if (std::abs(vec[i].first - med_x) < min_dist) {
            for (int j = static_cast<int>(temp_size) - 1; j >= 0 && vec[i].second - merged[j].second < min_dist; j--) {
                update_dist(vec[i], merged[j]);
            }
            merged[temp_size++] = vec[i];
        }
    }
}

int main() {
    freopen("rendezvous.in", "r", stdin);
    freopen("rendezvous.out", "w", stdout);

    size_t n;
    std::cin >> n;

    std::vector<Point> pts;
    pts.reserve(n);
    for (size_t i = 0; i < n; i++) {
        int32_t x, y;
        std::cin >> x >> y;
        pts.emplace_back(x, y);
    }

    std::sort(pts.begin(), pts.end());
    merged.resize(n);
    rec(pts, 0, n - 1);
    std::cout << min_a.first << ' ' << min_a.second << std::endl;
    std::cout << min_b.first << ' ' << min_b.second << std::endl;
}
