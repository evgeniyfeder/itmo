#define Re
#if defined Re
    #include<iostream>
#else
    #include<fstream>
#endif
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
 
#define endl "\n"
 
using namespace std;
 
#if !defined Re
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#endif
 
const int max_n = 100005, inf = int(2e9);
 
vector<int> to[max_n];
int s[max_n], p[max_n], ind_st[max_n], leader[max_n], n;
int promise_sum[max_n * 4], st_sum[max_n * 4], d[max_n];
 
void attache_tree(int root, int parent_root);
int dfs_for_calc_s(int v);
void dfs_for_build_lhd(int v, int lrd);
int get_ind(int v, int l, int r, int ind);
void addlr(int v, int l, int r, int L, int R, int val);
inline void push(int v, int ls, int rs);
inline void get_val(int v);
void build_LHD() {
    p[0] = 0;
    d[0] = 0;
    attache_tree(0, 0);
    dfs_for_calc_s(0);
    dfs_for_build_lhd(0, 0);
}
 
inline int find(int v) {
    return get_ind(0, 0, n, ind_st[v]);
}
 
void add_LHD(int v, int u, int val);
 
int cnt[max_n];
int main() {
    cin >> n;
    for (int i = 0, v, u; i < n-1; ++i) {
        cin >> u >> v;
        --v; --u;
        to[v].push_back(u);
        to[u].push_back(v);
    }
    build_LHD();
    int m; cin >> m;
    for(int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        --a; --b;
        add_LHD(a, b, 1);
    }
    int res = 0;
    for (int i = 1; i < n; ++i) {
        if (find(i) == 0)
            res++;
    }
    cout << res << endl;
    return 0;
}
 
void attache_tree(int root, int parent_root) {
    for(int i = 0, mem_to; i < (int)to[root].size(); ++i) {
        mem_to = to[root][i];
        if (mem_to != parent_root) {
            p[mem_to] = root;
            d[mem_to] = d[root] +1;
            attache_tree(mem_to, root);
        }
    }
    return;
}
 
int dfs_for_calc_s(int v) {
    int size = 0;
    for (int i = 0; i < (int)to[v].size(); ++i ) {
        if (p[v] != to[v][i]) {
            size += dfs_for_calc_s(to[v][i]);
        }
    }
    return s[v] = (size == 0? 1: size + 1);
}
 
void dfs_for_build_lhd(int v, int ldr) {
    static int time = -1;
    time++;
    ind_st[v] = time;
    leader[v] = ldr;
    int ind_heavy = inf, size = 0;
    for (int i = 0, mem_to; i < (int)to[v].size(); i++) {
        mem_to = to[v][i];
        if (p[v] != mem_to)
            if (size < s[mem_to]) {
                ind_heavy = mem_to;
                size = s[mem_to];
            }
    }
    if (ind_heavy  != inf)
        dfs_for_build_lhd(ind_heavy, ldr);
    for (int i = 0, mem_to; i < (int)to[v].size(); i++) {
        mem_to = to[v][i];
        if (mem_to != p[v] && mem_to != ind_heavy) {
            dfs_for_build_lhd(mem_to, mem_to);
        }
    }
}
 
int get(int v) {
    return promise_sum[v] + st_sum[v];
}
 
void push(int v, int ls, int rs) {
    if(promise_sum[v] != 0) {
        promise_sum[ls] += promise_sum[v];
        promise_sum[rs] += promise_sum[v];
        promise_sum[v] = 0;
        st_sum[v] = get(ls) + get(rs);
    }
}
 
int get_ind(int v, int l, int r, int ind) {
    if (r - l == 1)  {
        return get(v);
    } else {
        int m = (l + r) /2, ls = v * 2 +1, rs = ls + 1;
        push(v, ls, rs);
        if (ind < m) {
            return get_ind(ls, l, m, ind);
        } else {
            return get_ind(rs, m, r, ind);
        }
    }
}
 
void addlr(int v, int l, int r, int L, int R, int val) {
    if (r == R && l == L) {
        promise_sum[v] += val;
    } else {
        int m = (l + r) /2, ls = v * 2 + 1, rs = ls + 1;
        push(v, ls, rs);
        if (L < m) {
            addlr(ls, l, m, L, min(R, m), val);
        }
        if (R > m) {
            addlr(rs, m, r, max(m, L), R, val);
        }
        st_sum[v] = get(ls) + get(rs);
    }
    return;
}
 
void add_LHD(int v, int u, int val) {
    while(true) {
        if (leader[v] == leader[u]) {
            if (d[v] > d[u]) swap(v, u); //assert d[v] < d[v] => h[v] > h[u]
            if ( ind_st[v] != ind_st[u])
                addlr(0, 0, n, ind_st[v] + 1, ind_st[u] + 1, val); // (u, v]
            break;
        }
        if (d[leader[v]] < d[leader[u]]) swap(v, u);
        addlr(0, 0, n, ind_st[leader[v]], ind_st[v] + 1, val);
        v = leader[v];
        v = p[v];
    }
}