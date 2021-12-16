#include "investment.h"

Investment::Investment(std::string name, double profit, double risk) :
_name(name), _profit(profit), _risk(risk), _id(generate_id())
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
Investment::set_risk(double risk)
{
    if (risk < 0 || 1 <= risk)
    {
        std::cerr << "ERROR: invalid investment risk: " << risk
                  << ". Investment risk has to be [0; 1)\n";
    }
    this->_risk = risk;
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

inv_id_t
Investment::generate_id()
{
    static std::unordered_map<std::string, inv_id_t> inv_types = {
        { "Currency*",   1e3 },
        { "Metal*",      2e3 },
        { "Obligation*", 3e3 },
        { "Stock*",      4e3 },
        { "Investment*", 9e3 },
    };

    return inv_types[demangle(typeid(this).name())] + iota();
}