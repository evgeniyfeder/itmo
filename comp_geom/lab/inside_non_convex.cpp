#include <iostream>
#include <vector>
using point = std::pair<int64_t, int64_t>;

int32_t sign(int64_t x) {
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    return 0;
}

int32_t sign_rotate_predicate(point const & a, point const & b, point const & c) {
    return sign((b.first - a.first) * (c.second - a.second)
            - (c.first - a.first) * (b.second - a.second));
}

bool is_inner(point const & p0, std::vector<point> const & polyg) {
    size_t num_inter = 0;
    for (size_t i = 0; i < polyg.size(); i++) {
        point max_y = polyg[i];
        point min_y = polyg[(i + 1) % polyg.size()];

        if (sign_rotate_predicate(min_y,max_y,p0) == 0
                && std::min(min_y.first, max_y.first) <= p0.first
                && p0.first <= std::max(min_y.first, max_y.first) &&
                min_y.second <= p0.second && p0.second <= max_y.second)
            return true;

        if (min_y.second > max_y.second)
            std::swap(min_y, max_y);
        if (max_y.second <= p0.second || min_y.second > p0.second)
            continue;
        int orientation = sign_rotate_predicate(min_y, max_y, p0);
        if (orientation > 0)
            num_inter++;
    }
    return num_inter % 2;
}
int main() {
    size_t n;
    int64_t x0, y0;

    std::cin >> n >> x0 >> y0;
    std::vector<point> polyg;
    point p0 = point(x0, y0);

    for (size_t i = 0; i < n; i++) {
        int64_t x, y;
        std::cin >> x >> y;
        polyg.emplace_back(x, y);
    }
    if (is_inner(p0, polyg))
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}
