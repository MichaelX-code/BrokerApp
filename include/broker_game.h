#ifndef BROKERAPP_BROKER_GAME_H
#define BROKERAPP_BROKER_GAME_H

#include "market.h"
#include "fund.h"
#include "utils/utils.h"

class BrokerGame
{
public:
    // Constructor:
    explicit BrokerGame(size_t game_end = 12, rubles default_fund_budget = 1000000);

    // Destructor:
    ~BrokerGame();

    // Functions: selectors (get)
    Market * get_market();
    Fund   * get_fund();
    date_t get_date() const;

    // Methods:
    void step();
    void draw_interface();
    void command();
    void end_screen();
    bool is_not_over();
private:
    Market * _market;
    Fund   * _fund;
    size_t _game_duration;
    size_t _game_end;
    pos_t _cursor_pos = std::make_pair(0, 0);
    game_status _status;
    double _tax_rate = 0.17;

    // Private functions:
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
    void _handle_cmd_add(const std::vector<std::string>& cmd);
    void after_cmd_msg(const std::string& msg, void color());
};

typedef std::unique_ptr<BrokerGame> game_ptr_t;

game_ptr_t game_init();

#endif // BROKERAPP_BROKER_GAME_H
