#include <string>
#include <iostream>
#include <exception>

/* Two-tree tree data class */
class two_three_tree {
private:
	/* One node definition 
	 * left_data < right_data
	 * left < left_data < mid < right_data < right
	 */
	struct node {
		int left_data, right_data;
		node *left, *mid, *right, *parent;

		/* Class constructor */
		node(int left_data, int right_data = 0, node *left = nullptr, 
			node *middle = nullptr, node *right = nullptr)
			: left_data(left_data), right_data(right_data), left(left), mid(middle), right(right)
		{} /* End of 'node' constructor */

		/* Class destructor */
		~node() {
			delete left;
			delete right;
			delete mid;
		} /* End of 'node' destructor */

		/* Set nullptr ponters function */
		void set_empty_son(void) {
			left = nullptr;
			right = nullptr;
			mid = nullptr;
		} /* End of 'set_empty_son' function */
	} *root;

public:
}; /* End of 'two_three_tree' class */

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