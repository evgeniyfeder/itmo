#include <string>
#include <iostream>

std::string file_name = "mirror";

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
		<< "s _ -> back _ <\n"
		<< "s 0 -> s 0 >\n"
		<< "s 1 -> s 1 >\n"
		<< "back 0 -> set_zero 2 >\n"
		<< "back 1 -> set_one 3 > \n"
		<< "back 2 -> back 0 <\n"
		<< "back 3 -> back 1 <\n"
		<< "back _ -> ac _ >\n"
		<< "set_zero 0 -> set_zero 2 >\n"
		<< "set_zero 1 -> set_zero 3 >\n"
		<< "set_zero _ -> back 0 <\n"
		<< "set_one 0 -> set_one 2 >\n"
		<< "set_one 1 -> set_one 3 >\n"
		<< "set_one _ -> back 1 <\n";
}
