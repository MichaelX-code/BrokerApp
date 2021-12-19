#ifndef BROKERAPP_FUND_H
#define BROKERAPP_FUND_H

#include "investments/investment.hpp"

class Fund
{
public:
    // Constructor:
    Fund();

    // Functions: selectors (get)
    const investments_list_t& get_owned()   const noexcept;
    double get_budget()                     const noexcept;

    // Methods:
    void buy(investment_ptr_t investment_ptr);
    void sell(investment_ptr_t investment_ptr);
private:
    investments_list_t _owned;
    double _budget;
};

#endif // BROKERAPP_FUND_H
