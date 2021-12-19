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
#include <stdio.h>

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#include "date.h"
#include "list.hpp"
#include "csv_parser.h"

typedef unsigned long inv_id_t;

inv_id_t iota();

void clear_terminal();

std::string table_header();

void set_cursor_pos(int x, int y);

std::pair<int, int> get_term_size();

#endif // BROKERAPP_UTILS_H