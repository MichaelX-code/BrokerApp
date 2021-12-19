#include "market.h"

// Constructors:

Market::Market()
{
    csv_parser_t csv_parser("../assets/available_investments.csv");

    while (!csv_parser.empty())
    {
        std::vector<std::string> inv_info = csv_parser.next_line();

        // skip empty lines
        if (inv_info.size() == 0)
            continue;

        if (inv_info[0] == "Stock")
        {
            if (inv_info.size() != 5)
                csv_parser.blame_last_line("Not valid number of args");

            std::string stock_name = inv_info[1];
            double stock_price = stod(inv_info[2]);
            double stock_profit = stod(inv_info[3]);
            double stock_risk = stod(inv_info[4]);
            this->_available.emplace_back(
                new Stock(stock_name, stock_price, stock_profit, stock_risk)
            );
        }
        else if (inv_info[0] == "Obligation")
        {
            if (inv_info.size() != 6)
                csv_parser.blame_last_line("Not valid number of args");

            std::string obl_name = inv_info[1];
            double obl_price = stod(inv_info[2]);
            double obl_profit = stod(inv_info[3]);
            double obl_risk = stod(inv_info[4]);
            date_t obl_expiry_date = inv_info[5];
            this->_available.emplace_back(
                new Obligation(obl_name, obl_price, obl_profit,
                               obl_risk, obl_expiry_date)
            );
        }
        else if (inv_info[0] == "Metal")
        {
            if (inv_info.size() != 5)
                csv_parser.blame_last_line("Not valid number of args");

            std::string metal_name = inv_info[1];
            double metal_price = stod(inv_info[2]);
            double metal_profit = stod(inv_info[3]);
            double metal_risk = stod(inv_info[4]);
            this->_available.emplace_back(
                new Metal(metal_name, metal_price, metal_profit, metal_risk)
            );
        }
        else if (inv_info[0] == "Currency")
        {
            if (inv_info.size() != 5)
                csv_parser.blame_last_line("Not valid number of args");

            std::string cur_name = inv_info[1];
            double cur_price = stod(inv_info[2]);
            double cur_profit = stod(inv_info[3]);
            double cur_risk = stod(inv_info[4]);
            this->_available.emplace_back(
                new Currency(cur_name, cur_price, cur_profit, cur_risk)
            );
        }
        else
        {
            csv_parser.blame_last_line("Unkown Investment type");
        }
    }

    // generate a seed for rand() in future
    srand(std::time(0));
}

// Functions: selectors (get)

date_t
Market::get_date()
const
{
    return this->_cur_date;
}

const list<std::shared_ptr<Investment>>&
Market::get_available()
const
{
    return this->_available;
}

// Methods:

void
Market::_step_date()
{
    if (_cur_date.get_month() == 12)
    {
        _cur_date.set_year(_cur_date.get_year() + 1);
        _cur_date.set_month(1);
    }
    else
    {
        _cur_date.set_month(_cur_date.get_month() + 1);
    }
}

void
Market::_update_prices()
{
    for (auto& inv : _available)
    {
        // random number from [-1; 1]
        double rand_d = (static_cast<double>(rand()) / RAND_MAX) * 2 - 1;
        double new_price = inv->get_price() * (1 + rand_d * inv->get_profit() *
                                                   inv->get_risk());
        inv->set_price(new_price);
    }
}

void
Market::_clean_expired()
{
    std::shared_ptr<Obligation> obl(nullptr);
    for (auto it = _available.begin(); it != _available.end(); ++it)
    {
        if ((obl = std::dynamic_pointer_cast<Obligation>(*it)) &&
            obl->get_expiry_date() <= _cur_date)
        {
            _available.erase(it);
        }
    }
}

void
Market::step()
{
    _step_date();
    _update_prices();
    _clean_expired();
}