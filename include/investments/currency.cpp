#include "currency.h"

Currency::Currency(std::string name, rubles price, double profit, double risk) :
Investment(name, price, profit, risk)
{
    this->_id = 400 + iota();
}