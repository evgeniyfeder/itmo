#ifndef HW3_CALLABLE_FUNCTION_H
#define HW3_CALLABLE_FUNCTION_H
#include <memory>
#include <sys/mman.h>
#include <cstring>

typedef unsigned char byte;

///////////
typedef int (*func_type)(int);
///////////

class callable_function {
private:
    void *data;
    size_t size;
    int cur_prot;

    void change_prot(int new_prot);
public:
    callable_function(byte *code, size_t size);
    ~callable_function();

    void change_byte(byte new_byte, size_t byte_pos);
    int execute(int a);
};
#endif //HW3_CALLABLE_FUNCTION_H
