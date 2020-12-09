#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
#include <list>
#include <unordered_map>
#include <map>
#include <cmath>

using byte_vector = std::vector<std::uint8_t>;
using int16_vector = std::vector<std::uint16_t>;

std::tuple<byte_vector, std::size_t> borrow_uiller(byte_vector const & xs)
{
   byte_vector x = xs;
   std::size_t n = x.size();

   std::vector<std::size_t> index;
   index.reserve(n);

   for (std::size_t i = 0; i < n; i++)
   {
      index.push_back(i);
   }

   for (std::size_t i = 0; i < n; i++)
      x.push_back(x[i]);

   auto comp = [&x, n] (std::size_t start_1, std::size_t start_2)
   {
      for (std::size_t i = 0; i < n; i++)
      {
         std::uint8_t cur_1 = x[start_1 + i], cur_2 = x[start_2 + i];
         if (cur_1 != cur_2)
            return cur_1 < cur_2;
      }
      return false;
   };

   std::sort(index.begin(), index.end(), comp);

   byte_vector res;
   res.reserve(n);

   std::size_t start;
   for (std::size_t i = 0; i < n; i++)
   {
      if (index[i] == 0)
         start = i;
      res.push_back(x[index[i] + n - 1]);
   }

   return {res, start};
}

byte_vector reverse_borrow_uiller(byte_vector const & x, std::size_t start)
{
   std::size_t n = x.size();

   std::vector<std::size_t> index;
   index.reserve(n);

   for (std::size_t i = 0; i < n; i++)
   {
      index.push_back(i);
   }

   auto comp = [&x] (std::size_t i, std::size_t j)
   {
      return x[i] < x[j];
   };

   std::stable_sort(index.begin(), index.end(), comp);

   byte_vector res;
   res.reserve(n);

   std::size_t cur = start;
   for (std::size_t i = 0; i < n; i++)
   {
      res.push_back(x[index[cur]]);
      cur = index[cur];
   }
   return res;
}


byte_vector mtf_coding(byte_vector const & x)
{
   std::vector<std::int32_t> output;

   std::list<std::uint8_t> mtf_list;

   for (std::uint16_t i = 0; i <= 255; i++)
      mtf_list.push_back(i);
   byte_vector result;

   result.reserve(x.size());
   for (std::uint8_t c : x)
   {
      std::uint8_t index = 0;
      for (auto it = mtf_list.begin(); it != mtf_list.end(); ++it)
      {
         if (*it == c)
         {
            mtf_list.erase(it);
            break;
         }
         index++;
      }
      mtf_list.push_front(c);
      result.push_back(index);
   }

   return result;
}

byte_vector mtf_decoding(byte_vector const & x)
{
   std::vector<std::int32_t> output;

   std::list<std::uint8_t> mtf_list;

   for (std::uint16_t i = 0; i <= 255; i++)
      mtf_list.push_back(i);
   byte_vector result;

   result.reserve(x.size());
   for (std::uint8_t c : x)
   {
      std::uint8_t index = 0;
      for (auto it = mtf_list.begin(); it != mtf_list.end(); ++it)
      {
         if (index == c)
         {
            std::uint8_t old = *it;
            result.push_back(old);
            mtf_list.erase(it);
            mtf_list.push_front(old);
            break;
         }
         index++;
      }

   }

   return result;
}

std::size_t count_num_bit(std::uint16_t x)
{
   std::size_t result = 0;
   while (x > 0)
   {
      result++;
      x = x >> 1u;
   }
   return result;
}

void write_bit(byte_vector & v, std::size_t & first_free_elem, std::uint8_t bit)
{
   v[v.size() - 1] = v[v.size() - 1] | (bit << first_free_elem++);
   if (first_free_elem == 8)
   {
      v.push_back(0);
      first_free_elem = 0;
   }
}

byte_vector uniform_code(byte_vector const & x)
{
   byte_vector result(1);
   std::size_t first_free_elem = 0;

   for (std::size_t i = 0; i < x.size(); i++)
   {
      std::uint16_t cur_number = x[i];

      // Hack to remove 0
      cur_number = cur_number + 1;

      std::size_t num_bits = count_num_bit(cur_number);


      for (std::size_t j = 0; j + 1 < num_bits; j++)
      {
         write_bit(result, first_free_elem, 1);
      }
      write_bit(result, first_free_elem, 0);

      for (std::size_t j = 1; j < num_bits; j++)
      {
         write_bit(result, first_free_elem, (cur_number >> (num_bits - j - 1)) & 1u);
      }
   }

   while (first_free_elem != 0)
      write_bit(result, first_free_elem, 1);
   result.pop_back();

   return result;
}

std::uint8_t read_bit(byte_vector const & v, std::size_t & cur_elem, std::size_t & cur_bit)
{
   if (cur_elem >= v.size())
      return 2;

   std::uint8_t res = (v[cur_elem] >> cur_bit++) & 1;
   if (cur_bit == 8)
   {
      cur_bit = 0;
      cur_elem++;
   }
   return res;
}

