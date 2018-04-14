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
string file = "avia";
ifstream cin(file + ".in");
ofstream cout(file + ".out");
#endif
 
const int max_n = 1000, inf = int(2e9);
 
int n, m;
int weight[max_n][max_n];
 
vector<pair<int, int>> vec_edge; // <a, b> = a -> b
bool comp_vec_edge(pair<int, int> const& a, pair<int, int> const& b) {
    return weight[a.first][a.second] < weight[b.first][b.second];
}
 
vector<int> g[max_n], tg[max_n];
bool used[max_n];
 
void clear();
 
bool check(int x);
 
void dfs(int v, vector<int> (&g)[max_n]);
 
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> n; m = n * (n - 1);
    for (int i = 0, buf; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> buf;
            if (i != j) {
                weight[i][j] = buf;
                vec_edge.push_back(make_pair(i, j));
            }
        }
    }
 
    sort(vec_edge.begin(), vec_edge.end(), comp_vec_edge);
 
    // bin search (l, r]
    int l = -1, r = m, middle;
    while (r - l > 1) {
        middle = (r + l) / 2;
        if (check(middle)) {
            r = middle;
        } else {
            l = middle;
        }
    }
#ifdef __NR__
    cout << r << endl; // answer
#endif
    int res = 0;
    for (int i = 0; i < r; ++i) {
        res = max(res, weight[vec_edge[i].first][vec_edge[i].second]);
    }
    cout << res << endl;
    return 0;
}
 
//////////////////////////////////////////////////////
void clear() {
    memset(used, 0, sizeof(used));
    for (int i = 0; i < n; ++i) {
        g[i].clear();
        tg[i].clear();
    }
    return;
}
 
bool check(int x) {
    for (int i = 0; i < x; ++i) {
        g[vec_edge[i].first].push_back(vec_edge[i].second);
        tg[vec_edge[i].second].push_back(vec_edge[i].first);
    }
    dfs(0, g);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            clear();
            return false;
        }
    }
    memset(used, 0, sizeof(used));
    dfs(0, tg);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            clear();
            return false;
        }
    }
    clear();
    return true;
}
 
void dfs(int v, vector<int> (&g)[max_n]) {
    used[v] = true;
    for (auto it = g[v].begin(); it != g[v].end(); ++it) {
        if (!used[*it]) {
            dfs(*it, g);
        }
    }
    return;
}