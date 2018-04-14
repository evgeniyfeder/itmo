#include <iostream>
#include <vector>
#include <stack>
#include <conio.h>

int modul = 1000000000;
/* Decart tree data structure */
class treap {
private:
	/* One node implementation */
	struct node {
		int data;
		int child_count, sum, priority;
		node *left, *right;

		/* Class contructor */
		node(int data, int child_count = 0, int sum = 0, int priority = rand(),
			node *left = nullptr, node *right = nullptr) :
				data(data), child_count(child_count), sum(sum), priority(priority),
				left(left), right(right) {
		} /* End of 'node' constructor */

		/* Set empry sons */
		void set_empty_son() {
			left = nullptr;
			right = nullptr;
		} /* End of 'set_empty_son' function */

		/* Class destructor */
		~node() { delete left; delete right; }
	} *root; /* End of 'node' function */
	
	/* Helpful functions for tree */
	int get_child_count(node *treap) { return treap != nullptr ? treap->child_count : 0; }

	/* Helpful functions for tree */
	int get_sum(node *treap) { return treap != nullptr ? treap->sum : 0; }

	/* Update children count */
	void update_params(node *treap) {
		treap->child_count = get_child_count(treap->left) + get_child_count(treap->right) + 1;
		treap->sum = ((get_sum(treap->left) + get_sum(treap->right)) % modul + treap->data) % modul;
	} /* End of 'update_child' function */
	
	/* Recursive child update */
	void update_child_rec(node *treap) {
		if (treap->left != nullptr)
			update_child_rec(treap->left), treap->child_count += treap->left->child_count;
		if (treap->right != nullptr)
			update_child_rec(treap->right), treap->child_count += treap->right->child_count;
		treap->child_count++;
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

		update_params(cur_node);
	} /* End of 'split' function */

	/* Merge two tree function */
	node *merge(node *left, node *right) {
		if (left == nullptr)
			return right;
		else if (right == nullptr)
			return left;
		else if (left->priority > right->priority) {
			left->right = merge(left->right, right);
			update_params(left);
			return left;
		}
		else {
			right->left = merge(left, right->left);
			update_params(right);
			return right;
		}
	} /* End of 'merge' function */
	
    /* Add element to tree function */
	node *search_rec(node *cur_node, int x, int &ind, bool &isExist) {
		if (x < cur_node->data) {
			if (cur_node->left != nullptr)
				return search_rec(cur_node->left, x, ind, isExist);
			else
				return cur_node;
		}
		else if (x == cur_node->data) {
			ind += get_child_count(cur_node->left) + 1;
			isExist = true;
			return cur_node;
		}
		else {
			ind += get_child_count(cur_node->left) + 1;
			if (cur_node->right != nullptr)
				return search_rec(cur_node->right, x, ind, isExist);
			else
				return cur_node;
		}
	} /* End of 'push' function */

	/* Recursive delete function */
	node *delete_rec(node *cur_node, int x) {
		if (cur_node == nullptr)
			return cur_node;

		if (cur_node->data == x) {
			node *left = cur_node->left, *right = cur_node->right;
			cur_node->set_empty_son();
			delete cur_node;
			return merge(left, right);
		}
		else if (cur_node->data < x)
			cur_node->right = delete_rec(cur_node->right, x);
		else 
			cur_node->left = delete_rec(cur_node->left, x);
		update_params(cur_node);
		return cur_node;
	} /* End of 'delete_rec' function */

	/* Recursive Search k-th minimum function */
	int kth_min_rec(node *cur_node, int k) {
		if (cur_node == nullptr)
			return 0;

		int child_count = get_child_count(cur_node->left) + 1;
		if (child_count == k)
			return cur_node->data;
		else if (child_count > k)
			return kth_min_rec(cur_node->left, k);
		else 
			return kth_min_rec(cur_node->right, k - child_count);
	} /* End of 'kth_min_rec' function */
	
