#include <string>
#include <iostream>

std::string file_name = "balanced";

int main() {
#ifdef _DEBUG
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	// & - used close
	// * - cur finding open
	std::cout
		<< "start: s\n"
		<< "accept: ac\n"
		<< "reject: rj\n"
		<< "blank: _\n"
		<< "s _ -> ac _ ^\n"
		<< "s ) -> rj _ ^\n"
		<< "s ( -> find_close * >\n"
		<< "s & -> s _ >\n"
		<< "find_close ( -> find_close ( >\n"
		<< "find_close ) -> go_back & <\n "
		<< "find_close & -> find_close & >\n"
		<< "go_back * -> s _ >\n"
		<< "go_back ( -> go_back ( <\n"
		<< "go_back ) -> go_back ) <\n"
		<< "go_back & -> go_back & <\n"
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
		<< "\n"*/;
}
