#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>


int main()
{
#ifdef LOCAL
   freopen("test.in", "r", stdin);
   freopen("test.out", "w", stdout);
#endif

   std::ios_base::sync_with_stdio(false);

   std::size_t num_classes;
   std::cin >> num_classes;

   std::vector<std::size_t> class_errors(num_classes);
   for (std::size_t i = 0; i < num_classes; ++i)
   {
      std::size_t x;
      std::cin >> x;
      class_errors[i] = x;
   }

   std::int32_t alpha, num_test_objects;
   std::cin >> alpha >> num_test_objects;

   std::vector<std::unordered_map<std::string, std::size_t>> word_freq(num_classes);
   std::vector<std::size_t> class_count(num_classes);
   for (std::size_t i = 0; i < num_test_objects; ++i)
   {
      std::size_t clazz, num_words;
      std::cin >> clazz >> num_words;
      clazz--;

      std::unordered_set<std::string> words {};
      for (std::size_t j = 0; j < num_words; ++j)
      {
         std::string word;
         std::cin >> word;

         words.insert(word);
      }

      for (auto && w : words)
         word_freq[clazz][w]++;

      class_count[clazz]++;
   }

   std::vector<std::unordered_map<std::string, double>> P_O_C(num_classes);
   for (std::size_t c = 0; c < num_classes; ++c)
   {
      for (auto && e : word_freq[c])
      {
         P_O_C[c][e.first] = (double)(alpha + e.second) / (double)(class_count[c] + alpha * word_freq[c].size());
      }
   }


   std::vector<double > P_C(num_classes);
   for (std::size_t i = 0; i < num_classes; ++i)
   {
      P_C[i] = (double)class_count[i] / num_test_objects;
   }

   std::size_t num_req;
   std::cin >> num_req;
   std::cout.precision(10);
   for (std::size_t i = 0; i < num_req; ++i)
   {
      std::size_t num_word;
      std::cin >> num_word;

      std::unordered_set<std::string> words(num_word);

      for (std::size_t j = 0; j < num_word; j++)
      {
         std::string word;
         std::cin >> word;

         words.insert(word);
      }

      std::vector<double> scores(num_classes);

      std::size_t cnt = 0;
      double sum_scores = 0;
      for (std::size_t c = 0; c < num_classes; ++c)
      {
         if (class_count[c] != 0)
         {
            double score = log(class_errors[c] * P_C[c]);

            for (auto && w : words)
            {
               if (P_O_C[c].find(w) != P_O_C[c].end())
                  score += log(P_O_C[c][w]);
               else
                  score += log(alpha / (double) (class_count[c] + alpha * word_freq[c].size()));
            }
            scores[c] = score;
            cnt++;
            sum_scores += score;
         }
      }

      double avg = -sum_scores / cnt;
      sum_scores = 0;
      for (std::size_t c = 0; c < num_classes; ++c)
      {
         if (class_count[c] != 0)
         {
            scores[c] = exp(avg + scores[c]);
            sum_scores += scores[c];
         }
      }

      for (auto && s : scores)
         std::cout << s / sum_scores << ' ';
      std::cout << std::endl;
   }

}