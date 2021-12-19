#ifndef BROKERAPP_BROKER_GAME_H
#define BROKERAPP_BROKER_GAME_H

#include "market.h"
#include "fund.h"
#include "utils/utils.h"

class BrokerGame
{
public:
    // Constructor:
    BrokerGame(size_t game_end = 12);

    // Destructor:
    ~BrokerGame();

    // Functions: selectors (get)
    const Market * get_market()    const noexcept;
    const Fund   * get_fund()      const noexcept;
    date_t get_date()              const;

    // Methods:
    bool step();
    void interface()               const;
private:
    Market * _market;
    Fund   * _fund;
    size_t _game_duration;
    size_t _game_end;

    // Private functions:
    void _draw_available()          const;
    void _draw_owned()              const;

    void handle_command(std::string command);
};

#endif // BROKERAPP_BROKER_GAME_H
