//#define __NR__
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <list>
 
using namespace std;
#ifdef __NR__
//ifstream cin("input.txt");
//ofstream cout("output.txt");
#else
//string file = "biconv";
//ifstream cin(file + ".in");
//ofstream cout(file + ".out");
#endif
 
const int max_n = 20000, inf = int(2e9), max_m = 200000;
 
int n, m;
vector<pair<int, int>> g[max_n]; // <v, index edge>
int up[max_n]; // for find point
int comp[max_m], depth[max_n], cnt_comp = 0;
bool used[max_n];
list<int> glist;// stack for index edge;
 
inline void paint_list(list<int> &st, int col){
    while(!st.empty()) {
        comp[st.back()] = col;
        st.pop_back();
    }
    return;
}
 
int d = 0;
void dfs(int v, int p, list<int> &list_p) {
    used[v] = true;
    depth[v] = d;
    int v_up = d;
    list<int> loc_list;
    for (auto it = g[v].begin(); it != g[v].end(); ++it) {
        if (it->first != p) {
            if (!used[it->first]) {
                ++d;
                dfs(it->first, v, loc_list);
                --d;
                v_up = min(v_up, up[it->first]);
                loc_list.push_back(it->second);
                if (up[it->first] >= d) {
                    paint_list(loc_list, cnt_comp++);
                } else {
                    list_p.splice(list_p.end(), loc_list);
                }
            } else {
                v_up = min(v_up, depth[it->first]);
                if (depth[it->first] < d) { // invert edge to up
                    list_p.push_back(it->second);
                }
            }
        }
    }
    up[v] = v_up;
    return;
}
 
int main () {
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
#ifdef __NR__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    freopen("biconv.in", "r", stdin);
    freopen("biconv.out", "w", stdout);
#endif
 
 
    scanf("%d%d", &n, &m);
    for (int i = 0, a, b; i < m; ++i) {
        scanf("%d%d", &a, &b);
        --a; --b;
        if (a != b) {
            g[a].push_back(make_pair(b, i));
            g[b].push_back(make_pair(a, i));
        }
    }
 
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            d = 0;
            dfs(i, -1, glist);
        }
    }
 
    if (!glist.empty()) {
        paint_list(glist, cnt_comp++);
    }
 
    printf("%d\n", cnt_comp);
    for (int i = 0; i < m; ++i) {
        printf("%d ", comp[i] + 1);
//        cout << comp[i] + 1 << " ";
    }
 
    return 0;
}