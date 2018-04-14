//#define __NR__
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <cassert>
 
using namespace std;
#ifdef __NR__
ifstream cin("input.txt");
ofstream cout("output.txt");
#else
string file = "tiv";
ifstream cin(file + ".in");
ofstream cout(file + ".out");
#endif
 
const int max_n = 1005, inf = int(2e9);
const int cv = 26, max_len = 21;
 
int n;
vector<int> g[cv];
string word[max_n]; int len_word[max_n];
bool beg[max_n];
bool nil[cv];
 
string rest[max_len];
void init() {
    rest[0] = "";
    for (int i = 1; i < max_len; ++i) {
        rest[i] = rest[i-1] + '#';
    }
}
 
int deg[cv];
void add_adge(char a, char b) {
    g[size_t(a - 'a')].push_back(int(b - 'a'));
    deg[size_t(b - 'a')]++;
}
 
int val[cv];
vector<int> ts;
bool top_sort() {
    int start = -1;
    queue<int> q;
    for (int i = 0; i < cv; ++i) {
        if (!nil[i] && deg[i] == 0) {
            q.push(i);
            ts.push_back(i);
            start = i;
            break;
        }
    }
    if (start == -1)
        return false;
    else {
        for (int i = 0; i < cv; ++i) {
            if (start != i && deg[i] == 0) {
                q.push(i);
                ts.push_back(i);
            }
        }
 
        int v;
        while (!q.empty()) {
            v = q.front();
            q.pop();
            for (auto it = g[v].begin(); it != g[v].end(); ++it) {
                if (!(--deg[*it])) {
                    q.push(*it);
                    ts.push_back(*it);
                }
            }
        }
    }
 
    for (int i = 0; i < cv; ++i) {
        if (deg[i] > 0) {
            return false;
        }
    }
#ifdef __NR__
    if (ts.size() < cv) {
        cout << "ts.size() < cv" << endl;
    }
#endif
    return true;
}
 
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
 
    cin >> n;
    string str;
    for (int i = 0; i < n; ++i) {
        cin >> str; len_word[i] = str.size();
        word[i] = rest[max_len - str.size()] + str;
        if (str.size() > 1)
            nil[size_t(str[0] - 'a')] = true;
    }
 
    for (int i = 1; i < n; ++i) {
        if (word[i] == word[i-1] || len_word[i-1] > len_word[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }
 
    char last_ch, cur_ch;
    for (int i = 0; i < max_len; ++i) {
        last_ch = '#';
        for(int j = 0; j < n; ++j) {
            cur_ch =  word[j][i];
            if (beg[j]) {
                last_ch = cur_ch;
                continue;
            } else {
                if (cur_ch != last_ch) {
                    if (last_ch != '#')
                        add_adge(last_ch, cur_ch);
                    swap(cur_ch, last_ch);
                    beg[j] = true;
                }
            }
        }
    }
 
#ifdef __NR__
    for (int i = 0; i < cv; ++i) {
        for (auto it = g[i].begin(); it != g[i].end(); ++it) {
            cout << char(i + 'a') << " -> " << char(*it + 'a') << endl;
        }
    }
#endif
    if (top_sort()) {
        cout << "YES" << endl;
        int res[cv];
        for (int i = 0; i < cv; ++i) {
            res[ts[i]] = i;
        }
        for (int i = 0; i < cv; ++i) {
            cout << res[i] << " ";
        }
        cout << endl;
    } else cout << "NO" << endl;
 
    return 0;
}