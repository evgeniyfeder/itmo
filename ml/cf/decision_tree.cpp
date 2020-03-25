#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <map>
#include <memory>
#include <unordered_map>
#include <algorithm>

struct object_t
{
    std::vector<std::int32_t> xs;
    std::size_t y;

    object_t() {}

    object_t(std::vector<std::int32_t> xs, size_t y) : xs(std::move(xs)), y(y) {}
};

using objects_iterator_t = std::vector<object_t>::iterator;

std::size_t freq_class(objects_iterator_t from, objects_iterator_t to)
{
    std::unordered_map<std::size_t, std::size_t> cnt;
    std::size_t max_c = 0;

    for (auto it = from; it != to; ++it)
    {
        cnt[it->y]++;

        if (cnt[max_c] < cnt[it->y])
            max_c = it->y;
    }

    return max_c;
}

bool is_one_class(objects_iterator_t from, objects_iterator_t to)
{
    std::size_t x = from[0].y;

    for (auto it = from; it != to; ++it)
    {
        if (it->y != x)
            return false;
    }
    return true;
}

std::optional<std::pair<std::size_t, double>> split(objects_iterator_t left, objects_iterator_t right)
{
    std::optional<std::pair<std::size_t, double>> res;
    double max_s = 0;

    for (std::size_t f = 0; f < left->xs.size(); f++)
    {
        std::sort(left, right, [f](auto & x, auto & y) { return x.xs[f] < y.xs[f]; });

        std::unordered_map<std::size_t, std::int32_t> ys_l, ys_r;
        double sum_l = 0, sum_r = 0;

        for (auto it = left; it != right; ++it)
        {
            sum_r += 2 * ys_r[it->y] + 1;
            ys_r[it->y]++;
        }

        for (auto it = left; it != right; ++it)
        {
            sum_l += 2 * ys_l[it->y] + 1;
            ys_l[it->y]++;

            sum_r += -2 * ys_r[it->y] + 1;
            ys_r[it->y]--;

            if (it + 1 != right && it->xs[f] != (it + 1)->xs[f])
            {
                double s = sum_l / (it - left + 1) + sum_r / (right - it);
                if (s > max_s)
                {
                    max_s = s;
                    res = {f, (it->xs[f] + (it + 1)->xs[f]) / 2. };
                }
            }

        }
    }

    return res;
}

class decision_tree_t
{
public:
    decision_tree_t(std::vector<object_t> objs, std::size_t max_depth)
    : objs(objs), max_depth(max_depth)
    {
        head = std::make_unique<node_t>(0, max_depth, objs.begin(), objs.end());
    }

    void print()
    {
        std::size_t cnt = 1;
        head->print(cnt, false);
        std::cout << cnt - 1 << std::endl;
        cnt = 1;
        head->print(cnt, true);
    }
private:
    std::vector<object_t> objs;
    std::size_t max_depth;

    struct node_t
    {
        std::unique_ptr<node_t> left, right;
        std::size_t feat_idx = -1; // or class_idx
        double b = 0;

        node_t(std::size_t cur_depth, std::size_t max_depth, objects_iterator_t left_it, objects_iterator_t right_it)
        {
            if (cur_depth == max_depth)
            {
                feat_idx = freq_class(left_it, right_it);
                return;
            }

            if (is_one_class(left_it, right_it))
            {
                feat_idx = left_it->y;
                return;
            }

            if (auto res = split(left_it, right_it); res) // fidx_new, b_new
            {
                feat_idx = res->first;
                b = res->second;

                auto mid = std::partition(left_it, right_it, [res](auto & x) { return x.xs[res->first] < res->second; });
                left = std::make_unique<node_t>(cur_depth + 1, max_depth, left_it, mid);
                right = std::make_unique<node_t>(cur_depth + 1, max_depth, mid, right_it);
            }
            else
            {
                feat_idx = freq_class(left_it, right_it);
                return;
            }

        }

        void print(std::size_t & cnt, bool need_print = true)
        {
            if (left == nullptr)
            {
                if (need_print) std::cout << "C " << feat_idx + 1 << std::endl;
                cnt++;
            }
            else
            {
                std::size_t cur_node = cnt++;
                left->print(cnt, false);
                std::size_t right_node = cnt;
                right->print(cnt, false);

                if (need_print) std::cout << "Q " << feat_idx + 1 << " " << b << " " << cur_node + 1 << " " << right_node << std::endl;

                cnt = cur_node + 1;
                left->print(cnt, need_print);
                right->print(cnt, need_print);
            }
        }
    };

    std::unique_ptr<node_t> head;
};

int main()
{
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif

    std::size_t m, k, h;
    std::cin >> m >> k >> h;

    std::size_t n;
    std::cin >> n;


    std::vector<object_t> objs;
    for (std::size_t i = 0; i < n; i++)
    {
        object_t obj;
        obj.xs.resize(m);
        for (std::size_t j = 0; j < m; j++)
        {
            std::cin >> obj.xs[j];
        }
        std::cin >> obj.y;
        obj.y--;

        objs.push_back(obj);
    }

    decision_tree_t dt(std::move(objs), h);

    dt.print();
}
