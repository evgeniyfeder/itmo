#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cstring>

#define MAX_LEN 100
std::string file_name = "epsilon";
bool is_letter(char c) {
    return ('a' <= c && c <= 'z')
           || ('A' <= c && c <= 'Z');
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

    int n;
    char start;
    std::cin >> n >> start;

    std::queue<char> q;

    char str[MAX_LEN];

    std::cin.getline(str, MAX_LEN);

    std::vector<bool> isEpsilon(26);
    std::vector<std::pair<char, int>> sizeRightPart((unsigned int) n);
    std::vector<std::vector<int>> existed(26);

    for (int i = 0; i < n; i++) {
        char left_part;
        std::string right_part;

        memset(str, 0, MAX_LEN);
        std::cin.getline(str, MAX_LEN);
        left_part = str[0] - 'A';

        sizeRightPart[i].first = left_part;
        for (int j = 5; is_letter(str[j]); j++) {
            if ('A' <= str[j] && str[j] <= 'Z')
                existed[str[j] - 'A'].push_back(i);
            sizeRightPart[i].second++;
        }

        if (!is_letter(str[5])) {
            q.push(left_part);
            isEpsilon[left_part] = true;
        }
    }

    std::vector<bool> was(26);
    while (!q.empty()) {
        char cur_vert = q.front();
        q.pop();
        if (was[cur_vert])
            continue;
        was[cur_vert] = true;
        for (auto to = existed[cur_vert].begin(); to != existed[cur_vert].end(); ++to) {
            sizeRightPart[*to].second--;
            if (sizeRightPart[*to].second == 0) {
                q.push(sizeRightPart[*to].first);
                isEpsilon[sizeRightPart[*to].first] = true;
            }
        }
    }

    for (int i = 0; i < isEpsilon.size(); ++i)
        if (isEpsilon[i])
            std::cout << char('A' + i) << " ";
    return 0;
}
