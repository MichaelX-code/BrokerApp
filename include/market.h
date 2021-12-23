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
    const investments_list_t& get_available() const;

    // Methods:
    void step();
private:
    // Members:
    date_t _cur_date;
    investments_list_t _available;

    // Helpful functions:
    void _step_date();
    void _update_prices();
    void _clean_expired();
};

std::string get_inv_type(const investment_ptr_t& investment_ptr);
[[maybe_unused]] std::string get_csv_style_info(const investment_ptr_t& investment_ptr);
std::string get_table_style_info(const investment_ptr_t &investment_ptr, int n);

#endif // BROKERAPP_MARKET_H
