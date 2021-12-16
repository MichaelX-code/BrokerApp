#ifndef BROKERAPP_INVESTMENT_H
#define BROKERAPP_INVESTMENT_H

#include "utils/utils.h"

class Investment
{
public:
    // Constructors:
    Investment(std::string name, double profit, double risk);

    // Destructors:
    // virtual ~Investment() = 0;

    // Functions: selectors (get)
    inv_id_t get_id() const noexcept;
    double get_risk() const noexcept;
    double get_profit() const noexcept;
    std::string get_name() const;
    
    // Functions: modifiers (set)
    void set_risk(double risk);
    void set_profit(double profit);

protected:
    // Members:
    double _risk;
    double _profit;
    const std::string _name;
    const inv_id_t _id;

private:
    // Helpful private methods:
    inv_id_t generate_id();
};

#endif // BROKERAPP_INVESTMENT_H