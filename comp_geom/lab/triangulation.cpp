#include <iostream>
#include <vector>
#include <deque>
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

void triangulation_n3(std::vector<point> const &vec) {
    std::deque<size_t> deq;
    for (size_t i = 0; i < vec.size(); i++){
        deq.push_back(i);
    }

    while (deq.size() > 3) {
        size_t cur_ind = deq.front();
        deq.pop_front();
        size_t next_ind = deq.front();
        size_t prev_ind = deq.back();

        point cur = vec[cur_ind];
        point prev = vec[prev_ind];
        point next = vec[next_ind];

        if (sign_rotate_predicate(prev, cur, next) > 0) {
            bool is_ear = true;
            for (auto &&i : deq) {
                point v = vec[i];
                if (i != cur_ind && i != prev_ind && i != next_ind
                        && sign_rotate_predicate(prev, cur, v) >= 0
                        && sign_rotate_predicate(cur, next, v) >= 0
                        && sign_rotate_predicate(next, prev, v) >= 0) {
                    is_ear = false;
                    break;
                }
            }
            if (is_ear) {
                std::cout << cur_ind + 1 << ' ' << deq.front() + 1 << ' ' << deq.back() + 1 << std::endl;
            } else {
                deq.push_back(cur_ind);
            }
        } else {
            deq.push_back(cur_ind);
        }
    }
    size_t cur_ind = deq.front();
    deq.pop_front();

    std::cout << cur_ind + 1 << ' ' << deq.front() + 1 << ' ' << deq.back() + 1 << std::endl;
}

void triangulation_n2(std::vector<point> const &vec) {
    std::vector<size_t> stack;
    stack.reserve(vec.size());

    for (size_t i = 0; i < vec.size(); i++) {
        stack.push_back(i);

        while(stack.size() >= 3) {
            size_t
                    next_ind = stack[stack.size() - 1],
                    cur_ind = stack[stack.size() - 2],
                    prev_ind = stack[stack.size() - 3];
            point
                    a = vec[next_ind],
                    b = vec[cur_ind],
                    c = vec[prev_ind];
            if (sign_rotate_predicate(c, b, a) <= 0)
                break;

            bool is_ear = true;
            for (auto &&v : vec) {
                if (v != a && v != b && v != c
                        && sign_rotate_predicate(c, b, v) >= 0
                        && sign_rotate_predicate(b, a, v) >= 0
                        && sign_rotate_predicate(a, c, v) >= 0) {
                    is_ear = false;
                    break;
                }
            }
            if (is_ear) {
                std::cout << next_ind + 1 << ' ' << cur_ind + 1 << ' ' << prev_ind + 1 << std::endl;
                stack.pop_back();
                stack.back() = next_ind;
            } else {
                break;
            }
        }
    }
}

int main() {
    size_t n;
    std::cin >> n;

    std::ios_base::sync_with_stdio(false);
    std::vector<point> pts;
    for (size_t i = 0; i < n; i++) {
        int64_t x, y;
        std::cin >> x >> y;
        pts.emplace_back(x, y);
    }
    triangulation_n2(pts);
}
