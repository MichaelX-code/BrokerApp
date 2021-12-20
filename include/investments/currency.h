#ifndef BROKERAPP_INVESTMENTS_CURRENCY_H
#define BROKERAPP_INVESTMENTS_CURRENCY_H

#include "../utils/utils.h"
#include "investment.hpp"

class Currency : public Investment
{
public:
    // Constructors:
    Currency(std::string name, rubles price, double profit, double risk);
private:
};

typedef std::shared_ptr<Currency> currency_ptr_t;

#endif // BROKERAPP_INVESTMENTS_CURRENCY_H