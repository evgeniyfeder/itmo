#include <string>
#include <iostream>

std::string file_name = "less";

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
		<< "s 0 -> check_length 0 ^\n"
		<< "s 1 -> check_length 1 ^\n"

		<< "check_length 0 -> length_right 4 >\n"
		<< "check_length 1 -> length_right 5 >\n"
		<< "check_length < -> length_right_end < >\n"

		<< "length_right 0 -> length_right 0 >\n"
		<< "length_right 1 -> length_right 1 >\n"
		<< "length_right < -> length_right_after < >\n"
		
		<< "length_right_after 0 -> length_left_after 2 < \n"
		<< "length_right_after 1 -> length_left_after 3 < \n"
		<< "length_right_after 2 -> length_right_after 2 > \n"
		<< "length_right_after 3 -> length_right_after 3 > \n"
		<< "length_right_after _ -> rj _ ^\n"

		<< "length_left_after 2 -> length_left_after 2 < \n"
		<< "length_left_after 3 -> length_left_after 3 < \n"
		<< "length_left_after < -> length_left < <\n"

		<< "length_left 0 -> length_left 0 <\n"
		<< "length_left 1 -> length_left 1 <\n"
		<< "length_left 4 -> check_length 4 >\n"
		<< "length_left 5 -> check_length 5 >\n"

		<< "length_right_end 2 -> length_right_end 2 >\n"
		<< "length_right_end 3 -> length_right_end 3 >\n"
		<< "length_right_end 1 -> ac _ ^\n"
		<< "length_right_end 0 -> ac _ ^\n"
		<< "length_right_end _ -> go_begin _ <\n"


		<< "go_begin 4 -> go_begin 0 <\n"
		<< "go_begin 5 -> go_begin 1 <\n"
		<< "go_begin 2 -> go_begin 2 <\n"
		<< "go_begin 3 -> go_begin 3 <\n"
		<< "go_begin < -> go_begin < <\n"
		<< "go_begin _ -> next_compare _ >\n"
	
		<< "next_compare 1 -> compare_1 * >\n"
		<< "next_compare 0 -> compare_0 * >\n"
		<< "next_compare < -> rj _ ^\n"

		<< "compare_1 1 -> compare_1 1 >\n"
		<< "compare_1 0 -> compare_1 0 >\n"
		<< "compare_1 < -> compare_1 < >\n"
		<< "compare_1 & -> compare_1 & >\n"
		<< "compare_1 2 -> rj _ ^\n"
		<< "compare_1 3 -> return & <\n"
		<< "compare_1 _ -> rj _ ^\n"

		<< "compare_0 1 -> compare_0 1 >\n"
		<< "compare_0 0 -> compare_0 0 >\n"
		<< "compare_0 < -> compare_0 < >\n"
		<< "compare_0 & -> compare_0 & >\n"
		<< "compare_0 3 -> ac _ ^\n"
		<< "compare_0 2 -> return & <\n"
		<< "compare_0 _ -> rj _ ^\n"

		<< "return 0 -> return 0 <\n" 
		<< "return 1 -> return 1 <\n" 
		<< "return * -> next_compare * >\n"
		<< "return < -> return < <\n"
		<< "return & -> return & <\n"

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
