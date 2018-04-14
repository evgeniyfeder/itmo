#include <string>
#include <iostream>

std::string file_name = "";
int main(void) {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.in", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif

	return 0;
}