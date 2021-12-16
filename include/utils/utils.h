#ifndef BROKERAPP_UTILS_H
#define BROKERAPP_UTILS_H

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <unordered_map>
#include <cxxabi.h>

#include "date.h"
#include "list.hpp"

typedef unsigned long inv_id_t;

inv_id_t iota();

std::string demangle(const char* name);

#endif // BROKERAPP_UTILS_H
