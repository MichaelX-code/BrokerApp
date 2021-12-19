#include <iostream>
#include <broker_game.h>

int
main(void)
{
    BrokerGame game {};

    game.get_fund()->buy(game.get_market()->get_available()[0]);

    while(game.step())
    {
        game.interface();
    }

    return (EXIT_SUCCESS);
}