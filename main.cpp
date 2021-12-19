#include <iostream>
#include <market.h>

int
main(void)
{
    Market market;

    for (int i = 0; i < 50; ++i)
    {
        std::cout << market.get_available()[0]->get_price() << '\n';
        market.step();
    }

    return (EXIT_SUCCESS);
}
