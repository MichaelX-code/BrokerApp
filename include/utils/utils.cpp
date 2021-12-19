#include "utils.h"

inv_id_t
iota()
{
    static inv_id_t _count = 1;
    return _count++;
}

void
clear_terminal()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

std::string
table_header()
{
    std::stringstream buffer;
    buffer << std::left << ' '
           << std::setw(10) << "Type"   << " | "
           << std::setw(17) << "Name"   << " | "
           << std::setw(7)  << "Price"  << " | "
           << std::setw(10) << "Profit" << " | "
           << std::setw(4)  << "Risk"   << '\n';

    buffer << std::string(12, '-') << '+'
           << std::string(19, '-') << '+'
           << std::string(9,  '-') << '+'
           << std::string(12, '-') << '+'
           << std::string(6,  '-') << '\n';

    return buffer.str();
}