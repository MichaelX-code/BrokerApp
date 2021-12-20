#include "obligation.h"

Obligation::Obligation(std::string name, rubles price, double profit,
                       double risk, date_t expiry_date) :
Investment(name, price, profit, risk), _expiry_date(expiry_date)
{
    this->_id = 2e2 + iota();
}

date_t
Obligation::get_expiry_date()
const
{
    return this->_expiry_date;
}