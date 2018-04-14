#include <string>
#include <iostream>
#include <exception>

/* Unbalanced tree data class */
class binary_tree {
private:
	/* One node definition */
	struct node {
		int data;
		node *left, *right;

		/* Class constructor */
		node(int data, node *left = nullptr, node *right = nullptr) 
			: data(data), left(left), right(right)
		{} /* End of 'node' constructor */

		/* Class destructor */
		~node() {
			delete left;
			delete right;
		}
		
		/* Set nullptr ponters function */
		void set_empty_son(void) {
			left = nullptr;
			right = nullptr;
		} /* End of 'set_empty_son' function */
	} *root;

	/* Find place to insert function */
	node *search_node(node *cur_node, int x) {
		if (cur_node == nullptr || x == cur_node->data)
			return cur_node;
		else if (x < cur_node->data) {
			return search_node(cur_node->left, x);
		} else {
			return search_node(cur_node->right, x);
		}
	} /* End of 'search' function */

	node *get_minimum_node(node *cur_node) {
		if (cur_node == nullptr)
			return cur_node;

		while (cur_node->left != nullptr)
			cur_node = cur_node->left;

		return cur_node;
	} /* End of 'get_minimum_node' function */
	/* Recursive insert data function */
	node *insert_rec(node *cur_node, int x) {
		if (cur_node == nullptr)
			return new node(x);
		else if (cur_node->data < x)
			cur_node->right = insert_rec(cur_node->right, x);
		else if (cur_node->data > x)
			cur_node->left = insert_rec(cur_node->left, x);
		return cur_node;
	} /* End of 'insert_rec' function */

	/* Recursive remove function */
	node *remove_rec(node *cur_node, int x) {
		if (cur_node == nullptr)
			return nullptr;

		if (cur_node->data < x) {
			cur_node->right = remove_rec(cur_node->right, x);
		}
		else if (cur_node->data > x) {
			cur_node->left = remove_rec(cur_node->left, x);
		}
		else if (cur_node->left != nullptr && cur_node->right != nullptr) {
			cur_node->data = get_minimum_node(cur_node->right)->data;
			cur_node->right = remove_rec(cur_node->right, cur_node->data);
		}
		else if (cur_node->left != nullptr) {
			node *deleted_elem = cur_node;
			cur_node = cur_node->left;

			deleted_elem->set_empty_son();
			delete deleted_elem;
		}
		else if (cur_node->right != nullptr) {
			node *deleted_elem = cur_node;
			cur_node = cur_node->right;

			deleted_elem->set_empty_son();
			delete deleted_elem;
		}
		else {
			delete cur_node;
			cur_node = nullptr;
		}
		return cur_node;
	}
public:
	/* Standart constructor */
	binary_tree() : root(nullptr) {
	} /* End of 'binary_tree' constructor */

	/* Standart constructor */
	~binary_tree() {
		delete root;
	} /* End of '~binary_tree' function */

	/* Insert data to function */
	binary_tree & insert(int x) {
		root = insert_rec(root, x);
		return *this;
	} /* End of 'insert' function */

	/* Insert data to function */
	void remove(int x) {
		root = remove_rec(root, x);
	} /* End of 'remove' function */

	/* Get next element function */
	std::pair<bool, int> next(int x) {
		node *cur_node = root;
		int res = 0;
		bool is_find = false;

		while (cur_node != nullptr) {
			if (cur_node->data > x) {
				res = cur_node->data;
				cur_node = cur_node->left;

				if (!is_find)
					is_find = true;
			}
			else {
				cur_node = cur_node->right;
			}
		}
		return std::pair<bool, int>(is_find, res);
	} /* End of 'next' function */

	/* Get next element function */
	std::pair<bool, int> prev(int x) {
		node *cur_node = root;
		int res = 0;
		bool is_find = false;

		while (cur_node != nullptr) {
			if (cur_node->data >= x) {
				cur_node = cur_node->left;
			}
			else {
				res = cur_node->data;
				cur_node = cur_node->right;

				if (!is_find)
					is_find = true;
			}
		}
		return std::pair<bool, int>(is_find, res);
	} /* End of 'next' function */

	/* Check for element exists */
	bool exists(int x) {
		node *elem = search_node(root, x);
		if (elem != nullptr)
			return true;
		return false;
	} /* End of 'exists' function */
}; /* End of 'binary_tree' class */

/* The main function of program */
int main(void) {
	std::ios::sync_with_stdio(false);
	std::string key_word;
	binary_tree tree;
	
	while (std::cin >> key_word) {
		int num;
		std::cin >> num;

		if (key_word == "insert")
			tree.insert(num);
		else if (key_word == "delete")
			tree.remove(num);
		else if (key_word == "exists")
			std::cout << (tree.exists(num) ? "true" : "false") << std::endl;
		else if (key_word == "next") {
			std::pair<bool, int> res = tree.next(num);
			if (res.first)
				std::cout << res.second << std::endl;
			else 
				std::cout << "none\n";
		}
		else if (key_word == "prev") {
			std::pair<bool, int> res = tree.prev(num);
			if (res.first)
				std::cout << res.second << std::endl;
			else
				std::cout << "none\n";
		}
		else if (key_word == "")
			break;
		key_word.clear();
	}
	return 0;
} /* End of 'main' function */