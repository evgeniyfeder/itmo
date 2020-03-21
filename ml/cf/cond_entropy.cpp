#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <cmath>

double cond_entropy(std::vector<std::int64_t> const & x,
                    std::vector<std::int64_t> const & y,
                    size_t k1, size_t k2)
{
    assert(x.size() == y.size());
    std::size_t n = x.size();

    std::vector<double> p_i(k1);
    std::map<std::pair<std::int64_t, std::int64_t>, double> p_ij = {};

    for (std::size_t i = 0; i < n; i++)
    {
        p_i[x[i]] += 1. / n;
        p_ij[{x[i], y[i]}] += 1. / n;
    }

    double res = 0;
    for (auto [pair, p] : p_ij)
    {
        double p_i_of_j = p / p_i[pair.first];
        res += -p * std::log(p_i_of_j);
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
    for (std::size_t i = 0; i < n; i++)
    {
        std::cin >> x[i] >> y[i];
        x[i]--;
        y[i]--;
    }

    std::cout.precision(10);
    std::cout << cond_entropy(x, y, k1, k2);
}
