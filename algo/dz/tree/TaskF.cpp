#include <iostream>
#include <vector>
#include <stack>
#include <conio.h>
#include <algorithm>

/* Decart tree data structure */
class treap {
private:
	/* One node implementation */
	struct node {
		int data, child_count, priority, min;
		node *left, *right;

		/* Class contructor */
		node(int data, int child_count = 0, int priority = rand(),
			node *left = nullptr, node *right = nullptr) :
			data(data), child_count(child_count), priority(priority), min(data),
			left(left), right(right) {
		} /* End of 'node' constructor */

		/* Set empty sons for node */
		void set_empty_son() {
			left = nullptr;
			right = nullptr;
		} /* End of 'set_empty_son' function */

		  /* Class destructor */
		~node() { delete left; delete right; }
	} *root; /* End of 'node' function */

	/* Helpful functions for tree */
	int get_child_count(node *treap) { return treap != nullptr ? treap->child_count : 0; }
	int get_min(node *treap) { return treap != nullptr ? treap->min : INT_MAX; }

	/* Update children */
	void update_node(node *treap) {
		treap->child_count = get_child_count(treap->left) + get_child_count(treap->right) + 1;
		treap->min = std::min<int>(std::min<int>(get_min(treap->left), get_min(treap->right)), treap->data);
	} /* End of 'update_node' function */

	/* Recursive child update */
	void update_node_rec(node *treap) {
		if (treap->left != nullptr)
			update_node_rec(treap->left);
		if (treap->right != nullptr)
			update_node_rec(treap->right);
		update_node(treap);
	}

	/* Split from treap k nodes(k != 0) */
	void split(node *cur_node, node **res_left, node **res_right, int k, int add) {
		if (cur_node == nullptr)
			return void(*res_left = *res_right = nullptr);

		int elem_ind = add + get_child_count(cur_node->left);

		if (elem_ind >= k)
			split(cur_node->left, &(*res_left), &(cur_node->left), k, add), *res_right = cur_node;
		else
			split(cur_node->right, &(cur_node->right), &(*res_right), k, 1 + elem_ind), *res_left = cur_node;

		update_node(cur_node);
	} /* End of 'split' function */

	  /* Merge two tree function */
	node *merge(node *left, node *right) {
		if (left == nullptr)
			return right;
		else if (right == nullptr)
			return left;
		else if (left->priority > right->priority) {
			left->right = merge(left->right, right);
			update_node(left);
			return left;
		}
		else {
			right->left = merge(left, right->left);
			update_node(right);
			return right;
		}
	} /* End of 'merge' function */
	
	/* Recursive search to tree function */
	node *search_rec(node *cur_node, int x, int &ind) {
		if (x < cur_node->data) {
			if (cur_node->left != nullptr)
				return search_rec(cur_node->left, x, ind);
			else
				return cur_node;
		}
		else if (x == cur_node->data)
			return cur_node;
		else {
			ind += get_child_count(cur_node->left) + 1;
			if (cur_node->right != nullptr)
				return search_rec(cur_node->right, x, ind);
			else
				return cur_node;
		}
	} /* End of 'push' function */

	  /* Print tree function */
	void print_rec(node *cur_node) {
		if (cur_node == nullptr)
			return;

		print_rec(cur_node->left);
		std::cout << cur_node->data << " ";
		print_rec(cur_node->right);
	} /* End of 'print_rec' function */

	/* Search minimum element function */
	int search_min_node(node *cur_node, int ind) {
		if (cur_node == nullptr && cur_node->min != 0)
			return -1;

		if (get_min(cur_node->left) == 0)
			return search_min_node(cur_node->left, ind);
		else if (cur_node->data == 0) {
			return ind + get_child_count(cur_node->left);
		}
		else
			return search_min_node(cur_node->right, ind + get_child_count(cur_node->left) + 1);
	}

public:
	/* Class constructor */
	treap() : root(nullptr) {}

	/* Create treap from array */
	treap(const std::vector<int> &array_to_create) {
		if (array_to_create.size() == 0)
			return;

		/* fill elements */
		node *prev = new node(array_to_create[0], 0);
		root = prev;

		std::stack<node *> stack;
		stack.push(prev);
		for (size_t i = 1; i < array_to_create.size(); i++) {
			node *cur = new node(array_to_create[i], 0);
			if (cur->priority < prev->priority) {
				prev->right = cur;
			}
			else {
				while (stack.size() != 0 && stack.top()->priority < cur->priority)
					stack.pop();

				if (stack.size() == 0) {
					cur->left = root;
					root = cur;
				}
				else {
					cur->left = stack.top()->right;
					stack.top()->right = cur;
				}

			}
			stack.push(cur);
			prev = cur;
		}

		/* Update number of childrens */
		update_node_rec(root);
	} /* End of 'treap' constructor */

	/* Insert element to array function */
	treap &insert(int pos, int data) {
		node *less = nullptr;
		split(root, &less, &root, pos, 0);

		if (root->min == 0) {
			int delete_elem = search_min_node(root, 0);
			remove(delete_elem);
		}
		push_front(data);
		root = merge(less, root);
		return *this;
	} /* End of 'insert' function */

	  /* Delete element from array function */
	treap &remove(int ind) {
		if (root == nullptr)
			return *this;

		node *less, *node, *more;
		split(root, &less, &node, ind, 0);
		split(node, &node, &more, 1, 0);
		delete node;
		root = merge(less, more);
		return *this;
	} /* End of 'remove' function */

	/* Push element to array */
	treap &push_front(int x) {
		if (root == nullptr) {
			root = new node(x, 1);
			return *this;
		}

		root = merge(new node(x, 1), root);
		return *this;
	} /* End of 'push' function */

	/* Class destructor */
	~treap() { delete root; }

	/* Print tree function */
	void print() {
		print_rec(root);
		std::cout << std::endl;
	} /* End of 'print' function */

	/* Get size of tree function */
	int size() {
		return get_child_count(root);
	} /* End of 'size' function */

	/* Get data by index */
	int data(int index) {
		node *cur_node = root;
		if (root == nullptr)
			return -1;

		int add = 0, cur_ind;
		while ((cur_ind = get_child_count(cur_node->left) + add) != index) {
			if (cur_ind < index) {
				add += get_child_count(cur_node->left) + 1;
				cur_node = cur_node->right;
			}
			else if (cur_ind > index)
				cur_node = cur_node->left;
		}
		return cur_node->data;
	}
}; /* End of 'treap' class */

   /* The main function of programme */
int main(void) {
	int n, m;
	
	std::cin >> n >> m;

	std::vector<int> arr(m);
	for (int i = 0; i < m; i++)
		arr[i] = 0;

	treap t(arr);
	for (int i = 0; i < n; i++) {
		int ind;

		std::cin >> ind;
		t.insert(ind - 1, i + 1);
	}
	while (t.data(t.size() - 1) == 0)
		t.remove(t.size() - 1);

	std::cout << t.size() << std::endl;
	t.print();
	/*#ifdef _DEBUG
	getch();
	#endif*/
} /* End of 'main' function */