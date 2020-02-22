#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>


using object_t = std::pair<std::int32_t, std::int32_t>;

double count_k_pirson(std::vector<object_t> const & xs)
{
   double med_x = 0, med_y = 0;
   for (auto const & x : xs)
   {
      med_x += x.first;
      med_y += x.second;
   }
   med_x /= xs.size();
   med_y /= xs.size();

   double cov_xy = 0, s_x = 0, s_y = 0;
   for (auto const & x : xs)
   {
      cov_xy += (x.first - med_x) * (x.second - med_y);
      s_x += (x.first - med_x) * (x.first - med_x);
      s_y += (x.second - med_y) * (x.second - med_y);
   }
   if (s_x != 0 && s_y != 0)
      return cov_xy / sqrt(s_x * s_y);
   else
      return 0;
}

std::vector<std::int64_t> count_rangs(std::vector<std::int32_t> const & x)
{
   std::vector<std::pair<std::int32_t, std::size_t>> indexed_x(x.size());

   for (std::size_t i = 0; i < x.size(); i++)
      indexed_x[i] = {x[i], i};
   std::sort(indexed_x.begin(), indexed_x.end());

   std::vector<std::int64_t> rangs(x.size());

   std::size_t r = 0;

   rangs[indexed_x[0].second] = r;
   for (std::size_t i = 1; i < x.size(); i++)
   {
      if (indexed_x[i].first != indexed_x[i - 1].first)
         r++;
      rangs[indexed_x[i].second] = r;
   }

   return rangs;
}

double count_k_spirmen(std::vector<std::int32_t> const & x, std::vector<std::int32_t> const & y)
{
   assert(x.size() == y.size());

   std::vector<std::int64_t> rangs_x = count_rangs(x);
   std::vector<std::int64_t> rangs_y = count_rangs(y);

   std::int64_t n = x.size();
   std::int64_t d_2 = 0;
   for (std::size_t i = 0; i < n; i++)
      d_2 += (rangs_x[i] - rangs_y[i]) * (rangs_x[i] - rangs_y[i]);

   return 1 - (6. * d_2) / double(n * (n * n - 1));
}

int main()
{
#ifdef LOCAL
   freopen("test.in", "r", stdin);
   freopen("test.out", "w", stdout);
#endif
   std::size_t n;
   std::cin >> n;

   std::vector<std::int32_t> x(n);
   std::vector<std::int32_t> y(n);

   for (std::size_t i = 0; i < n; i++)
      std::cin >> x[i] >> y[i];

   std::cout.precision(10);
   std::cout << count_k_spirmen(x, y) << std::endl;
}