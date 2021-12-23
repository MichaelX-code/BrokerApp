#ifndef BROKERAPP_UTILS_H
#define BROKERAPP_UTILS_H

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>
#include <numeric>
#include <stdio.h>
#include <memory>

#ifdef _WIN32
#   include <Windows.h>
#else
#   include <sys/ioctl.h>
#   include <unistd.h>
#endif

#include "date.h"
#include "list.hpp"
#include "csv_parser.h"
    
#define DECIMAL 10

typedef unsigned long inv_id_t;
typedef long double   rubles;
typedef std::pair<int, int> pos_t;

enum class game_status {
    PLAYING,
    ENDED,
};

void fix_term_encoding();

inv_id_t iota();

void clear_terminal();

std::string table_header();

void set_cursor_pos(int x, int y);

std::pair<int, int> get_term_size();

std::vector<std::string> parse_into_words(std::string s);

void set_tem_color_red();
void set_tem_color_green();
void set_tem_color_default();

std::string get_table_header();
std::string get_table_divider();

// Templates:

template <typename T>
bool
parse(const std::string& str, T& value)
{
    std::istringstream parser(str);
    parser >> value;

    return (!parser.fail() && parser.eof());
}


#endif // BROKERAPP_UTILS_H