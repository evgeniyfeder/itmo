#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <tuple>
#include <algorithm>
#include <random>


using metric_t = std::vector<std::vector<std::int32_t>>;

// http://cs229.stanford.edu/materials/smo.pdf
class svm_model_t
{
public:
   svm_model_t(metric_t metric,
               std::vector<std::int32_t> ys,
               std::int32_t c,
               std::size_t max_t = 1000,
               double eps = 1e-6)
               : metric(std::move(metric)), ys(std::move(ys)), c(c), max_t(max_t), eps(eps)
   {
      n = this->ys.size();
   }



   std::tuple<std::vector<double>, double> build_model()
   {
      if (!alphas.empty())
         return {};

      b = 0;
      alphas.resize(n);

      std::vector<std::size_t> pairs(n);
      for (size_t i = 0; i < n; i++)
         pairs[i] = i;

      std::random_device rd;
      std::mt19937 g(rd());

      for (std::size_t t = 0; t < max_t; t++)
      {
         std::shuffle(pairs.begin(), pairs.end(), g);

         for (std::size_t i = 0; i < n; i++)
         {
            double E_i = f(i) - ys[i];

            if ((ys[i] * E_i < -eps && alphas[i] < c) || (ys[i] * E_i > eps && alphas[i] > 0))
            {
               std::size_t j = pairs[i];

               if (j == i)
                  continue;

               double E_j = f(j) - ys[j];

               if (std::abs(E_i - E_j) < eps)
                  continue;

               double L, H;
               if (ys[i] != ys[j])
               {
                  L = std::max(0., alphas[j] - alphas[i]);
                  H = std::min(c, c + alphas[j] - alphas[i]);
               }
               else
               {
                  L = std::max(0., alphas[j] + alphas[i] - c);
                  H = std::min(c, alphas[j] + alphas[i]);
               }

               if (std::abs(L - H) < eps)
                  continue;

               double eta = 2 * metric[i][j] - metric[i][i] - metric[j][j];
               if (eta >= eps)
                  continue;

               double aj_old = alphas[j];
               double aj = std::max(L, std::min(H, aj_old - ys[j] * (E_i - E_j) / eta));

               if (std::abs(aj - aj_old) < eps)
                  continue;

               double ai_old = alphas[i];
               double ai = ai_old + ys[i] * ys[j] * (aj_old - aj);

               double b_1 = b - E_i
                            - ys[i] * (ai - ai_old) * metric[i][i]
                            - ys[j] * (aj - aj_old) * metric[i][j];

               double b_2 = b - E_j
                            - ys[i] * (ai - ai_old) * metric[i][j]
                            - ys[j] * (aj - aj_old) * metric[j][j];

               if (0 < ai_old && ai_old < c)
                  b = b_1;
               else if (0 < aj_old && aj_old < c)
                  b = b_2;
               else
                  b = (b_1 + b_2) / 2;

               alphas[i] = ai;
               alphas[j] = aj;

            }
         }
      }

      return {alphas, b};
   }

private:
   double f(std::size_t i)
   {
      double res = 0;

      for (std::size_t j = 0; j < n; j++)
      {
         res += metric[i][j] * ys[j] * alphas[j];
      }
      res += b;

      return res;
   }

private:
   metric_t metric;
   std::vector<std::int32_t> ys;
   std::int32_t max_t;
   std::size_t n;

   std::vector<double> alphas;
   double b = 1, c, eps;
};


int main()
{
#ifdef LOCAL
   freopen("test.in", "r", stdin);
   freopen("test.out", "w", stdout);
#endif

   std::size_t n;
   std::cin >> n;

   metric_t metric(n, std::vector<std::int32_t>(n));
   std::vector<std::int32_t> ys(n);

   for (std::size_t i = 0; i < n; i++)
   {
      for (std::size_t j = 0; j < n; j++)
      {
         std::cin >> metric[i][j];
      }

      std::cin >> ys[i];
   }

   std::int32_t c;
   std::cin >> c;

   svm_model_t m(metric, ys, c);
   auto [alphas, b] = m.build_model();

   std::cin.precision(10);
   for (double a : alphas)
   {
      std::cout << a << std::endl;
   }
   std::cout << b;
}
