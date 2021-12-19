#include "investment.hpp"

// Constructors:

Investment::Investment(std::string name, double price,
                       double profit, double risk) :
_name(name), _price(price), _profit(profit), _risk(risk)
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
    return this->_id;
}

double
Investment::get_risk()
const noexcept
{
    return this->_risk;
}

double
Investment::get_price()
const noexcept
{
    return this->_price;
}

double
Investment::get_profit()
const noexcept
{
    return this->_profit;
}

std::string
Investment::get_name()
const
{
    return this->_name;
}

void
Investment::set_price(double price)
{
    if (price < 0)
    {
        std::cerr << "ERROR: invalid investment price: " << price
                  << ". Investment price has to be >= 0\n";
    }
    this->_price = price;
}

void
Investment::set_profit(double profit)
{
    if (profit < 0)
    {
        std::cerr << "ERROR: invalid investment profit: " << profit
                  << ". Investment profit has to be >= 0\n";
    }
    this->_profit = profit;
}

void
Investment::set_risk(double risk)
{
    if (risk < 0 || 1 <= risk)
    {
        std::cerr << "ERROR: invalid investment risk: " << risk
                  << ". Investment risk has to be [0; 1)\n";
    }
    this->_risk = risk;
}
