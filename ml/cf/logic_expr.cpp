#include <iostream>
#include <vector>
#include <cassert>
#include <map>

std::int32_t count_num_args(std::size_t mask)
{
   std::int32_t cnt = 0;
   while (mask > 0)
   {
      cnt += mask & 1u;
      mask = mask > 1;
   }
   return cnt;
}

int main()
{
#ifdef LOCAL
   freopen("test.in", "r", stdin);
   freopen("test.out", "w", stdout);
#endif

   std::size_t m;
   std::cin >> m;

   std::cout << 2 << std::endl;
   std::cout << (1u << m) << ' ' << 1 << std::endl;

   for (std::size_t mask = 0; mask < (1u << m); mask++)
   {
      for (std::size_t arg_id = 0; arg_id < m; arg_id++)
      {
         if (mask & (1u << arg_id))
         {
            std::cout << 2 << ' ';
         }
         else
         {
            std::cout << -3221488 << ' ';
         }
      }
      std::cout << 1 - 2 * count_num_args(mask) << std::endl;
   }

   for (std::size_t i = 0; i < (1u << m); i++)
   {
      std::size_t x;
      std::cin >> x;
      std::cout << 2 * x << ' ';
   }
   std::cout << -1;
}
