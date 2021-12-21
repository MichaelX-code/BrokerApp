#ifndef BROKERAPP_FUND_H
#define BROKERAPP_FUND_H

#include "investments/investment.hpp"

class Fund
{
public:
    // Constructor:
    Fund(rubles default_budget);

    // Functions: selectors (get)
    fund_investments_t get_owned();
    rubles get_budget() const noexcept;

    // Methods:
    bool buy(investment_ptr_t investment_ptr, int n);
    bool sell(investment_ptr_t investment_ptr, int n);
    rubles calc_earnings() const;
    bool pay_taxes(double tax_rate);
private:
    fund_investments_t _owned;
    rubles _budget;
    rubles _start_budget;
};

#endif // BROKERAPP_FUND_H
