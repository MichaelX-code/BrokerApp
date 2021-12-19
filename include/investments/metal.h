#ifndef BROKERAPP_INVESTMENTS_METAL_H
#define BROKERAPP_INVESTMENTS_METAL_H

#include "../utils/utils.h"
#include "investment.hpp"

class Metal : public Investment
{
public:
    // Constructors:
    Metal(std::string name, double price, double profit, double risk);
private:
};

typedef std::shared_ptr<Metal> metal_ptr_t;

#endif // BROKERAPP_INVESTMENTS_METAL_H