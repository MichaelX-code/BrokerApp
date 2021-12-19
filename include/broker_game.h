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
    Market * get_market();
    Fund   * get_fund();
    date_t get_date()              const;

    // Methods:
    bool step();
    void interface();
private:
    Market * _market;
    Fund   * _fund;
    size_t _game_duration;
    size_t _game_end;
    int cursor_row = 0;

    // Private functions:
    void _draw_available();
    void _draw_owned();

    void handle_command(std::string command);
};

#endif // BROKERAPP_BROKER_GAME_H