	/* Print tree function */
	void print_rec(node *cur_node) {
		if (cur_node == nullptr)
			return;

		print_rec(cur_node->left);
		std::cout << cur_node->data << " ";
		print_rec(cur_node->right);
	} /* End of 'print_rec' function */	
public:
	/* Default constructor */
	treap(void) : root(nullptr) {}

	/* Class constructor */
	treap(std::vector<int> const &array_to_create) : root(nullptr) {
		if (array_to_create.size() == 0)
			return;

		/* fill elements */
		node *prev = new node(array_to_create[0], 0, array_to_create[0]);
		root = prev;

		std::stack<node *> stack;
		stack.push(prev);
		for (size_t i = 1; i < array_to_create.size(); i++) {
			node *cur = new node(array_to_create[i], 0, array_to_create[i]);
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
		update_child_rec(root);
	} /* End of 'treap' constructor */

	/* Class destructor */
	~treap() {
		delete root; 
	}

	/* Move segment to the begin */
	treap &move_segment(int begin, int end) {
		node *less = nullptr, *between = nullptr, *more = nullptr;
		
		split(root, &less, &between, begin, 0);
		split(between, &between, &more, end - begin + 1, 0);

		less = merge(between, less);
		root = merge(less, more);
		return *this;
	} /* End of 'move_secgemnt' function */

	/* Get sum for segment */
	int get_sum(int left_round, int right_round) {
		if (root == nullptr)
			return 0;

		node *less = nullptr, *between = nullptr, *more = nullptr;
		int left = 0, right = 0;
		bool isExist = false;

		search_rec(root, right_round, right, isExist);

		isExist = false;
		search_rec(root, left_round, left, isExist);

		split(root, &less, &between, isExist ? left - 1 : left, 0);
		split(between, &between, &more, isExist ? right - left + 1 : right - left, 0);

		int res_sum = get_sum(between);
		less = merge(less, between);
		root = merge(less, more);

		return res_sum;
	} /* End of 'get_sum' function */

	/* Push element to array */
	treap &push(int x) {
		if (root == nullptr) {
			root = new node(x, 1, x);
			return *this;
		}

		int elem_ind = 0;
		bool isExist;
		node *parent = search_rec(root, x, elem_ind, isExist);
		if (parent->data == x)
			return *this;

		node *more;
		split(root, &root, &more, elem_ind, 0);
		root = merge(root, new node(x, 1, x));
		root = merge(root, more);
		return *this;
	} /* End of 'push' function */

	/* Delete element from array function */
	treap &remove(int x) {
		if (root == nullptr)
			return *this;

		root = delete_rec(root, x);
		return *this;
	} /* End of 'remove' function */

	/* Search k-th minimum function */
	int kth_min(int k) {
		if (root == nullptr || k > size() || k <= 0)
			return -1;
		
		return kth_min_rec(root, k);
	} /* End of 'kth_min' function */

	/* Search k-th maximum function */
	int kth_max(int k) {
		if (root == nullptr || k > size() || k <= 0)
			return -1;

		return kth_min_rec(root, size() - k + 1);
	} /* End of 'kth_min' function */

	/* Get size of tree function */
	int size() { 
		return get_child_count(root);
	} /* End of 'size' function */
	/* Print tree function */
	void print() {
		print_rec(root);
		std::cout << std::endl;
	} /* End of 'print' function */
}; /* End of 'treap' class */

/* The main function of programme */
int main(void) {
	int n;

	std::cin >> n;

	treap t;
	bool isLastQuest = false;
	int last_sum = 0;
	for (int i = 0; i < n; i++) {
		char key = 0;
		std::cin >> key;

		if (key == '+') {
			int num;
			std::cin >> num;
			if (isLastQuest)
				t.push((num + last_sum) % modul);
			else
				t.push(num);
			isLastQuest = false;
		}
		else if (key == '?') {
			int left, right = 0;
			std::cin >> left >> right;
			std::cout << (last_sum = t.get_sum(left, right)) << std::endl;
			isLastQuest = true;
		}
		else if (key == '-')
			t.print();
	}
/*#ifdef _DEBUG
	getch();
#endif*/
} /* End of 'main' function */