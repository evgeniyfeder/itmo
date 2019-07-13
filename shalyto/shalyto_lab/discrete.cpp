#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using node_map = std::unordered_map<char, double>;
struct Node
{
   size_t left, right;
   node_map left_c, right_c;
};

void inc_val(node_map & m, char c, size_t len)
{
   auto iter = m.find(c);
   if (iter == m.end())
      m.insert({c, 1. / len});
   else
      iter->second += 1. / len;
}

char find_ans(node_map const & m)
{
   double cmax = 0;
   char c = 'a';
   for (auto && it : m)
   {
      if (cmax < it.second) {
         cmax = it.second;
         c = it.first;
      }
   }
   return c;
}

int main()
{
   freopen("discrete.in", "r", stdin);
   freopen("discrete.out", "w", stdout);
   std::ios_base::sync_with_stdio(false);
   size_t n, m;
   std::cin >> n >> m;

   std::vector<Node> a(n);
   for (size_t i = 0; i < n; i++)
   {
      size_t left, right;
      std::cin >> left >> right;
      a[i].left = left - 1;
      a[i].right = right - 1;
   }

   for (size_t i = 0; i < m; i++)
   {
      size_t len;
      std::cin >> len;

      std::string in, out;
      std::cin >> in >> out;

      size_t cur_ind = 0;
      for (size_t j = 0; j < len; j++)
      {
         if (in[j] == '0')
         {
            inc_val(a[cur_ind].left_c, out[j], len);
            cur_ind = a[cur_ind].left;
         }
         else
         {
            inc_val(a[cur_ind].right_c, out[j], len);
            cur_ind = a[cur_ind].right;
         }
      }
   }

   for (size_t i = 0; i < n; i++)
   {
      std::cout << find_ans(a[i].left_c) << ' ' << find_ans(a[i].right_c) << std::endl;
   }
}
