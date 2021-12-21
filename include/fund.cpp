#include "fund.h"

Fund::Fund(rubles default_budget) :
_budget(default_budget)
{}

fund_investments_t
Fund::get_owned()
{
    return _owned;
}

double
Fund::get_budget()
const noexcept
{
    return _budget;
}

bool
Fund::buy(investment_ptr_t investment_ptr, int n)
{
    if (!investment_ptr)
        return false;

    if (_budget < investment_ptr->get_price() * n)
    {
        std::cerr << "ERROR: Could not buy investment "
                  << investment_ptr->get_name() << " for "
                  << investment_ptr->get_price() << " RUB: "
                  << "Not enough money!\n";
        return false;
    }

    _budget -= investment_ptr->get_price() * n;
    _owned[investment_ptr] += n;
    return true;
}

bool
Fund::sell(investment_ptr_t investment_ptr, int n)
{
    auto inv_p = _owned.find(investment_ptr);

    if (n < inv_p->second)
        inv_p->second -= n;
    else if (n == inv_p->second)
        _owned.erase(inv_p);
    else
        return false;

    _budget += investment_ptr->get_price() * n;
    return true;
}