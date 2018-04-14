#define _CRT_SECURE_NO_WARNINGS	
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <conio.h>
#include <algorithm>

long long modul = 1000000000;
/* Decart tree data structure */
class treap {
private:
	/* One node implementation */
	struct node {
		long long data, key, priority;
		long long sum;
		node *left, *right;

		/* Class contructor */
		node(long long data, long long key, long long priority = rand(),
			node *left = nullptr, node *right = nullptr) :
			data(data), key(key), priority(priority), sum((long long)data),
			left(left), right(right) {
		} /* End of 'node' constructor */

		  /* Class destructor */
		~node() { delete left; delete right; }
	} *root; /* End of 'node' function */

	/* Helpful functions for tree */
	long long get_key(node *treap) { return treap != nullptr ? treap->key : 0; }

	/* Get sum of node */
	long long get_sum(node *treap) { return treap != nullptr ? treap->sum : 0; }

	/* Helpful functions for tree */
	long long get_priority(node *treap) { return treap != nullptr ? treap->priority : 0; }

	/* Update params function */
	void update_param(node *cur_node) {
		cur_node->sum = get_sum(cur_node->left) + get_sum(cur_node->right) + cur_node->data;
	} /* End of 'update_param' function */

	/* Split from treap nodes which key <= k */
	void split(node *cur_node, node **res_left, node **res_right, long long k) {
		if (cur_node == nullptr)
			return void(*res_left = *res_right = nullptr);
		else if (cur_node->key > k)
			split(cur_node->left, &(*res_left), &(cur_node->left), k), *res_right = cur_node;
		else
			split(cur_node->right, &(cur_node->right), &(*res_right), k), *res_left = cur_node;

		update_param(cur_node);
	} /* End of 'split' function */

	  /* Merge two tree function */
	node *merge(node *left, node *right) {
		if (left == nullptr)
			return right;
		else if (right == nullptr)
			return left;
		else if (left->priority > right->priority) {
			left->right = merge(left->right, right);
			update_param(left);
			return left;
		}
		else {
			right->left = merge(left, right->left);
			update_param(right);
			return right;
		}
	} /* End of 'merge' function */

	long long get_data(node *cur_node) {
		return cur_node != nullptr ? cur_node->data : 0;
	}

public:
	/* Class constructor */
	treap() : root(nullptr) {
	}

	/* Class destructor */
	~treap() { delete root; }

	/* Add element to set function */
	treap &push(long long data, long long key) {
		node *left, *cur, *more;
		split(root, &left, &cur, key - 1);
		split(cur, &cur, &more, key);

		if (cur != nullptr)
			return *this;
		
		root = merge(left, new node(data, key));
		root = merge(root, more);
		return *this;
	} /* End of 'push' function */

	/* Get summary of the segment */
	long long get_sum(long long left, long long right) {
		node *less, *between, *more;
		split(root, &less, &between, left - 1);
		split(between, &between, &more, right);

		long long res = get_sum(between);
		less = merge(less, between);
		root = merge(less, more);

		return res;
	} /* End of 'get_sum' fynction */
}; /* End of 'treap' class */

/* The main function of programme */
int main(void) {
	std::ios::sync_with_stdio(false);

	long long n;
	treap t;
	std::cin >> n;

	bool isLastQuest = false;
	long long last_sum = 0;
	for (long long i = 0; i < n; i++) {
		char key = 0;
		std::cin >> key;

		if (key == '+') {
			long long num;
			std::cin >> num; 

			if (isLastQuest)
				t.push(((num + last_sum) % modul), ((num + last_sum % modul) % modul));
			else
				t.push(num, num);
			isLastQuest = false;
		}
		else if (key == '?') {
			long long left, right = 0;
			std::cin >> left >> right;
			std::cout << (last_sum = t.get_sum(left, right)) << std::endl;
			isLastQuest = true;
		}
	}

	/*#ifdef _DEBUG
	getch();
	#endif*/
	} /* End of 'main' function */