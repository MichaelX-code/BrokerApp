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

const Market *
BrokerGame::get_market()
const noexcept
{
    return _market;
}

const Fund *
BrokerGame::get_fund()
const noexcept
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
const
{
    std::stringstream buffer;
    buffer << "             Investments available on the market:\n";
    buffer << table_header();

    for (auto& investment : _market->get_available())
        buffer << get_table_style_info(investment);

    std::cout << buffer.str();
}

void
BrokerGame::_draw_owned()
const
{
    if (_fund->get_owned().size() == 0)
    {
        std::cout << "\nYou don't own any investments at the moment\n";
        return;
    }

    std::stringstream buffer;
    buffer << "\n             Investments you own:\n";
    buffer << table_header();

    for (auto& investment : _fund->get_owned())
        buffer << get_table_style_info(investment);

    std::cout << buffer.str();
}

void
BrokerGame::interface()
const
{
    clear_terminal();
    _draw_available();
    _draw_owned();
}