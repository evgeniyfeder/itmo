#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

double get_f(double x, size_t dim, size_t size) {
   for (size_t i = 0; i < dim; i++) {
      std::cout << "0 ";
   }
   std::cout << x << " ";
   for (size_t i = dim + 1; i < size; i++)
   {
      std::cout << "0 ";
   }
   std::cout << std::endl;

   double res;
   std::cin >> res;

   return res;
}

int main()
{
   size_t n;
   std::cin >> n;

   std::cout << std::fixed << std::setprecision(6);

   std::vector<double> mins_f(n, 1e9);
   std::vector<double> mins_x(n, 1);
   for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < 20; j++)
      {
         double l = static_cast<double>(j) / 20., r = static_cast<double>(j + 1) / 20.;
         for (size_t k = 0; k < 20; k++)
         {
            double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;

            if (get_f(m1, i, n) < get_f(m2, i, n))
            {
               r = m2;
            }
            else
            {
               l = m1;
            }
         }
         double f = get_f(r, i, n);
         if (f < mins_f[i]) {
            mins_f[i] = f;
            mins_x[i] = r;
         }
      }
   }

   for (double x : mins_x) {
      std::cout << x << ' ';
   }
   std::cout << std::endl;

   double res;
   std::cin >> res;

   std::cout << "minimum " << res << std::endl;

   return 0;
}
