#include "fund.h"

Fund::Fund(rubles default_budget) :
_budget(default_budget), _start_budget(default_budget)
{}

fund_investments_t
Fund::get_owned()
{
    return _owned;
}

rubles
Fund::get_budget()
const noexcept
{
    return _budget;
}

bool
Fund::buy(investment_ptr_t investment_ptr, int n)
{
    if (!investment_ptr || (_budget < investment_ptr->get_price() * n))
        return false;

    _budget -= investment_ptr->get_price() * n;
    _owned[investment_ptr] += n;
    return true;
}

bool
Fund::sell(investment_ptr_t investment_ptr, int n)
{
    auto inv_p = _owned.find(investment_ptr);

    if (inv_p == _owned.end())
        return false;

    if (n < inv_p->second)
        inv_p->second -= n;
    else if (n == inv_p->second)
        _owned.erase(inv_p);
    else
        return false;

    _budget += investment_ptr->get_price() * n;
    return true;
}

rubles
Fund::calc_earnings()
const
{
    auto each = [](rubles x, const std::pair<investment_ptr_t, int>& inv_p) {
                         return x + inv_p.first->get_price() * inv_p.second;
                };

    rubles _cur_wealth = std::accumulate(_owned.begin(), _owned.end(), _budget,
                                         each);
    
    return _cur_wealth - _start_budget;
}

bool
Fund::pay_taxes(double tax_rate)
{
    if (tax_rate < 0 || tax_rate > 1)
        return false;

    if (calc_earnings() > 0)
        _budget -= calc_earnings() * tax_rate;    
    
    return true;
}