#ifndef BROKERAPP_UTILS_H
#define BROKERAPP_UTILS_H

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>

#include "date.h"
#include "list.hpp"
#include "csv_parser.h"

typedef unsigned long inv_id_t;

inv_id_t iota();

void clear_terminal();

std::string table_header();

#endif // BROKERAPP_UTILS_H