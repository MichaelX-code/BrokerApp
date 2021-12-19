#include "utils.h"

inv_id_t
iota()
{
    static inv_id_t _count = 1;
    return _count++;
}