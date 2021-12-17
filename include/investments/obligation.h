#ifndef BROKERAPP_OBLIGATION_H
#define BROKERAPP_OBLIGATION_H

#include "../utils/utils.h"
#include "investment.hpp"

class Obligation : public Investment
{
public:
    // Constructors:
    Obligation(std::string name, double profit, double risk,
               date_t expiry_date);
private:
    // Members:
    date_t _expiry_date;
};

#endif // BROKERAPP_OBLIGATION_H