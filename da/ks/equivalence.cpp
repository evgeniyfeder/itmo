#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

std::string file_name = "equivalence";

std::vector<std::vector<int>> dka[2];
std::vector<bool> is_dopusk[2];

bool check_equivalence() {
    typedef std::pair<int, int> pair;

    std::queue<pair> q;
    q.push(pair(0, 0));

    std::vector<bool> used1(dka[0].size()), used2(dka[1].size());
    while (!q.empty()) {
        pair &p = q.front();
        q.pop();

        int state0 = p.first, state1 = p.second;
        if (is_dopusk[0][state0] != is_dopusk[1][state1])
            return false;
        used1[state0] = true;
        used2[state1] = true;

        for (char i = 0; i < 26; i++) {
            if ((dka[0][state0][i] != dka[0].size() - 1 || dka[1][state1][i] != dka[1].size() - 1) &&
                    (!used1[dka[0][state0][i]] || !used2[dka[1][state1][i]])) {
                q.push(pair(dka[0][state0][i], dka[1][state1][i]));
            }
        }
    }
    return true;
}

void get_dka(int ind) {
    size_t n, m, k;

    std::cin >> n >> m >> k;

    is_dopusk[ind].resize(n + 1);
    for (int i = 0; i < k; i++) {
        int a;
        std::cin >> a;
        is_dopusk[ind][a - 1] = true;
    }

    dka[ind].resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        dka[ind][i].resize(26);
        for (int j = 0; j < 26; j++) {
            dka[ind][i][j] = n;
        }
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        char sym;
        std::cin >> from >> to >> sym;
        dka[ind][from - 1][sym - 'a'] = to - 1;
    }
}

int main() {
#ifdef NDEBUG
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
#endif
    std::ios_base::sync_with_stdio(false);
    get_dka(0);
    get_dka(1);
    std::cout << (check_equivalence() ? "YES" : "NO");
    return 0;
}

