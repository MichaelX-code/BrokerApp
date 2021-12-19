#include "metal.h"

Metal::Metal(std::string name, double price, double profit, double risk) :
Investment(name, price, profit, risk)
{
    this->_id = 3e3 + iota();
}