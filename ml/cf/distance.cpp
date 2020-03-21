#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using object_t = std::pair<std::int64_t, std::int64_t>;

std::int64_t inner_distance(std::vector<object_t> const & objs, std::size_t k)
{
    std::int64_t distance = 0;

    std::vector<object_t> copy(objs);
    std::sort(copy.begin(), copy.end(), [](auto & a, auto & b) { return a.second < b.second || (a.second == b.second && a.first < b.first); });

    std::int64_t start_window = 0, end_window = 0;
    for (std::size_t c = 0; c < k; c++)
    {
        std::int64_t pref_sum = 0, suf_sum = 0;
        while (end_window < objs.size() && copy[end_window].second == c)
        {
            suf_sum += copy[end_window].first;
            end_window++;
        }

        for (std::size_t i = start_window; i < end_window; i++)
        {
            std::int32_t x = copy[i].first;
            suf_sum -= x;
            distance += ((i - start_window) * x - pref_sum) + (suf_sum - (end_window - 1 - i) * x);
            pref_sum += x;
        }

        start_window = end_window;
    }
    return distance;
}


std::int64_t outer_distance(std::vector<object_t> const & objs, std::size_t k)
{
    std::int64_t distance = 0;

    std::vector<object_t> copy(objs);
    std::sort(copy.begin(), copy.end());

    // class -> (sum, cnt)
    std::unordered_map<std::size_t, std::pair<std::int64_t, std::int64_t>> pref_sum;
    std::int64_t pref_sum_total = 0;

    // class -> (sum, cnt)
    std::unordered_map<std::size_t, std::pair<std::int64_t, std::int64_t>> suf_sum;
    std::int64_t suf_sum_total = 0;

    for (auto && o : copy)
    {
        suf_sum[o.second] = {suf_sum[o.second].first + o.first, suf_sum[o.second].second + 1};
        suf_sum_total += o.first;
        pref_sum[o.second] = {0, 0};

    }

    for (int i = 0; i < copy.size(); i++)
    {
        object_t const & o = copy[i];

        suf_sum[o.second] = {suf_sum[o.second].first - o.first, suf_sum[o.second].second - 1 };
        suf_sum_total -= o.first;

        std::int64_t pref_d = (i - pref_sum[o.second].second) * o.first - (pref_sum_total - pref_sum[o.second].first);
        std::int64_t suf_d = (suf_sum_total - suf_sum[o.second].first) - ((objs.size() - 1 - i) - suf_sum[o.second].second) * o.first;
        distance += pref_d + suf_d;

        pref_sum[o.second] = {pref_sum[o.second].first + o.first, pref_sum[o.second].second + 1 };
        pref_sum_total += o.first;
    }
    return distance;
}


int main()
{
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif

    std::size_t k, n;
    std::cin >> k >> n;

    std::vector<object_t> objs(n);
    for (std::size_t i = 0; i < n; i++) {
        std::cin >> objs[i].first >> objs[i].second;
        objs[i].second--;
    }
    std::cout << inner_distance(objs, k) << std::endl;
    std::cout << outer_distance(objs, k) << std::endl;
}
