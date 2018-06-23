#include <string>
#include <iostream>

std::string file_name = "postfixlogic";

int main() {
#ifdef _DEBUG
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	std::cout
		<< "2\n"
		<< "S 0 _ -> S _ > 0 >\n"
		<< "S 1 _ -> S _ > 1 >\n"
		<< "S o _ -> S o ^ _ <\n"
		<< "S a _ -> S a ^ _ <\n"

		<< "S o 0 -> or_0 o ^ _ <\n"
		<< "S o 1 -> or_1 o ^ _ <\n"

		<< "or_0 o 0 -> S _ > 0 >\n"
		<< "or_0 o 1 -> S _ > 1 >\n"
		<< "or_1 o 0 -> S _ > 1 >\n"
		<< "or_1 o 1 -> S _ > 1 >\n"

		<< "S a 0 -> and_0 a ^ _ <\n"
		<< "S a 1 -> and_1 a ^ _ <\n"

		<< "and_0 a 0 -> S _ > 0 >\n"
		<< "and_0 a 1 -> S _ > 0 >\n"
		<< "and_1 a 0 -> S _ > 0 >\n"
		<< "and_1 a 1 -> S _ > 1 >\n"

		<< "S _ _ -> S _ ^ _ <\n"
		<< "S _ _ -> S _ ^ _ <\n"
		<< "S _ 0 -> AC 0 ^ _ ^\n"
		<< "S _ 1 -> AC 1 ^ _ ^\n"
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
		<< "\n"*/;
}
