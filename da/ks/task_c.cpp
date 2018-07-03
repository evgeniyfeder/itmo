#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cstring>

#define BEGIN_RIGHT 5
#define MAX_LEN 228

std::vector<std::pair<char, std::pair<int, std::string>>> ksg_strings;
std::vector<std::vector<int>> var_in_str(26);
std::vector<bool> is_exist(26);
std::unordered_map<char, std::unordered_map<std::string, bool>> ksg;
std::vector<bool> is_reacheble(26);


bool is_letter(char c) {
    return ('a' <= c && c <= 'z')
           || ('A' <= c && c <= 'Z');
}

bool is_big(char c) {
    return ('A' <= c && c <= 'Z');
}

std::vector<bool> was;
void dfs(char cur_vert) {
    if (was[cur_vert])
        return;
    was[cur_vert] = true;

    for (auto i = ksg[cur_vert].begin(); i != ksg[cur_vert].end(); ++i) {
        for (auto to = i->first.begin(); to != i->first.end(); ++to) {
            dfs(*to - 'A');
        }
    }
}

std::vector<bool> check_reacheble () {
    std::queue<char> queue;

    for (char i = 0; i < 26; i++) {
        if (is_reacheble[i])
            queue.push(i);
    }

    std::vector<bool> was_reac(26);
    while (!queue.empty()) {
        char cur_vert = queue.front();
        queue.pop();
        if (was_reac[cur_vert])
            continue;

        was_reac[cur_vert] = true;
        for (int i = 0; i < var_in_str[cur_vert].size(); i++) {
            ksg_strings[var_in_str[cur_vert][i]].second.first--;
            if (ksg_strings[var_in_str[cur_vert][i]].second.first == 0) {
                queue.push(ksg_strings[var_in_str[cur_vert][i]].first);
                is_reacheble[ksg_strings[var_in_str[cur_vert][i]].first] = true;
            }
        }
    }

    return is_reacheble;
}
int main() {
    FILE *InF, *OutF;
    InF = fopen("useless.in", "r");
    OutF = fopen("useless.out", "w");
    was.resize(26);
    int n;
    char start;
    fscanf(InF, "%d %c", &n, &start);
    start -= 'A';
    char str[MAX_LEN];

    ksg_strings.resize((size_t)n);
    is_exist[start] = true;

    fgets(str, MAX_LEN, InF);
    for (int i = 0; i < n; i++) {
        memset(str, 0, MAX_LEN);
        fgets(str, MAX_LEN, InF);

        char left;
        left = str[0] - 'A';
        is_exist[left] = true;
        ksg_strings[i].first = left;

        bool is_small = true;
        std::string right;
        for (int j = BEGIN_RIGHT; is_letter(str[j]); j++) {
            if (is_big(str[j])) {
                is_small = false;
                is_exist[str[j] - 'A'] = true;

                ksg_strings[i].second.first++;
                var_in_str[str[j] - 'A'].push_back(i);
            }
            right.push_back(str[j]);
        }
        ksg[left][right] = true;
        ksg_strings[i].second.second = right;
        if (!is_letter(str[BEGIN_RIGHT]) || is_small) {
            ksg_strings[i].second.first = 1;
        }
        if (is_small)
            is_reacheble[left] = true;
    }

    check_reacheble();
    for (char i = 0; i < 26; i++) {
        if ((is_exist[i] && !is_reacheble[i])) {
            for (auto j = var_in_str[i].begin(); j != var_in_str[i].end(); ++j) {
                ksg[ksg_strings[*j].first].erase(ksg_strings[*j].second.second);
            }
            ksg.erase(i);
        }
    }
    dfs(start);
    for (int i = 0; i < 26; ++i)
        if ((is_exist[i] && !is_reacheble[i]) || (is_exist[i] && !was[i]))
            fprintf(OutF, "%c ", char('A' + i));
    return 0;
}
