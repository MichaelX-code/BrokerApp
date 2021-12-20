#ifndef BROKERAPP_FUND_H
#define BROKERAPP_FUND_H

#include "investments/investment.hpp"

class Fund
{
public:
    // Constructor:
    Fund(rubles default_budget);

    // Functions: selectors (get)
    const fund_investments_t& get_owned()   const noexcept;
    double get_budget()                     const noexcept;

    // Methods:
    bool buy(investment_ptr_t investment_ptr, int n);
    bool sell(investment_ptr_t investment_ptr, int n);
private:
    fund_investments_t _owned;
    double _budget;
};

#endif // BROKERAPP_FUND_H
