#include <iostream>
#include <broker_game.h>

int
main(void)
{
    size_t game_duration_in_months = 12;
    rubles starting_fund_budget    = 100000;

    BrokerGame game(game_duration_in_months, starting_fund_budget);

    game.get_fund()->buy(game.get_market()->get_available()[0], 2);
    game.get_fund()->buy(game.get_market()->get_available()[1], 2);
    game.get_fund()->buy(game.get_market()->get_available()[2], 2);

    while(game)
    {
        game.draw_interface();
        game.get_command();
    }

    return (EXIT_SUCCESS);
}