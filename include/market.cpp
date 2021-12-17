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
            if (inv_info.size() != 4)
                csv_parser.blame_last_line("Not valid number of args");

            std::string stock_name = inv_info[1];
            double stock_profit = stod(inv_info[2]);
            double stock_risk = stod(inv_info[3]);
            this->_available.emplace_back(
                new Stock(stock_name, stock_profit, stock_risk)
            );
        }
        else if (inv_info[0] == "Obligation")
        {
            if (inv_info.size() != 5)
                csv_parser.blame_last_line("Not valid number of args");

            std::string obl_name = inv_info[1];
            double obl_profit = stod(inv_info[2]);
            double obl_risk = stod(inv_info[3]);
            date_t obl_expiry_date = inv_info[4];
            this->_available.emplace_back(
                new Obligation(obl_name, obl_profit, obl_risk, obl_expiry_date)
            );
        }
        else if (inv_info[0] == "Metal")
        {
            if (inv_info.size() != 4)
                csv_parser.blame_last_line("Not valid number of args");

            std::string metal_name = inv_info[1];
            double metal_profit = stod(inv_info[2]);
            double metal_risk = stod(inv_info[3]);
            this->_available.emplace_back(
                new Metal(metal_name, metal_profit, metal_risk)
            );
        }
        else
        {
            csv_parser.blame_last_line("Unkown Investment type");
        }
    }
}

// Functions: selectors (get)

date_t
Market::get_date()
const
{
    return this->_cur_date;
}

list<std::unique_ptr<Investment>>
Market::get_available()
const
{
    return this->_available;
}