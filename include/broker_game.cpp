#include "broker_game.h"

BrokerGame::BrokerGame() :
_market(), _fund()
{}

const Market&
BrokerGame::get_market()
const noexcept
{
    return _market;
}

const Fund&
BrokerGame::get_fund()
const noexcept
{
    return _fund;
}

date_t
BrokerGame::get_date()
const
{
    return _market.get_date();
}

void
BrokerGame::step()
{
    _market.step();
}