#include <iostream>
#include <broker_game.h>

int
main(void)
{
    size_t game_duration_in_months = 12;
    rubles starting_fund_budget    = 100000;

    BrokerGame game(game_duration_in_months, starting_fund_budget);

    while(game)
    {
        game.draw_interface();
        game.get_command();
    }

    return (EXIT_SUCCESS);
}