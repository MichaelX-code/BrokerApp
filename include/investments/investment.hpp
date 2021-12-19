#ifndef BROKERAPP_INVESTMENTS_INVESTMENT_H
#define BROKERAPP_INVESTMENTS_INVESTMENT_H

#include "../utils/utils.h"

class Investment
{
public:
    // Constructors:
    Investment(std::string name, double price, double profit, double risk);

    // Destructors:
    virtual ~Investment() = 0;

    // Functions: selectors (get)
    inv_id_t get_id()           const noexcept;
    double get_price()          const noexcept;
    double get_risk()           const noexcept;
    double get_profit()         const noexcept;
    std::string get_name()      const;

    
    // Functions: modifiers (set)
    void set_price(double price);
    void set_profit(double profit);
    void set_risk(double risk);

    // Operators overloads:
    bool operator == (const Investment& other);
    bool operator != (const Investment& other);

protected:
    // Members:
    const std::string _name;
    double _price;
    double _profit;
    double _risk;
    inv_id_t _id;
};

typedef std::shared_ptr<Investment> investment_ptr_t;
typedef list<investment_ptr_t> investments_list_t;

#endif // BROKERAPP_INVESTMENTS_INVESTMENT_H