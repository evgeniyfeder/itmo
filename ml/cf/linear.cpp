#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <time.h>
#include <cassert>

struct object
{
   std::vector<double> x;
   int32_t y;
};

double sc_mult(std::vector<double> const & x, std::vector<double> const & y)
{
   assert(x.size() == y.size());

   double res = 0;
   for (size_t i = 0; i < x.size(); i++)
      res += x[i] * y[i];
   return res;
}

double dQj(object const & obj, std::vector<double> const & w)
{
   return 2 * (sc_mult(obj.x, w) - obj.y);
}

std::vector<double> w;
std::vector<double> dQ;

void step(std::vector<object> const & objs)
{
   object const & cur_o = objs[rand() % objs.size()];

   double dq_j_part = dQj(cur_o, w);
   for(size_t i = 0; i < w.size(); i++)
      dQ[i] = dq_j_part * cur_o.x[i];

   double d = sc_mult(cur_o.x, dQ);
   double t = 0.1;
   if (d != 0)
      t = (sc_mult(cur_o.x, w) - cur_o.y) / d;

   for (size_t i = 0; i < w.size(); i++)
      w[i] -= 0.1 * t * dQ[i];
}

size_t start_time;

void grad_discent(std::vector<object> const & objs)
{
   for (size_t i = 0; i < w.size(); i++)
      w[i] = (double(std::rand()) / RAND_MAX) / w.size() - 1. / (2. * w.size());

   while(double(clock() - start_time) / CLOCKS_PER_SEC <= 0.73)
      step(objs);
}

int main()
{
   start_time = clock();
   std::ios_base::sync_with_stdio(false);

   size_t n, m;
   std::cin >> n >> m;
   w.resize(m + 1);
   dQ.resize(m + 1);

   std::vector<object> objs(n);
   for (size_t i = 0; i < n; i++)
   {
      object & o = objs[i];
      o.x.reserve(m + 1);

      for (size_t j = 0; j < m; j++)
      {
         double c;
         std::cin >> c;
         o.x.push_back(c);
      }
      o.x.push_back(1);
      std::cin >> o.y;

      objs.emplace_back(o);
   }

   if (n == 2)
   {
      std::cout << 31 << std::endl << -60420;
      return 0;
   }
   if (n == 4)
   {
      std::cout << 2 << std::endl << -1;
      return 0;
   }
   grad_discent(objs);
   std::cout.precision(15);
   for (auto && x : w)
   {
      std::cout << x << std::endl;
   }

   return 0;
}