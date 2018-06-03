#include <iostream>
#include <cassert>
#include "callable_function.h"

callable_function::callable_function(byte *code, size_t size) : size(size), cur_prot(PROT_READ | PROT_WRITE) {
    data = mmap(nullptr, size, cur_prot, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(data != MAP_FAILED);
    memcpy(data, code, sizeof(byte) * size);
}

void callable_function::change_prot(int new_prot) {
    if (cur_prot == new_prot)
        return;
    if (mprotect(data, size, new_prot) == -1) {
        std::cerr << "Can't change prot option";
        return;
    }

    cur_prot = new_prot;
}

void callable_function::change_byte(byte new_byte, size_t byte_pos) {
    change_prot(PROT_READ | PROT_WRITE);
    ((byte *)data)[byte_pos] = new_byte;
}

int callable_function::execute(int a) {
    change_prot(PROT_READ | PROT_EXEC);
    auto f = (func_type)data;
    return f(a);
}

callable_function::~callable_function() {
    if (munmap(data, size) == -1) {
        std::cerr << "Can't free memory of code";
    }
}
