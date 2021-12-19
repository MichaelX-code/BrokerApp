#ifndef BROKERAPP_UTILS_CSV_PARSER_H
#define BROKERAPP_UTILS_CSV_PARSER_H

#include "utils.h"

class csv_parser_t
{
public:
    // Constructors:
    csv_parser_t(std::string file_path);

    // Destructors:
    ~csv_parser_t();

    // Functions: selectors (get)
    bool empty() const;
    std::string get_file_path() const;

    // Functions: modifiers (set)
    

    // Methods:
    std::vector<std::string> next_line();
    void blame_last_line(std::string msg = "Invalid CSV line");

private:
    // Members:
    std::string   _file_path;
    std::ifstream _fstream;
    std::string   _last_line;
};

#endif // BROKERAPP_UTILS_CSV_PARSER_H