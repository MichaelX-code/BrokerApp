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
    buffer << std::left 
           << std::setw(10) << "Type"   << '|'
           << std::setw(12) << "Name"   << '|'
           << std::setw(7)  << "Price"  << '|'
           << std::setw(6)  << "Profit" << '|'
           << std::setw(4)  << "Risk"   << '\n';

    buffer << std::string(10, '-') << '+'
           << std::string(12, '-') << '+'
           << std::string(7,  '-') << '+'
           << std::string(6,  '-') << '+'
           << std::string(4,  '-') << '\n';

    return buffer.str();
}

void
set_cursor_pos(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

std::pair<int, int>
get_term_size()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return std::make_pair(columns, rows);
#else
    struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
    return std::make_pair(max.ws_col, max.ws_row);
#endif
}