byte_vector uniform_decode(byte_vector const & x)
{
   byte_vector result;
   std::size_t cur_bit = 0, cur_elem = 0;

   while (true)
   {
      std::uint8_t last, len = 0;
      while ((last = read_bit(x, cur_elem, cur_bit)) == 1)
      {
         len++;
      }

      if (last == 2)
         return result;

      std::uint8_t c = 1 << len;
      for (std::size_t i = 1; i <= len; i++)
      {
         last = read_bit(x, cur_elem, cur_bit);
         c |= last << (len - i);
      }

      result.push_back(c - 1);
   }
}

std::tuple<byte_vector, std::size_t> code(byte_vector const & x)
{
   auto const & [a, b] = borrow_uiller(x);
   byte_vector mtfed = mtf_coding(a);

   return {uniform_code(mtfed), b};
   //return {a, b};

}

byte_vector decode(byte_vector const & x, std::size_t start_borrow)
{
   return reverse_borrow_uiller(mtf_decoding(uniform_decode(x)), start_borrow);
   //return reverse_borrow_uiller(x, start_borrow);
}

double count_hx(byte_vector const & x)
{
   double res = 0;

   std::unordered_map<std::uint8_t, double> p{};

   for (auto c: x)
   {
      p[c]++;
   }

   for (auto & [key, px] : p)
   {
      px = px / x.size();
      res -= px * log2(px);
   }

   return res;
}

double count_hxx(byte_vector const & x)
{
   double res = 0;

   std::unordered_map<std::uint8_t, double> p{};
   std::map<std::pair<std::uint8_t,std::uint8_t>, double> p_pair{};

   p[x[0]]++;
   for (std::size_t i = 1; i < x.size(); i++)
   {
      p[x[i]]++;
      p_pair[{x[i], x[i - 1]}]++;
   }

   for (auto & [key, px] : p_pair)
   {
      auto & [key_cur, key_prev] = key;

      px = px / p[key_prev];
      res -= (p[key_prev] / x.size()) * px * log2(px);
   }

   return res;
}

double count_hxxx(byte_vector const & x)
{
   double res = 0;

   std::map<std::pair<std::uint8_t,std::uint8_t>, double> p{};
   std::map<std::tuple<std::uint8_t,std::uint8_t,std::uint8_t>, double> p_pair{};

   p[{x[1],x[0]}]++;
   p[{x[2],x[1]}]++;

   for (std::size_t i = 2; i < x.size(); i++)
   {
      p[{x[i], x[i - 1]}]++;
      p_pair[{x[i], x[i - 1], x[i - 2]}]++;
   }

   for (auto & [key, px] : p_pair)
   {
      auto & [key_cur, key_prev, key_preprev] = key;

      px = px / p[{key_prev, key_preprev}];
      res -= (p[{key_prev, key_preprev}] / (x.size() - 2)) * px * log2(px);
   }

   return res;
}

void count_metricks(std::string name, byte_vector const & x, byte_vector const & res)
{
   std::size_t Z = sizeof(std::size_t) + res.size();

   std::cout << name << " & " << count_hx(x) << " & " << count_hxx(x) << " & " << count_hxxx(x) << " & " << 8. * Z / x.size() << " & " << Z << " \\\\ " << std::endl;
}


int main(int argc, char *argv[])
{
   if (argc != 4)
   {
      std::cout << "Wrong argmuents: {code, decode} input_file output_file" << std::endl;
      return 0;
   }

   if (std::string(argv[1]) == "code")
   {
      std::ifstream inf(argv[2], std::ios_base::binary);

      std::string buffer_string(std::istreambuf_iterator<char>(inf), {});

      byte_vector buffer(buffer_string.size());

      for (std::size_t i = 0; i < buffer.size(); i++)
         buffer[i] = static_cast<std::uint8_t>(buffer_string[i]);

      auto const & [result, start] = code(buffer);

      count_metricks(argv[3], buffer, result);

      std::ofstream ouf(argv[3], std::ios_base::binary);

      ouf.write((char *)&start, sizeof(std::size_t));
      ouf.write((char *)result.data(), result.size());

      ouf.close();
      inf.close();
   }
   else if (std::string(argv[1]) == "decode")
   {
      std::ifstream inf(argv[2], std::ios_base::binary);

      std::string buffer_string(std::istreambuf_iterator<char>(inf), {});

      byte_vector buffer(buffer_string.size() - sizeof(std::size_t));

      std::size_t start_borrow = ((std::size_t *)buffer_string.data())[0];

      for (std::size_t i = 0; i < buffer.size(); i++)
         buffer[i] = static_cast<std::uint8_t>(buffer_string[i + sizeof(std::size_t)]);

      byte_vector result = decode(buffer, start_borrow);

      std::ofstream ouf(argv[3], std::ios_base::binary);

      ouf.write((char *)result.data(), result.size());

      ouf.close();
      inf.close();
   }
   else
   {
      std::cout << "Mode needs to be 'code' or 'decode'" << std::endl;
   }

}