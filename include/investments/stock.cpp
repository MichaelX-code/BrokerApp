#include "stock.h"

Stock::Stock(std::string name, rubles price, double profit, double risk) :
Investment(name, price, profit, risk)
{
    this->_id = 1e2 + iota();
}