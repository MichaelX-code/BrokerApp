#ifndef BROKERAPP_STOCK_H
#define BROKERAPP_STOCK_H

#include "../utils/utils.h"
#include "investment.hpp"

class Stock : public Investment
{
public:
    Stock(std::string name, double profit, double risk);
private:
    // Private functions:
    inv_id_t generate_id();
};

#endif // BROKERAPP_STOCK_H