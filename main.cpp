#include <iostream>
#include <broker_game.h>

int
main(void)
{
    BrokerGame game;

    for (int i = 0; i < 50; ++i)
    {
        std::cout << game.get_market().get_available()[0]->get_price() << '\n';
        game.step();
    }

    return (EXIT_SUCCESS);
}
