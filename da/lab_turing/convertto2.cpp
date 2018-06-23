#include <string>
#include <iostream>

std::string file_name = "convertto2";

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
		<< "s 1 -> s1 1 <\n"
		<< "s 2 -> s1 2 <\n"
		<< "s 0 -> s1 0 <\n"
		<< "s1 _ -> s2 = <\n"
		<< "s2 _ -> go_end 0 >\n"
		<< "go_end 0 -> go_end 0 >\n"
		<< "go_end 1 -> go_end 1 >\n"
		<< "go_end 2 -> go_end 2 >\n"
		<< "go_end = -> go_end = >\n"
		<< "go_end _ -> minus_one _ <\n"
		<< "minus_one 0 -> minus_one 2 <\n"
		<< "minus_one 1 -> go_to_eq 0 <\n"
		<< "minus_one 2 -> go_to_eq 1 <\n"
		<< "minus_one = -> go_end_finish = >\n"
		<< "go_to_eq 0 -> go_to_eq 0 <\n"
		<< "go_to_eq 1 -> go_to_eq 1 <\n"
		<< "go_to_eq 2 -> go_to_eq 2 <\n"
		<< "go_to_eq = -> plus_one = <\n"
		<< "plus_one 0 -> go_end 1 >\n"
		<< "plus_one 1 -> plus_one 0 <\n"
		<< "plus_one _ -> go_end 1 >\n"
		<< "go_end_finish 2 -> go_end_finish 2 >\n"
		<< "go_end_finish _ -> go_begin _ <\n"
		<< "go_begin 0 -> go_begin 0 <\n"
		<< "go_begin 1 -> go_begin 1 <\n"
		<< "go_begin 2 -> go_begin _ <\n"
		<< "go_begin = -> go_begin _ <\n"
		<< "go_begin _ -> ac _ >\n"
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
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"
		<< "\n"*/;
}
