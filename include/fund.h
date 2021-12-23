#ifndef BROKERAPP_FUND_H
#define BROKERAPP_FUND_H

#include "investments/investment.hpp"

class Fund
{
public:
    // Constructor:
    explicit Fund(rubles default_budget);

    // Functions: selectors (get)
    fund_investments_t get_owned();
    rubles get_budget() const noexcept;

    // Methods:
    bool buy(const investment_ptr_t& investment_ptr, int n);
    bool sell(const investment_ptr_t& investment_ptr, int n, double tax_rate);
    void add_to_budget(rubles amount);
    rubles calc_earnings() const;
private:
    fund_investments_t _owned;
    rubles _budget;
    rubles _initial_budget;
};

#endif // BROKERAPP_FUND_H
