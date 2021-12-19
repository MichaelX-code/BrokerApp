#ifndef BROKERAPP_INVESTMENTS_CURRENCY_H
#define BROKERAPP_INVESTMENTS_CURRENCY_H

#include "../utils/utils.h"
#include "investment.hpp"

class Currency : public Investment
{
public:
    Currency(std::string name, double price, double profit, double risk);
private:
};

#endif // BROKERAPP_INVESTMENTS_CURRENCY_H