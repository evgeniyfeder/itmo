#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct Node {
    int32_t pred, left, right, parent, print_index;
};

int dfs(int32_t cur_ind, std::vector<Node> & tree, std::unordered_map<int32_t, int32_t> & cur_predicates) {
    if (tree[cur_ind].left == -1) {
        return cur_ind;
    }

    Node & node = tree[cur_ind];
    auto it = cur_predicates.find(node.pred);
    if (it != cur_predicates.end()) {
        if (it->second == 0) return dfs(node.left, tree, cur_predicates);
        else return dfs(node.right, tree, cur_predicates);
    }

    cur_predicates[node.pred] = 0;
    node.left = dfs(node.left, tree, cur_predicates);
    cur_predicates[node.pred] = 1;
    node.right = dfs(node.right, tree, cur_predicates);
    cur_predicates.erase(node.pred);
    return cur_ind;
}

int32_t count_node(int32_t cur_ind, int32_t &print_index, std::vector<Node> & tree) {
    Node &node = tree[cur_ind];
    node.print_index = print_index++;
    if (node.left == -1) return 1;
    else return 1 + count_node(node.left, print_index, tree) + count_node(node.right, print_index, tree);
}

int32_t out_tree(int32_t old_ind, std::vector<Node> const & tree) {
    Node node = tree[old_ind];
    if (node.left == -1) {
        std::cout << "leaf " << node.pred + 1 << std::endl;
    } else {
        std::cout << "choice " << node.pred + 1 << ' ' << tree[node.left].print_index + 1 << ' ' << tree[node.right].print_index + 1 << std::endl;
        out_tree(node.left, tree);
        out_tree(node.right, tree);
    }
}

int main() {
    freopen("trees.in", "r", stdin);
    freopen("trees.out", "w", stdout);

    size_t n;
    std::cin >> n;

    std::vector<Node> tree(n);
    tree[0].parent = -1;
    for(size_t i = 0; i < n; i++) {
        std::string action;
        std::cin >> action;

        if (action == "choice") {
            int32_t pred, left, right;
            std::cin >> pred >> left >> right;

            tree[i].pred = pred - 1;
            tree[i].left = left - 1;
            tree[i].right = right - 1;
            tree[left - 1].parent = static_cast<int32_t>(i);
            tree[right - 1].parent = static_cast<int32_t>(i);
        } else if (action == "leaf") {
            int32_t data;
            std::cin >> data;
            tree[i].pred = data - 1;
            tree[i].left = -1;
            tree[i].right = -1;
        }
    }

    std::unordered_map<int32_t, int32_t> predicates;
    dfs(0, tree, predicates);
    int32_t x = 0;
    std::cout << count_node(0, x, tree) << std::endl;
    out_tree(0, tree);
    return 0;
}
