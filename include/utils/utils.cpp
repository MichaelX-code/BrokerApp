#include "utils.h"

inv_id_t
iota()
{
    static inv_id_t _count = 1;
    return _count++;
}

std::string
demangle(const char * name)
{
    int status = -4; // arbitrary value to eliminate the compiler warning

    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status == 0 ? res.get() : name);
}
