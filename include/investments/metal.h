#ifndef BROKERAPP_INVESTMENTS_METAL_H
#define BROKERAPP_INVESTMENTS_METAL_H

#include "../utils/utils.h"
#include "investment.hpp"

class Metal : public Investment
{
public:
    Metal(std::string name, double price, double profit, double risk);
private:
};

#endif // BROKERAPP_INVESTMENTS_METAL_H