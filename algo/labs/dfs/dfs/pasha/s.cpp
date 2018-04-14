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
string file = "dfs";
ifstream cin(file + ".in");
ofstream cout(file + ".out");
#endif
 
const int max_n = 305, inf = int(2e9);
 
int n, m;
int g[max_n][max_n];
bool used[max_n][max_n];
int node[max_n * 3];
 
vector<int> st;
vector<int> gg[max_n];
bool usedused[max_n];
 
vector<pair<int, int>> edges;
 
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> n >> m;
    int a, b;
    cin >> a;
    node[0] = a - 1;
    for(int i = 0; i < m-1; ++i) {
        cin >> b;
        g[a - 1][b - 1]++;
        g[b - 1][a - 1]++;
        swap(a, b);
        node[i + 1] = a - 1;
    }
 
    size_t size;
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!used[j][i]) {
                size = edges.size();
                while (g[i][j] >= 2) {
                    edges.push_back(make_pair(i, j));
                    g[i][j] -= 2;
                }
                if (size < edges.size()) {
                    used[i][j] = true;
                    used[j][i] = true;
                }
            }
        }
    }
 
#ifdef __NR__
    cout << edges.size() << endl;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        cout << it->first + 1 << " " << it->second + 1 << "\n";
    }
    cout << endl;
#endif
 
    int max_ind_son[max_n];
    vector<int> st;
    node[m] = 302;
    st.push_back(node[0]);
    for (int i = 0; i < m; ++i) {
        if (used[node[i]][node[i + 1]]) {
            if (st.size() > 1 && st[st.size() - 2] == node[i + 1]) {
 
                for (auto it = st.rbegin() + 2; it != st.rend(); ++it) {
                    if (max_ind_son[*it] < node[i])
                        edges.push_back(make_pair(node[i], *it));
                }
                max_ind_son[node[i + 1]] = -1;
                st.pop_back();
 
            } else {
                st.push_back(node[i + 1]);
                max_ind_son[node[i]] = node[i + 1];
            }
        } else {
            st.clear();
            st.push_back(node[i + 1]);
        }
    }
 
    cout << edges.size() << endl;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        cout << it->first + 1 << " " << it->second + 1 << "\n";
    }
    cout << endl;
 
    return 0;
}