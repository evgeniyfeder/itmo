#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Node {
    size_t left, right;
    char c;
};

int main() {
    freopen("start.in", "r", stdin);
    freopen("start.out", "w", stdout);

    size_t m, n;
    std::cin >> m >> n;

    std::vector<Node> a(n);
    for (size_t i = 0; i < n; i++) {
        size_t left, right;
        std::cin >> left >> right;

        std::string c;
        std::cin >> c;
        a[i].left = left - 1;
        a[i].right = right - 1;
        a[i].c = c[0];
    }
    std::string s;
    std::cin >> s;

    std::vector<std::vector<bool>> dp(n, std::vector<bool>(2));
    for (size_t i = 0; i < n; i++)
        dp[i][0] = true;

    for (int32_t i = m - 1; i >= 0; i--) {
        for (size_t j = 0; j < n; j++) {
            dp[j][1] = false;
            if (a[a[j].left].c == s[i])
                dp[j][1] = dp[j][1] | dp[a[j].left][0];
            if (a[a[j].right].c == s[i])
                dp[j][1] = dp[j][1] | dp[a[j].right][0];
        }
        for (size_t j = 0; j < n; j++)
            dp[j][0] = dp[j][1];
    }

    std::vector<size_t> res;
    for (size_t i = 0; i < n; i++) {
        if (dp[i][1])
            res.push_back(i);
    }

    std::sort(res.begin(), res.end());
    std::cout << res.size() << ' ';
    for (auto x : res)
        std::cout << x + 1 << ' ';
    return 0;
}
