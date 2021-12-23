#include <broker_game.h>

int
main(void)
{
    fix_term_encoding();

    auto game = game_init();

    while(game->is_not_over())
    {
        game->draw_interface();
        game->command();
    }

    game->end_screen();

    return (EXIT_SUCCESS);
}