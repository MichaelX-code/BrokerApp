#include "obligation.h"

Obligation::Obligation(std::string name, double profit, double risk,
                       date_t expiry_date) :
Investment(name, profit, risk), _expiry_date(expiry_date)
{}