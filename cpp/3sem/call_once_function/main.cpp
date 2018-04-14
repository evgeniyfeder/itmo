#include "call_once_function.h"
#include <iostream>
#include <conio.h>
#include <functional>
#include <crtdbg.h>

struct big
{
	int operator()(int)
	{
		return 42;
	}

	int arr[900];
};

struct small
{
	int operator()(int)
	{
		return 24;
	}
	int x;
};

struct a {
	int x, y;
};

a f() {
	return {1, 2};
}

int main() {
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	a x = f();
	using my_f = call_once_function<int(int)>;
	my_f big_f(big{});
	my_f small_f(small{});
	int n = 1;
	std::cout << call_once_function<int(int)>(big{})(5) << std::endl;
	std::cout << call_once_function<int(int)>(small{})(5) << std::endl;
	std::cout << call_once_function<int(void)>([&n]() { return n; })() << std::endl;

	big_f.swap(small_f);

	system("pause");
	return 0;
}