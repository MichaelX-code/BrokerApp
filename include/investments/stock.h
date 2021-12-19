#ifndef BROKERAPP_INVESTMENTS_STOCK_H
#define BROKERAPP_INVESTMENTS_STOCK_H

#include "../utils/utils.h"
#include "investment.hpp"

class Stock : public Investment
{
public:
    Stock(std::string name, double price, double profit, double risk);
};

#endif // BROKERAPP_INVESTMENTS_STOCK_H