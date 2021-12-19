#include "fund.h"

Fund::Fund() :
_budget(100000)
{}

const investments_list_t&
Fund::get_owned()
const noexcept
{
    return _owned;
}

double
Fund::get_budget()
const noexcept
{
    return _budget;
}

void
Fund::buy(investment_ptr_t investment_ptr)
{
    if (_budget < investment_ptr->get_price())
    {
        std::cerr << "ERROR: Could not buy investment "
                  << investment_ptr->get_name() << " for "
                  << investment_ptr->get_price() << " RUB: "
                  << "Not enough money!\n";
        return;
    }

    _budget -= investment_ptr->get_price();
    _owned.push_back(investment_ptr);
}

void
Fund::sell(investment_ptr_t investment_ptr)
{
    _budget += investment_ptr->get_price();
    _owned.erase(_owned.find(investment_ptr));
}