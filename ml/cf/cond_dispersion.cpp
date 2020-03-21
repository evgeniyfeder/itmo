#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using object_t = std::pair<std::int64_t, std::int64_t>;

double cond_dispersion(std::vector<object_t> const & objs, std::size_t k)
{
    double res = 0;

    // E(D(y|x)) = E(E(y^2|x) - E(y|x)^2) = E(y^2) - E(E(y|x)^2)
    double E_y_2 = 0;
    for (auto & [x, y]: objs)
    {
        E_y_2 += y * y * (1. / objs.size());
    }

    double E_E_y_of_x_2 = 0;

    std::vector<double> p_x(k, 0);
    std::vector<double> e_y_of_x(k, 0);
    for (auto & [x, y]: objs)
    {
        p_x[x - 1] += 1. / objs.size();
        e_y_of_x[x - 1] += static_cast<double>(y) / objs.size();
    }

    for (std::size_t i = 0; i < k; i++)
    {
        if (p_x[i] != 0)
            E_E_y_of_x_2 += e_y_of_x[i] * e_y_of_x[i] / p_x[i];
    }

    return E_y_2 - E_E_y_of_x_2;
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

    std::cout.precision(10);
    std::cout <<  cond_dispersion(objs, k);
}
