#ifndef BROKERAPP_BROKER_GAME_H
#define BROKERAPP_BROKER_GAME_H

#include "market.h"
#include "fund.h"
#include "utils/utils.h"

class BrokerGame
{
public:
    // Constructor:
    BrokerGame();

    // Functions: selectors (get)
    const Market& get_market()      const noexcept;
    const Fund& get_fund()          const noexcept;
    date_t get_date()               const;

    // Methods:
    void step();
private:
    Market _market;
    Fund   _fund;
};

#endif // BROKERAPP_BROKER_GAME_H
