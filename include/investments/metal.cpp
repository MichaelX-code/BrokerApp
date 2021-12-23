#include "metal.h"

Metal::Metal(std::string name, rubles price, double profit, double risk) :
Investment(name, price, profit, risk)
{
    this->_id = 300 + iota();
}