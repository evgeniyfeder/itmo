#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

std::string file_name = "minimization";

std::vector<std::vector<int>> dka;
std::vector<std::vector<std::vector<int>>> dka_reverse;
std::vector<bool> is_term;

std::vector<bool> reacheble;
void build_reacheble() {
    reacheble.resize(dka.size());

    std::queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int ind = q.front();
        q.pop();

        if (reacheble[ind])
            continue;
        reacheble[ind] = true;
        for (char c = 0; c < 26; c++) {
            if (dka[ind][c] != 0)
                q.push(dka[ind][c]);
        }
    }
}

void get_dka() {
    size_t n, m, k;

    std::cin >> n >> m >> k;

    is_term.resize(n + 1);
    for (int i = 0; i < k; i++) {
        int a;
        std::cin >> a;
        is_term[a] = true;
    }

    dka.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        dka[i].resize(26);
        for (int j = 0; j < 26; j++) {
            dka[i][j] = 0;
        }
    }

    //build_reacheble();
    //reacheble[0] = true;
    /* delete unreacheble verteces */
    /*std::vector<int> unreach;
    for (int i = 0; i < dka.size(); i++) {
        if (!reacheble[i])
            unreach.push_back(i);
    }
    for (int i = 0; i < dka.size(); i++)
        for (char c = 0; c < 26; c++) {
            for (auto unr = unreach.begin(); unr != unreach.end(); unr++) {
                if (dka[i][c] == *unr)
                    dka[i][c] = 0;
            }
        }*/
    //reacheble[0] = false;
    /* build reverse */
    dka_reverse.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        dka_reverse[i].resize(26);
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        char sym;
        std::cin >> from >> to >> sym;
        dka[from][sym - 'a'] = to;
        dka_reverse[to][sym - 'a'].push_back(from);
    }

    for (int i = 0; i < dka.size(); i++) {
        for (char c = 0; c < 26; c++) {
            if (dka[i][c] == 0)
                dka_reverse[0][c].push_back(i);
        }
    }
}

std::vector<std::vector<bool>> equviv_table;
void create_equviv_table() {
    equviv_table.resize(dka.size());
    for (int i = 0; i < dka.size(); i++) {
        equviv_table[i].resize(dka.size());
    }

    typedef std::pair<int, int> pair;
    std::queue<pair> q;

    for (int i = 0; i < equviv_table.size(); i++) {
        for (int j = 0; j < equviv_table.size(); j++) {
            if (!equviv_table[i][j] && is_term[i] != is_term[j]) {
                equviv_table[i][j] = true;
                equviv_table[j][i] = true;
                q.push(pair(i, j));
            }
        }
    }

    while (!q.empty()) {
        pair p = q.front();
        q.pop();

        int u = p.first, v = p.second;
        for (char c = 0; c < 26; c++) {
            for (auto prev_u = dka_reverse[u][c].begin(); prev_u != dka_reverse[u][c].end(); ++prev_u) {
                for (auto prev_v = dka_reverse[v][c].begin(); prev_v != dka_reverse[v][c].end(); ++prev_v) {
                    if (!equviv_table[*prev_u][*prev_v]) {
                        equviv_table[*prev_u][*prev_v] = true;
                        equviv_table[*prev_v][*prev_u] = true;
                        q.push(pair(*prev_u, *prev_v));
                    }
                }
            }
        }
    }
}

std::vector<std::vector<int>> dka_min;
std::vector<bool> is_term_min;
int num_term;
int build_min_dka_by_components(const std::vector<int> &components, int n) {
    dka_min.resize(n);
    for (int i = 0; i < n; i++) {
        dka_min[i].resize(26);
        for (int j = 0; j < 26; j++) {
            dka_min[i][j] = -1;
        }
    }
    is_term_min.resize(n);
    int num_edges = 0;
    for (int i = 1; i < components.size(); i++) {
        for (char c = 0; c < 26; c++) {
            if (dka[i][c] != 0 && components[i] > 0 && dka_min[components[i] - 1][c] == -1) {
                dka_min[components[i] - 1][c] = components[dka[i][c]] - 1;
                num_edges++;
            }
        }
        if (components[i] > 0 && is_term[i] && !is_term_min[components[i] - 1]) {
            is_term_min[components[i] - 1] = true;
            num_term++;
        }
    }
    return num_edges;
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
    get_dka();
    build_reacheble();
    // reacheble[0] = true;
    create_equviv_table();

    std::vector<int> components(dka.size());
    for (int i = 0; i < dka.size(); i++) {
        if (!equviv_table[0][i])
            components[i] = 0;
        else
            components[i] = -1;
    }

    int num_components = 0;
    for (int i = 1; i < dka.size(); i++) {
        if (!reacheble[i])
            continue;
        if (components[i] == -1) {
            num_components++;
            components[i] = num_components;
            for (int j = i + 1; j < dka.size(); j++) {
                if (!equviv_table[i][j])
                    components[j] = num_components;
            }
        }
    }

    int num_edges = build_min_dka_by_components(components, num_components);

    std::cout << num_components << " " << num_edges << " " << num_term << std::endl;
    for (int i = 0; i < is_term_min.size(); i++)
        if (is_term_min[i])
            std::cout << i + 1 << " ";
    std::cout << "\n";

    for (int i = 0; i < dka_min.size(); i++) {
        for (char c = 0; c < 26; c++) {
            if (dka_min[i][c] != -1) {
                std::cout << i + 1 << " " <<  dka_min[i][c] + 1 << " " << char(c + 'a') << std::endl;
            }
        }
    }

    return 0;
}