#include <dlfcn.h>
#include <iostream>
#include "include/static.h"
#include "include/dynamic_linking.h"
#include "include/dynamic_loadable.h"

typedef int(*func_type)(int, int);

int main(void) {
	std::cout << "Input two numbers: ";
	int a, b;
	std::cin >> a >> b;

	std::cout << "Count sum:\n";
	std::cout << "Static: " << static_function(a, b) << '\n';
	std::cout << "Dynamic linked: " << dynamic_linking_function(a, b) << '\n';
	
	void *lib_ptr = dlopen("libdloadable.so", RTLD_LAZY);
	if (!lib_ptr) {
		std::cerr << dlerror() << '\n';
		return 1;
	}

	func_type sum_ptr = (func_type)dlsym(lib_ptr, "_Z25dynamic_loadable_functionii");
	if (!sum_ptr) {
		std::cerr << dlerror();
		return 1;
	}

	std::cout << "Dynamic loaded: " << sum_ptr(a, b) << '\n';
	return 0;
}
