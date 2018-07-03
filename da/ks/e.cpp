#include <iostream>
#include <vector>
#include <cstring>

#define MAX_STR 100
typedef std::pair<char, std::string> paircstr;
typedef std::pair<char, char> paircc;

bool is_letter(char c) {
    return ('a' <= c && c <= 'z')
           || ('A' <= c && c <= 'Z');
}

bool is_big(char c) {
    return ('A' <= c && c <= 'Z');
}

// std::string file_name = "";
std::string file_name = "test";

int main() {
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
    std::ios_base::sync_with_stdio(false);

    int n;
    char start;
    std::cin >> n >> start;

    std::vector<paircstr> ksg_strings_nsmall;
    std::vector<paircstr> ksg_strings_small;
    std::vector<char> ksg_strings_zero;
    char str[MAX_STR];
    std::cin.getline(str, MAX_STR);
    for (int i = 0; i < n; i++) {
        memset(str, 0, MAX_STR);

        std::cin.getline(str, MAX_STR);
        char left_part = str[0] - 'A';
        std::string right_part;
        bool is_small = true;
        for (int j = 5; is_letter(str[j]); j++) {
            if (is_big(str[j]))
                is_small = false;
            right_part.push_back(str[j]);
        }
        if (is_small)
            ksg_strings_small.push_back(paircstr(left_part, right_part));
        else if (right_part.size() == 0)
            ksg_strings_zero.push_back(left_part);
        else
            ksg_strings_nsmall.push_back(paircstr(left_part, right_part));
    }

    std::vector<std::vector<std::vector<bool>>> dp(26);

    std::string word;
    std::cin >> word;
    for (int i = 0; i < 26; i++) {
        dp[i].resize(word.size() + 1);
        for (int j = 0; j < word.size(); j++) {
            dp[i][j].resize(word.size() + 1);
        }
    }

    std::vector<std::vector<std::vector<std::vector<bool>>>> dp_prefix(26);
    for (int i = 0; i < 26; i++) {
        dp_prefix[i].resize(word.size() + 1);
        for (int j = 0; j < word.size(); j++) {
            dp_prefix[i][j].resize(word.size() + 1);
            for (int k = 0; k < word.size(); k++)
                dp_prefix[i][j][k].resize(100);
        }
    }

    /* Initialize dp */
    for (int i = 0; i < word.size(); i++) {
        int j = 0;
        for (auto str = ksg_strings_small.begin(); str != ksg_strings_small.end(); ++str, ++j) {
            if (str->second.size() == 1 && str->second[0] == word[i]) {
                dp[str->first][i][i + 1] = true;
            }
            dp_prefix[j][i][i][0] = true;
        }
        for (auto str = ksg_strings_zero.begin(); str != ksg_strings_zero.end(); ++str) {
                dp[*str][i][i] = true;
        }
    }

    /* Count dp */
    for (int len = 1; len < word.size(); len++) {
        for (int i = 0; i < word.size(); i++) {
            int j = i + len;
            for (int str = 0; str < ksg_strings_small.size(); ++str) {
                for (int k = 1; k < ksg_strings_small[str].second.size(); k++) {
                    for (int r = i; r < j + 1; r++) {
                        dp_prefix[str][i][j + 1][k] = dp_prefix[str][i][j + 1][k] | (dp_prefix[str][i][r][k - 1] & dp[ksg_strings_small[str].second[k]][r][j + 1]);
                    }
                }
            }
        }
    }

    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < word.size(); j++)
           for (int str = 0; str < ksg_strings_small.size(); ++str) {
               for (int str_a = 0; str_a < ksg_strings_small.size(); ++str_a) {
                   if (ksg_strings_small[str_a].first == ksg_strings_small[str].first) {
                       dp[ksg_strings_small[str_a].first][i][j] = dp[ksg_strings_small[str_a].first][i][j] | dp_prefix[str_a][i][j][ksg_strings_small[str_a].second.size()];
                   }
               }
           }
    }
    std::cout << (dp[start][0][word.size() - 1] ? "yes" : "no");

            return 0;
}