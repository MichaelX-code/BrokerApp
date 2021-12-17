#include "csv_parser.h"

// Constructors:

csv_parser_t::csv_parser_t(std::string file_path) :
_file_path(file_path), _fstream(file_path)
{
    if (!_fstream.is_open())
        throw new std::runtime_error("ERROR: Could not open file: \"" +
                                     file_path + "\"\n");   
}

// Destructors:

csv_parser_t::~csv_parser_t()
{
    _fstream.close();
}

// Functions: selectors (get)

bool
csv_parser_t::empty()
const
{
    return this->_fstream.eof();
}

std::string
csv_parser_t::get_file_path()
const
{
    return this->_file_path;
}

// Methods:

std::vector<std::string>
csv_parser_t::next_line()
{
    std::vector<std::string> result;

    if (this->empty())
        return result;

    std::string line;
    std::getline(this->_fstream, line);

    // skip empty lines
    if (line.length() == 0)
        return this->next_line();

    // lines starting with "#" are interpreted as comments
    if (line[0] != '#') {
        std::stringstream line_stream(line);
        std::string cell;

        while (std::getline(line_stream, cell, ','))
            result.push_back(cell);

        if (!line_stream && cell.empty())
            result.push_back("");
        
        this->_last_line = line;
    }

    return result;
}

void
csv_parser_t::blame_last_line(std::string msg)
{
    std::cerr << "ERROR: " << msg << ": \"";
    for (auto& cell : _last_line)
        std::cerr << cell << ',';
    std::cerr << "\"\n";
    exit(EXIT_FAILURE);
}