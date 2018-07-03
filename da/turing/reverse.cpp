#include <string>
#include <iostream>

std::string file_name = "reverse";

int main() {
#ifdef _DEBUG
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	// 2 - used 0
	// 3 - used 1

	std::cout
		<< "start: s\n"
		<< "accept: ac\n"
		<< "reject: rj\n"
		<< "blank: _\n"
		<< "s _ -> back _ <\n"
		<< "s 0 -> s 0 >\n"
		<< "s 1 -> s 1 >\n"
		<< "back 0 -> set_zero 2 >\n"
		<< "back 1 -> set_one 3 > \n"
		<< "back 2 -> back 2 <\n"
		<< "back 3 -> back 3 <\n"
		<< "back 4 -> back 4 <\n"
		<< "back 5 -> back 5 <\n"

		<< "back _ -> delete _ >\n"

		<< "set_zero 4 -> set_zero 4 >\n"
		<< "set_zero 5 -> set_zero 5 >\n"
		<< "set_zero 2 -> set_zero 2 >\n"
		<< "set_zero 3 -> set_zero 3 >\n"
		<< "set_zero _ -> back 4 <\n"

		<< "set_one 4 -> set_one 4 >\n"
		<< "set_one 5 -> set_one 5 >\n"
		<< "set_one 2 -> set_one 2 >\n"
		<< "set_one 3 -> set_one 3 >\n"
		<< "set_one _ -> back 5 <\n"

		<< "delete 4 -> delete 0 >\n"
		<< "delete 5 -> delete 1 >\n"
		<< "delete 2 -> delete _ >\n"
		<< "delete 3 -> delete _ >\n"
		<< "delete _ -> reverse _ <\n"

		<< "reverse 0 -> reverse 0 <\n"
		<< "reverse 1 -> reverse 1 <\n"
		<< "reverse _ -> ac _ >\n"
		/*<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"*/;
}
