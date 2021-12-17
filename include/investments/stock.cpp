#include "stock.h"

Stock::Stock(std::string name, double profit, double risk) :
Investment(name, profit, risk)
{}

inv_id_t
Stock::generate_id()
{
    return 1e3 + iota();
}