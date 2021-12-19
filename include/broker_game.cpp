#include "broker_game.h"

// Constructors:

BrokerGame::BrokerGame() :
_market(new Market()), _fund(new Fund())
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

void
BrokerGame::step()
{
    _market->step();
}