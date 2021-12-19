#include <iostream>
#include <broker_game.h>

int
main(void)
{
    BrokerGame game {};

    while(game.step())
    {
        game.interface();
    }

    return (EXIT_SUCCESS);
}
