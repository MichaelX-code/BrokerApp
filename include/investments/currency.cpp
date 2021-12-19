#include "currency.h"

Currency::Currency(std::string name, double price, double profit, double risk) :
Investment(name, price, profit, risk)
{
    this->_id = 4e3 + iota();
}