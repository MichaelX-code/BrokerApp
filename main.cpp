#include <iostream>
#include <market.h>

int
main(void)
{
    Market market; 
    list<int> li = {1, 2, 3};
    li.push_back(4);
    list<std::unique_ptr<Investment>> invs = market.get_available();
    for (auto& inv : invs)
        std::cout << inv->get_name() << ' ' << inv->get_id() << '\n';

    return (EXIT_SUCCESS);
}
