#ifndef BROKERAPP_INVESTMENTS_OBLIGATION_H
#define BROKERAPP_INVESTMENTS_OBLIGATION_H

#include "../utils/utils.h"
#include "investment.hpp"

class Obligation : public Investment
{
public:
    // Constructors:
    Obligation(std::string name, rubles price, double profit, double risk,
               date_t expiry_date);

    // Functions: selectors (get)
    date_t get_expiry_date() const;
private:
    // Members:
    date_t _expiry_date;
};

typedef std::shared_ptr<Obligation> obligation_ptr_t;

#endif // BROKERAPP_INVESTMENTS_OBLIGATION_H