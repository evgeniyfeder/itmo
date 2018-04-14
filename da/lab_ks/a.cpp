#include <iostream>
#include <vector>
#include <unordered_map>

bool check(char cur_var, std::string &word,
           int cur_str_ind, std::string &builded_word,
           std::unordered_map<char, std::vector<std::string>> &ksg) {
    if (cur_str_ind == word.size())
        return false;
    bool result = false;
    for (auto out = ksg[cur_var].begin(); out != ksg[cur_var].end(); ++out) {
        if (out->size() == 1) {
            result |= (cur_str_ind == word.size() - 1 && (*out)[0] == word[word.size() - 1]);
        }
        else {
            if ((*out)[0] == word[cur_str_ind]) {
                builded_word.push_back(word[cur_str_ind]);
                result |= check((*out)[1], word, cur_str_ind + 1, builded_word, ksg);
                builded_word.pop_back();
            }
        }
    }
    return result;
}

std::string file_name = "automaton";
int main() {
#ifdef NDEBUG
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
#endif
    std::ios_base::sync_with_stdio(false);
    std::unordered_map<char, std::vector<std::string>> ksg;

    int n;
    char start;
    std::cin >> n >> start;

    for (int i = 0; i < n; i++) {
        char left_part;
        std::string middle, right_part;
        std::cin >> left_part >> middle >> right_part;
        ksg[left_part].push_back(right_part);
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        std::string word;
        std::cin >> word;
        std::string builded_word;
        if (check(start, word, 0, builded_word, ksg))
            std::cout << "yes" << std::endl;
        else
            std::cout << "no" << std::endl;
    }
    return 0;
}