#include <iostream>
#include <vector>
#include <algorithm>

struct plane {
    int32_t a, b, c;


    plane(int32_t a, int32_t b, int32_t c) : a(a), b(b), c(c) {}
};

struct dual_plane {
    int32_t x, y;
    dual_plane(plane const & p) {

    }
};

struct point {
    int32_t x, y;
};

int32_t sign(int32_t x) {
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    return 0;
}

int32_t normal_rotate_predicate(plane const & a, plane const & b) {
    // a - 0, 0 b - a, c - b
    return sign(a.a * b.b - b.a * a.b);
}

std::vector<point> create_hull(std::vector<plane> planes) {
    //std::sort(planes.begin(), planes.end(), [](plane const & a, plane const & b){return normal_rotate_predicate(a, b) > 0; })

}

int main() {
    size_t n;
    std::cin >> n;

    std::vector<plane> planes_up, planes_down;
    for (size_t i = 0; i < n; i++) {
        int32_t a, b, c;
        std::cin >> a >> b >> c;

        if (b >= 0) {
            planes_up.emplace_back(a, b, c);
        } else {
            planes_down.emplace_back(a, b, c);
        }
    }


    return 0;
}
