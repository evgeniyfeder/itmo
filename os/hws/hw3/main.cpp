#include <iostream>
#include <sstream>

#include "callable_function.h"

/////////// Changeble part
byte code[] = {
        0x55,                        //      	push   %rbp
        0x48, 0x89, 0xe5,            //        mov    %rsp,%rbp
        0x89, 0x7d, 0xfc,            //       	mov    %edi,-0x4(%rbp)
        0x8b, 0x45, 0xfc,            //       	mov    -0x4(%rbp),%eax
        0x5, 0x83, 0x00, 0x00, 0x00, //       	add    $0x82,%eax
        0x5d,                        //     	pop    %rbp
        0xc3,                        //      	retq
}; // add 131 to argument

const size_t CHANGEBLE_INDEX = 12;
size_t code_size = 17;
/////////////////

int main() {
    auto function = callable_function(code, code_size);

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);

        std::string command;
        iss >> command;

        if (command == "execute") {
            int a;
            iss >> a;

            std::cout << "Result is " << function.execute(a) << '\n';
        }
        else if (command == "change") {
            int a;
            iss >> a;
            a = (byte)a;
            function.change_byte(a, CHANGEBLE_INDEX);
            std::cout << "second argument now " << a << '\n';
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command\n";
        }
    }
    std::cout << "JIT Ended" << std::endl;
    return 0;
}