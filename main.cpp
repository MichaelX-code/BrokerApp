#include <broker_game.h>

int
main(void)
{
    fix_term_encoding();

    size_t game_duration_in_months = 24;
    rubles starting_fund_budget    = 500000;

    BrokerGame game(game_duration_in_months, starting_fund_budget);

    while(game)
    {
        game.draw_interface();
        game.command();
    }

    game.end();

    return (EXIT_SUCCESS);
}