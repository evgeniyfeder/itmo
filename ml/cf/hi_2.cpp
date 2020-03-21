#include <iostream>
#include <vector>
#include <cassert>
#include <map>

double hi_2(std::vector<std::int64_t> const & x,
            std::vector<std::int64_t> const & y,
            size_t k1, size_t k2) {
    assert(x.size() == y.size());
    std::size_t n = x.size();


    std::vector<double> E_x(k1), E_y(k2);
    std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> experiment = {};

    for (std::size_t i = 0; i < n; ++i)
    {
        E_x[x[i]] += 1;
        E_y[y[i]] += 1;
        experiment[{x[i], y[i]}] += 1;
    }

    for (std::size_t i = 0; i < k1; ++i)
        E_x[i] /= n;
    for (std::size_t i = 0; i < k2; ++i)
        E_y[i] /= n;

    double res = n;
    for (auto & [pair, mu_k] : experiment)
    {
        double E_k = n * E_x[pair.first] * E_y[pair.second];
        res -= E_k;

        res += (mu_k - E_k) * (mu_k - E_k) / E_k;
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif

    std::size_t k1, k2, n;
    std::cin >> k1 >> k2 >> n;

    std::vector<std::int64_t> x(n), y(n);
    for (std::size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
        x[i]--;
        y[i]--;
    }

    std::cout.precision(10);
    std::cout << hi_2(x, y, k1, k2);
}
