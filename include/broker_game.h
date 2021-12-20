#ifndef BROKERAPP_BROKER_GAME_H
#define BROKERAPP_BROKER_GAME_H

#include "market.h"
#include "fund.h"
#include "utils/utils.h"

class BrokerGame
{
public:
    // Constructor:
    BrokerGame(size_t game_end = 12, rubles default_fund_budget = 1000000);

    // Destructor:
    ~BrokerGame();

    // Functions: selectors (get)
    Market * get_market();
    Fund   * get_fund();
    date_t get_date()              const;

    // Methods:
    void step();
    void draw_interface();
    void get_command();

    // Operators overloads:
    operator bool () const;
private:
    Market * _market;
    Fund   * _fund;
    size_t _game_duration;
    size_t _game_end;
    int _cursor_row = 0;
    game_status_t _status;

    // Private functions:
    void _draw_available();
    void _draw_owned();
    void _draw_stats();
    void _draw_help();
    void _draw_easter();
    void _draw_console();
    void error_cmd_msg(std::string msg, void color());
};

#endif // BROKERAPP_BROKER_GAME_H
