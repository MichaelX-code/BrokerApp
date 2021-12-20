#ifndef BROKERAPP_INVESTMENTS_STOCK_H
#define BROKERAPP_INVESTMENTS_STOCK_H

#include "../utils/utils.h"
#include "investment.hpp"

class Stock : public Investment
{
public:
    // Constructors:
    Stock(std::string name, rubles price, double profit, double risk);
};

typedef std::shared_ptr<Stock> stock_ptr_t;

#endif // BROKERAPP_INVESTMENTS_STOCK_H