#ifndef BROKERAPP_BROKER_GAME_H
#define BROKERAPP_BROKER_GAME_H

#include "market.h"
#include "fund.h"
#include "utils/utils.h"

enum tui_mode_t {
    SINGLE_COLUMN,
    TWO_COLUMNS
};

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
    void command();
    void end();

    // Operators overloads:
    operator bool () const;
private:
    Market * _market;
    Fund   * _fund;
    size_t _game_duration;
    size_t _game_end;
    pos_t _cursor_pos = std::make_pair(0, 0);
    game_status_t _status;
    tui_mode_t _tui_mode;
    double _tax_rate = 0.17;

    // Private functions:
    tui_mode_t _pick_tui_mode();

    void _draw_available();
    void _draw_owned();
    void _draw_single_column_owned();
    void _draw_two_columns_owned();
    void _clear_second_column(int second_col);
    void _draw_quick_stats();
    void _draw_help();
    void _draw_full_stats();
    void _draw_easter();
    void _draw_console();

    void _handle_cmd_buy(const std::vector<std::string>& cmd);
    void _handle_cmd_sell(const std::vector<std::string>& cmd);

    void after_cmd_msg(std::string msg, void color());
};

#endif // BROKERAPP_BROKER_GAME_H
