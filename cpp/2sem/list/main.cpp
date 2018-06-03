#include "list.h"
#include <cstdlib>
#include <iostream>
#include <string>

int main(void) {
	list<int> my_list;

	for (int i = 0; i < 10; i++)
		my_list.push_back(i);
	list<int>::const_iterator i(my_list.begin());
	list<int> l1, l2 = my_list;

	for (auto i = l2.begin(); i != l2.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;

	l1 = my_list;

	l1.splice(++++++++l1.begin(), l2, ++++++l2.begin(), ------l2.end());

	for (auto i = l1.begin(); i != l1.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;

	while (true)
	{
		std::string s;
		std::cin >> s;
		if (s == "push_back") {
			int x;
			std::cin >> x;
			my_list.push_back(x);
		}
		else if (s == "push_front") {
			int x;
			std::cin >> x;
			my_list.push_front(x);
		}
		else if (s == "pop_back") {
			my_list.pop_back();
		}
		else if (s == "pop_front") {
			my_list.pop_front();
		}
		else if (s == "print") {
			for (auto i = my_list.begin(); i != my_list.end(); ++i)
				std::cout << *i << " ";
			std::cout << std::endl;
		}
		else if (s == "insert") {
			int x, y;
			std::cin >> x >> y;

			list<int>::iterator it = my_list.begin();
			for (; it != my_list.end(); ++it)
				if (*it == x)
					break;

			auto res = my_list.insert(it, y);
			for (; res != my_list.end(); ++res)
				std::cout << *(res) << " ";
			std::cout << std::endl;
		}
		else if (s == "erase") {
			int x;
			std::cin >> x;

			list<int>::iterator it = my_list.begin();
			for (; it != my_list.end(); ++it)
				if (*it == x)
					break;

			auto res = my_list.erase(it);
			for (; res != my_list.end(); ++res)
				std::cout << *(res) << " ";
			std::cout << std::endl;
		}
		else if (s == "erase_segm") {
			int x, y;
			std::cin >> x >> y;

			list<int>::iterator it = my_list.begin();
			for (; it != my_list.end(); ++it)
				if (*it == x)
					break;

			list<int>::iterator it2 = my_list.begin();
			for (; it2 != my_list.end(); ++it2)
				if (*it2 == y)
					break;

			auto res = my_list.erase(it, it2);
			for (; res != my_list.end(); ++res)
				std::cout << *(res) << " ";
			std::cout << std::endl;
		}
		else if (s == "reverse") {
			for (auto i = my_list.rbegin(); i != my_list.rend(); ++i)
				std::cout << *i << " ";
			std::cout << std::endl;
		}
		else if (s == "exit")
			break;
	}
	return 0;
}
