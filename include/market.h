#ifndef BROKERAPP_MARKET_H
#define BROKERAPP_MARKET_H

#include "investments/investment.hpp"
#include "investments/stock.h"
#include "investments/obligation.h"
#include "investments/metal.h"
#include "investments/currency.h"
#include "utils/utils.h"

class Market
{
public:
    // Constructor:
    Market();

    // Functions: selectors (get)
    date_t get_date() const;
    const list<std::shared_ptr<Investment>>& get_available() const;

    // Methods:
    void step();
private:
    // Members:
    date_t _cur_date;
    list<std::shared_ptr<Investment>> _available;

    // Helpful functions:
    void _step_date();
    void _update_prices();
    void _clean_expired();
};

#endif // BROKERAPP_MARKET_H
