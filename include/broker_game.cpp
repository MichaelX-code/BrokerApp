#include "broker_game.h"

// Constructors:

BrokerGame::BrokerGame(size_t game_end) :
_market(new Market()), _fund(new Fund()), _game_duration(0), _game_end(game_end)
{}

// Destructor:

BrokerGame::~BrokerGame()
{
    delete _market;
    delete _fund;
}

Market *
BrokerGame::get_market()
{
    return _market;
}

Fund *
BrokerGame::get_fund()
{
    return _fund;
}

date_t
BrokerGame::get_date()
const
{
    return _market->get_date();
}

bool
BrokerGame::step()
{
    _market->step();
    ++_game_duration;

    return (_game_duration != _game_end);
}

void
BrokerGame::_draw_available()
{
    set_cursor_pos(0, 0);
    cursor_row = 1;
    std::stringstream buffer;
    buffer << "   Investments available on the market:\n";
    buffer << table_header(); cursor_row += 2;

    for (auto& investment : _market->get_available())
    {
        buffer << get_table_style_info(investment);
        ++cursor_row;
    }

    std::cout << buffer.str();
    buffer.clear();
}

void
BrokerGame::_draw_owned()
{
    std::stringstream buffer;
    std::pair<int, int> term_size = get_term_size();
    if (term_size.first < 100)
    {
        if (_fund->get_owned().size() == 0)
        {
            std::cout << "\nYou don't own any investments at the moment\n";
            return;
        }

        buffer << "\n           Investments you own:\n";
        buffer << table_header();

        for (auto& investment : _fund->get_owned())
            buffer << get_table_style_info(investment, 1);
    }
    else
    {
        int cur_cursor_row = 0;
        set_cursor_pos(50, cur_cursor_row++);
        if (_fund->get_owned().size() == 0)
        {
            std::cout << "     You don't own any investments at the moment";
            set_cursor_pos(0, cursor_row);
            return;
        }

        std::cout << "           Investments you own:";
        set_cursor_pos(50, cur_cursor_row++);

        std::cout << std::left
                  << std::setw(2)  << "n"      << '|'
                  << std::setw(10) << "Type"   << '|'
                  << std::setw(12) << "Name"   << '|'
                  << std::setw(7)  << "Price"  << '|'
                  << std::setw(6)  << "Profit" << '|'
                  << std::setw(4)  << "Risk";
        set_cursor_pos(50, cur_cursor_row++);
        std::cout << std::string(2,  '-') << '+'
                  << std::string(10, '-') << '+'
                  << std::string(12, '-') << '+'
                  << std::string(7,  '-') << '+'
                  << std::string(6,  '-') << '+'
                  << std::string(4,  '-');

        set_cursor_pos(50, cur_cursor_row++);

        for (auto& investment : _fund->get_owned())
        {
            std::cout << get_table_style_info(investment, 1);
            set_cursor_pos(50, cur_cursor_row++);
        }
        set_cursor_pos(0, cursor_row);
    }

    std::cout << buffer.str();

    buffer.clear();
}

void
BrokerGame::draw_interface()
{
    clear_terminal();
    _draw_available();
    _draw_owned();
}