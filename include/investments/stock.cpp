#include "stock.h"

Stock::Stock(std::string name, double price, double profit, double risk) :
Investment(name, price, profit, risk)
{
    this->_id = 1e3 + iota();
}