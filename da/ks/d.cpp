#include <iostream>
#include <vector>

typedef std::pair<char, std::string> paircstr;
typedef std::pair<char, char> paircc;

const int mod = 1000000007;
std::string file_name = "test";
// std::string file_name = "nfc";

std::vector<std::vector<std::vector<long long>>> dp(26);
std::vector<paircstr> ksg_strings_vars;
std::vector<paircc> ksg_strings_let;

int main() {
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);

    int n;
    char start;

    std::ios_base::sync_with_stdio(false);
    std::cin >> n >> start;
    start -= 'A';

    for (int i = 0; i < n; i++) {
        char left_part;
        std::string middle, right_part;
        std::cin >> left_part >> middle >> right_part;
        if (right_part.size() == 2)
            ksg_strings_vars.push_back(paircstr(left_part, right_part));
        else
            ksg_strings_let.push_back(paircc(left_part, right_part[0]));
    }

    std::string word;
    std::cin >> word;
    for (int i = 0; i < 26; i++) {
        dp[i].resize(word.size());
        for (int j = 0; j < word.size(); j++) {
            dp[i][j].resize(word.size());
        }
    }

    /* Initialize dp vector */
    for (int i = 0; i < word.size(); i++) {
        for (auto str = ksg_strings_let.begin(); str != ksg_strings_let.end(); ++str) {
            if (str->second == word[i])
                dp[str->first - 'A'][i][i] = true;
        }
    }

    for (int len = 1; len < word.size(); len++) {
        for (int i = 0; i < word.size() - len; i++) {
            for (auto str = ksg_strings_vars.begin(); str != ksg_strings_vars.end(); ++str) {
                for (int k = 0; k < len; k++) {
                    dp[str->first - 'A'][i][i + len] = (dp[str->first - 'A'][i][i + len] + dp[str->second[0] - 'A'][i][i + k] * dp[str->second[1] - 'A'][i + k + 1][i + len]) % mod;
                }
            }
        }
    }

    std::cout << (dp[start][0][word.size() - 1] % mod);
    return 0;
}