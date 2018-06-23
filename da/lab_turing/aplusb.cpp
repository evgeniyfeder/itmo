#include <string>
#include <iostream>

std::string file_name = "aplusb";

int main() {
#ifdef _DEBUG
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	std::cout
		<< "start: s\n"
		<< "accept: ac\n"
		<< "reject: rj\n"
		<< "blank: _\n"
		<< "s 0 -> s 0 >\n"
		<< "s 1 -> s 1 >\n"
		<< "s + -> si + >\n"

		<< "si 0 -> si 2 >\n"
		<< "si 1 -> si 3 >\n"
		<< "si _ -> sum_next _ <\n"

		<< "sum_next 2 -> sum_0 * <\n"
		<< "sum_next 3 -> sum_1 * <\n"
		<< "sum_next + -> go_begin _ <\n"

		<< "sum_0 2 -> sum_0 2 <\n"
		<< "sum_0 3 -> sum_0 3 <\n"
		<< "sum_0 4 -> sum_0 4 <\n"
		<< "sum_0 5 -> sum_0 5 <\n"
		<< "sum_0 + -> sum_0 + <\n"
		<< "sum_0 0 -> reverse 4 >\n"
		<< "sum_0 1 -> reverse 5 >\n"
		<< "sum_0 _ -> reverse 4 >\n"

		<< "sum_1 2 -> sum_1 2 <\n"
		<< "sum_1 3 -> sum_1 3 <\n"
		<< "sum_1 4 -> sum_1 4 <\n"
		<< "sum_1 5 -> sum_1 5 <\n"
		<< "sum_1 + -> sum_1 + <\n"
		<< "sum_1 0 -> reverse 5 >\n"
		<< "sum_1 1 -> plus_1 4 <\n"
		<< "sum_1 _ -> reverse 5 >\n"

		<< "plus_1 0 -> reverse 1 >\n"
		<< "plus_1 1 -> plus_1 0 <\n"
		<< "plus_1 _ -> reverse 1 >\n"

		<< "reverse 0 -> reverse 0 >\n"
		<< "reverse 1 -> reverse 1 >\n"
		<< "reverse 2 -> reverse 2 >\n"
		<< "reverse 3 -> reverse 3 >\n"
		<< "reverse 4 -> reverse 4 >\n"
		<< "reverse 5 -> reverse 5 >\n"
		<< "reverse + -> reverse + >\n"
		<< "reverse * -> sum_next _ <\n"

		<< "go_begin 0 -> go_begin 0 <\n"
		<< "go_begin 1 -> go_begin 1 <\n"
		<< "go_begin 4 -> go_begin 0 <\n"
		<< "go_begin 5 -> go_begin 1 <\n"
		<< "go_begin _ -> ac _ >\n"

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
		<< "\n";
}
