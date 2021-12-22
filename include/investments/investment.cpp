#include "investment.hpp"

// Constructors:

Investment::Investment(std::string name, rubles price,
                       double profit, double risk) :
_name(name), _initial_price(price), _price(price), _profit(profit), _risk(risk)
{
    if (risk < 0 || 1 <= risk)
    {
        std::cerr << "ERROR: invalid investment risk: " << risk
                  << ". Investment risk has to be [0; 1)\n";
    }
    if (profit < 0)
    {
        std::cerr << "ERROR: invalid investment profit: " << profit
                  << ". Investment profit has to be >= 0\n";
    }
}

// Destructors:

Investment::~Investment()
{}

inv_id_t
Investment::get_id()
const noexcept
{
    return _id;
}

double
Investment::get_risk()
const noexcept
{
    return _risk;
}

rubles
Investment::get_price()
const noexcept
{
    return _price;
}

rubles
Investment::get_price_change()
const noexcept
{
    return _price - _initial_price;
}

double
Investment::get_profit()
const noexcept
{
    return _profit;
}

std::string
Investment::get_name()
const
{
    return _name;
}

void
Investment::set_price(rubles price)
{
    if (price < 0)
    {
        std::cerr << "ERROR: invalid investment price: " << price
                  << ". Investment price has to be >= 0\n";
    }
    _price = price;
}

void
Investment::set_profit(double profit)
{
    if (profit < 0)
    {
        std::cerr << "ERROR: invalid investment profit: " << profit
                  << ". Investment profit has to be >= 0\n";
    }
    _profit = profit;
}

void
Investment::set_risk(double risk)
{
    if (risk < 0 || 1 <= risk)
    {
        std::cerr << "ERROR: invalid investment risk: " << risk
                  << ". Investment risk has to be [0; 1)\n";
    }
    _risk = risk;
}

// Operators overloads:

bool
Investment::operator == (const Investment& other)
{
    return (this->get_id() == other.get_id());
}

bool
Investment::operator != (const Investment& other)
{
    return !(*this == other);
}

investment_ptr_t
find_by_id(investments_list_t invs, inv_id_t id)
{
    for (auto& inv : invs)
        if (inv->get_id() == id)
            return inv;
    return nullptr;
}