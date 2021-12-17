#ifndef BROKERAPP_MARKET_H
#define BROKERAPP_MARKET_H

#include "investments/investment.hpp"
#include "investments/stock.h"
#include "investments/obligation.h"
#include "investments/metal.h"
#include "utils/utils.h"

class Market
{
public:
    // Constructor:
    Market();

    // Functions: selectors (get)
    date_t get_date() const;
    list<std::unique_ptr<Investment>> get_available() const;
private:
    // Members:
    date_t _cur_date;
    list<std::unique_ptr<Investment>> _available;
};

#endif // BROKERAPP_MARKET_H
