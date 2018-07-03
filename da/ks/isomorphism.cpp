#include <iostream>
#include <vector>
#include <unordered_map>

std::string file_name = "isomorphism";

std::vector<std::vector<int>> dka[2];
std::vector<bool> is_dopusk[2];

std::vector<int> deep[2];
bool check_isomorphic(int state0, int state1, int cur_deep) {
    bool result = true;
    if (is_dopusk[0][state0] && !is_dopusk[1][state1] || !is_dopusk[0][state0] && is_dopusk[1][state1])
        return false;
    if (deep[0][state0] == deep[1][state1] && deep[0][state0] != -1)
        return true;
    else if (deep[0][state0] == deep[1][state1] && deep[0][state0] == -1) {
        deep[0][state0] = cur_deep;
        deep[1][state1] = cur_deep;

        for (char i = 0; i < 26; i++) {
            if (dka[0][state0][i] != -1 && dka[1][state1][i] != -1) {
                result &= check_isomorphic(dka[0][state0][i], dka[1][state1][i], cur_deep + 1);
            } else if (dka[0][state0][i] == -1 && dka[1][state1][i] == -1) {
                continue;
            } else {
                result = false;
            }
        }
        return result;
    }
    else
        return false;
}

void get_dka(int ind) {
    size_t n, m, k;

    std::cin >> n >> m >> k;

    is_dopusk[ind].resize(n);
    for (int i = 0; i < k; i++) {
        int a;
        std::cin >> a;
        is_dopusk[ind][a - 1] = true;
    }

    dka[ind].resize(n);
    for (int i = 0; i < n; i++) {
        dka[ind][i].resize(26);
        for (int j = 0; j < 26; j++) {
            dka[ind][i][j] = -1;
        }
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        char sym;
        std::cin >> from >> to >> sym;
        dka[ind][from - 1][sym - 'a'] = to - 1;
    }

    deep[ind].resize(n);
    for (int i = 0; i < n; i++) {
        deep[ind][i] = -1;
    }
}

int main() {
#ifndef NDEBUG
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
#endif
    std::ios_base::sync_with_stdio(false);
    size_t n, m, k;
    get_dka(0);
    get_dka(1);
    std::cout << (check_isomorphic(0, 0, 0) ? "YES" : "NO");
    return 0;
}
