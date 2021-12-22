#include "broker_game.h"

// Constructors:

BrokerGame::BrokerGame(size_t game_end, rubles default_fund_budget) :
_market(new Market()), _fund(new Fund(default_fund_budget)), _game_duration(0),
_game_end(game_end), _status(PLAYING), _tui_mode(_pick_tui_mode())
{}

// Destructor:

BrokerGame::~BrokerGame()
{
    delete _market;
    delete _fund;
}

Market *
BrokerGame::get_market()
{
    return _market;
}

Fund *
BrokerGame::get_fund()
{
    return _fund;
}

date_t
BrokerGame::get_date()
const
{
    return _market->get_date();
}

void
BrokerGame::step()
{
    _market->step();
    ++_game_duration;

    if (_game_duration == _game_end)
        _status = ENDED;
}

BrokerGame::operator bool()
const
{
    return (_status == PLAYING);
}

tui_mode_t
BrokerGame::_pick_tui_mode()
{
    return (get_term_size().first < 100 ? SINGLE_COLUMN : TWO_COLUMNS);
}

void
BrokerGame::_draw_available()
{
    set_cursor_pos(0, 0);
    std::cout << "   Investments available on the market:\n";
    std::cout << table_header();

    for (auto& investment : _market->get_available())
        std::cout << get_table_style_info(investment) << '\n';

    _cursor_pos.second = 3 + _market->get_available().size();
}

void
BrokerGame::_draw_single_column_owned()
{
    if (_fund->get_owned().size() == 0)
    {
        std::cout << "\nYou don't own any investments at the moment\n";
        _cursor_pos.second += 2;
        return;
    }

    std::cout << "\n           Investments you own:\n";
    std::cout << std::left << std::setw(3)  << "n" << '|' << get_table_header()
              << '\n';
    std::cout << std::string(3,  '-') << '+' << get_table_divider()
              << '\n';

    for (auto& inv : _fund->get_owned())
        std::cout << get_table_style_info(inv.first, inv.second) << '\n';

    _cursor_pos.second += 4 + _fund->get_owned().size();
}

void
BrokerGame::_draw_two_columns_owned()
{
    int cur_cursor_row = 0;
    int second_col = 49;

    _clear_second_column(second_col);

    set_cursor_pos(second_col, cur_cursor_row++);

    if (_fund->get_owned().size() == 0)
    {
        std::cout << "     You don't own any investments at the moment";
        set_cursor_pos(_cursor_pos.first, _cursor_pos.second);
        return;
    }

    std::cout << "           Investments you own:";
    set_cursor_pos(second_col, cur_cursor_row++);
    std::cout << std::left << std::setw(3)  << "n" << '|' << get_table_header()
              << '\n';
    set_cursor_pos(second_col, cur_cursor_row++);
    std::cout << std::string(3,  '-') << '+' << get_table_divider()
              << '\n';

    set_cursor_pos(second_col, cur_cursor_row++);
    for (auto& inv : _fund->get_owned())
    {
        std::cout << get_table_style_info(inv.first, inv.second) << '\n';
        set_cursor_pos(second_col, cur_cursor_row++);
    }
    set_cursor_pos(_cursor_pos.first, _cursor_pos.second);
}

void
BrokerGame::_clear_second_column(int second_col)
{
    int cur_cursor_row = 0;
    set_cursor_pos(second_col, cur_cursor_row++);

    size_t n_lines = _market->get_available().size();
    size_t n_col = get_term_size().first - second_col;

    for (size_t i = 0; i < n_lines; ++i)
    {
        std::cout << std::string(n_col, ' ');
        set_cursor_pos(second_col, cur_cursor_row++);
    }

    set_cursor_pos(_cursor_pos.first, _cursor_pos.second);
}

void
BrokerGame::_draw_owned()
{
    if (_tui_mode == SINGLE_COLUMN)
        _draw_single_column_owned();
    else
        _draw_two_columns_owned();
}

void
BrokerGame::_draw_quick_stats()
{
    _cursor_pos.first = 0;
    _cursor_pos.second = 3 + _market->get_available().size();
    set_cursor_pos(_cursor_pos.first, _cursor_pos.second);

    for (int i = 0; i < 4; ++i)
        std::cout << std::string(get_term_size().first, ' ') << '\n';

    set_cursor_pos(_cursor_pos.first, _cursor_pos.second);
    std::cout << "\nQuick stats:\n";    
    std::cout << "Current date: " << _market->get_date().get_formated() << '\n';
    std::cout << "Fund budget: " << _fund->get_budget() << " rub" << '\n';

    std::cout << "Total earnings: "; 
    if (_fund->calc_earnings() > 0)
        set_tem_color_green();
    else if (_fund->calc_earnings() < 0)
        set_tem_color_red();

    std::cout << _fund->calc_earnings() << " rub" << '\n';
    set_tem_color_default();

    _cursor_pos.second += 5;
}

void
BrokerGame::_draw_console()
{
    std::cout << "\nEnter a command (\"help\" to see all commands):\n";
    std::cout << "> ";
    _cursor_pos.first = 2;
    _cursor_pos.second += 2;
}

void
BrokerGame::draw_interface()
{
    clear_terminal();
    _draw_available();
    _draw_owned();
    _draw_quick_stats();
    _draw_console();
}

void
BrokerGame::_draw_help()
{
    static list<std::pair<std::string, std::string>> commands_help = {
        { "help", "Opens this help menu" },
        { "next", "End turn and go to the next month" },
        { "stats", "Opens all stats available in the game" },
        { "buy [id] [n]", "Buy n investment lots with specific id" },
        { "sell [id] [n]", "Sell n investment lots with specific id" },
        { "quit", "End the game immediately" }
    };

    int offset = 20;

    clear_terminal();
    std::cout << "Command";
    set_cursor_pos(offset, 0);
    std::cout << "Description";

    int current_row = 2;
    for (auto& command : commands_help)
    {
        set_cursor_pos(0, current_row);
        std::cout << command.first;
        set_cursor_pos(offset, current_row++);
        std::cout << command.second;
    }
    
    set_cursor_pos(0, current_row);
    std::cout << "\nPress ENTER to go back to the game...\n";
    getchar();
    draw_interface();
}

void
BrokerGame::_draw_full_stats()
{
    clear_terminal();
    int cursor_x = 0, cursor_y = 0;
    set_cursor_pos(cursor_x, cursor_y);

    if (_fund->get_owned().size() > 0)
    {
        std::cout << "      All stats for your investments:\n";

        std::cout << std::left << std::setw(3)  << "n" << '|' << get_table_header()
                  << '|' << std::setw(12) << "Price change\n";
        std::cout << std::string(3,  '-') << '+' << get_table_divider()
                  << '+' << std::string(12, '-') << '\n';

        for (auto& inv : _fund->get_owned())
        {
            std::cout << get_table_style_info(inv.first, inv.second);

            rubles price_change = inv.first->get_price_change();

            std::cout << '|';
            if (price_change > 0)
            {
                set_tem_color_green();
                std::cout << '+';
            }
            else if (price_change < 0)
            {
                set_tem_color_red();
            }
            std::cout << std::setw(12) << price_change << '\n';
            set_tem_color_default();
        }
    }
    else
    {
        std::cout << "\nYou don't own any investments at the moment\n";
    }

    std::cout << "\nPress ENTER to go back to the game...\n";
    getchar();
    draw_interface();
}

void
BrokerGame::command()
{
    std::string command;

    while (true)
    {
        std::getline(std::cin, command);
        std::vector<std::string> cmd_split = parse_into_words(command);
        size_t cmd_sz = cmd_split.size();

        if (cmd_sz == 0)
            continue;

        if (cmd_sz == 1 && cmd_split[0] == "help")
        {
            _draw_help();
        }
        else if (cmd_sz == 1 && cmd_split[0] == "next")
        {
            step();
            return;
        }
        else if (cmd_sz == 1 && cmd_split[0] == "quit")
        {
            _status = ENDED;
            clear_terminal();
            return;
        }
        else if (cmd_sz == 1 && cmd_split[0] == "stats")
        {
            _draw_full_stats();
        }
        else if (cmd_sz == 1 && cmd_split[0] == "easter")
        {
            _draw_easter();
        }
        else if (cmd_sz >= 1 && cmd_split[0] == "buy")
        {
            _handle_cmd_buy(cmd_split);
        }
        else if (cmd_sz == 3 && cmd_split[0] == "sell")
        {
            _handle_cmd_sell(cmd_split);
        }
        else
        {
            after_cmd_msg("Unknown command!", set_tem_color_red);
        }
    }
}

void
BrokerGame::_handle_cmd_buy(const std::vector<std::string>& cmd)
{
    if (cmd.size() != 3)
    {
        after_cmd_msg("USAGE: buy [id] [n]", set_tem_color_red);
        return;
    }

    inv_id_t id_to_buy;
    if (!parse<inv_id_t>(cmd[1], id_to_buy))
    {
        after_cmd_msg("ERROR: Invalid id", set_tem_color_red);
        return;
    }

    int n_to_buy;
    if (!parse<int>(cmd[2], n_to_buy))
    {
        after_cmd_msg("ERROR: Invalid number to buy", set_tem_color_red);
        return;
    }

    investment_ptr_t inv_to_buy = find_by_id(_market->get_available(),
                                             id_to_buy);

    if (n_to_buy + _fund->get_owned()[inv_to_buy] >= 1000)
    {
        after_cmd_msg("ERROR: You can not own more than 999 lots", 
                      set_tem_color_red);
        return;
    }

    if (_fund->buy(inv_to_buy, n_to_buy))
        after_cmd_msg("Purchase was a success!", set_tem_color_green);
    else
        after_cmd_msg("ERROR: Could not make such purchase!",
                       set_tem_color_red);

    _draw_owned();
    _draw_quick_stats();
    _draw_console();
}

void
BrokerGame::_handle_cmd_sell(const std::vector<std::string>& cmd)
{
    if (cmd.size() != 3)
    {
        after_cmd_msg("USAGE: sell [id] [n]", set_tem_color_red);
        return;
    }

    inv_id_t id_to_sell;
    if (!parse<inv_id_t>(cmd[1], id_to_sell))
    {
        after_cmd_msg("ERROR: Invalid id", set_tem_color_red);
        return;
    }

    int n_to_sell;
    if (!parse<int>(cmd[2], n_to_sell))
    {
        after_cmd_msg("ERROR: Invalid number to sell", set_tem_color_red);
        return;
    }

    investment_ptr_t inv_to_sell = find_by_id(_market->get_available(),
                                              id_to_sell);

    if (_fund->sell(inv_to_sell, n_to_sell, _tax_rate))
        after_cmd_msg("Sold successfully!", set_tem_color_green);
    else
        after_cmd_msg("ERROR: You don't own that!", set_tem_color_red);

    _draw_owned();
    _draw_quick_stats();
    _draw_console();
}

void
BrokerGame::after_cmd_msg(std::string msg, void color())
{
    // clear msg line
    set_cursor_pos(0, _cursor_pos.second + 1);
    std::cout << std::string(get_term_size().first, ' ');

    // write msg
    set_cursor_pos(0, _cursor_pos.second + 1);
    color();
    std::cout << msg;

    // clear console
    set_tem_color_default();
    set_cursor_pos(0, _cursor_pos.second);
    std::cout << std::string(get_term_size().first, ' ');
    std::cout << '\r' << "> ";
    _cursor_pos.first = 2;
    set_cursor_pos(_cursor_pos.first, _cursor_pos.second);
}

// TODO: Implement end screen
void
BrokerGame::end()
{

}

void
BrokerGame::_draw_easter()
{
    clear_terminal();
    char decimal[] = {
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,44,49,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,46,46,46,46,46,46,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,46,105,102,76,49,10,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,46,59,49,116,116,116,116,76,76,102,49,44,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,59,102,102,102,102,102,44,10,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,58,76,67,76,102,116,
116,102,76,76,76,76,76,58,32,32,32,32,32,32,32,32,32,32,32,32,32,32,44,116,102,
102,102,102,102,102,105,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,44,67,67,67,76,102,49,49,102,102,49,116,102,102,59,32,32,32,32,32,
32,32,32,32,32,32,32,44,49,76,102,102,102,102,102,102,102,102,46,10,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,105,76,116,116,116,49,49,105,
102,76,76,76,102,102,116,46,32,32,32,32,32,32,32,32,32,32,32,58,105,105,116,102,
102,102,102,102,102,76,105,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,59,116,49,49,49,49,105,105,49,102,102,102,102,102,49,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,102,102,102,102,102,116,59,105,49,46,10,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,44,49,105,105,105,105,
105,105,49,116,116,49,105,116,44,32,32,32,32,32,32,32,32,32,32,32,32,32,32,105,
102,102,102,102,102,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,59,49,105,59,59,59,59,105,49,116,102,102,58,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,46,102,102,102,102,102,49,10,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,44,116,49,105,105,59,58,58,58,59,105,59,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,105,102,102,102,102,102,44,10,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,44,59,49,49,105,105,
105,59,58,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,102,102,102,102,
102,49,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,46,44,44,46,44,44,
46,44,105,102,116,105,116,71,105,46,46,46,32,32,32,32,32,32,32,32,32,32,32,32,
32,105,102,102,102,102,102,44,10,32,32,32,32,32,32,32,32,32,32,32,32,46,44,44,
44,58,58,58,58,44,44,44,44,46,46,59,76,76,76,71,116,58,58,58,58,44,44,44,46,32,
32,32,32,32,32,32,46,102,102,102,102,102,49,10,32,32,32,32,32,32,32,32,32,32,32,
32,59,44,44,44,44,44,44,44,44,44,44,44,44,44,46,44,59,116,102,105,44,58,58,44,
44,58,58,58,58,44,32,32,32,32,32,59,102,102,102,102,102,44,10,32,32,32,32,32,32,
32,32,32,32,32,32,58,58,44,44,44,44,44,44,44,44,46,46,44,58,44,44,46,58,102,116,
44,58,58,44,44,58,44,44,58,58,46,32,32,32,46,102,102,102,102,102,49,10,32,32,32,
32,32,32,32,32,32,32,32,32,44,105,58,44,44,44,44,44,44,44,44,46,46,44,44,44,44,
44,44,59,44,58,58,58,44,58,44,44,44,58,58,32,32,32,59,102,102,102,102,102,44,10,
32,32,32,32,32,32,32,32,32,32,32,32,46,49,58,44,44,44,44,44,44,44,44,46,46,44,
44,44,58,44,44,44,58,58,44,44,44,58,44,44,44,44,58,44,32,46,102,102,102,102,102,
49,10,32,32,32,32,32,32,32,32,32,32,32,32,32,59,59,58,44,44,44,44,44,58,44,32,
46,46,44,44,44,58,58,44,44,44,58,44,44,58,44,44,44,44,58,58,46,44,49,116,102,
102,102,58,10,32,32,32,32,32,32,32,32,32,32,32,32,32,44,49,59,58,44,44,44,44,59,
102,58,46,44,44,44,44,44,44,58,44,46,46,44,44,58,44,46,46,44,44,58,58,44,32,32,
46,46,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,59,105,58,58,44,44,44,44,
44,58,44,44,58,44,44,58,44,58,58,58,44,44,44,59,49,58,44,46,44,44,44,58,44,10,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,59,59,59,58,44,44,44,44,44,44,44,
44,44,58,58,58,58,58,58,58,58,58,58,76,71,67,59,44,44,44,44,58,46,10,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,46,59,59,58,44,44,46,44,44,44,44,44,44,44,
44,44,44,44,44,44,44,58,58,58,59,59,58,44,44,44,44,44,58,41};

    for (int i = 0; i < 1228; ++i)
        std::cout << (char) decimal[i];

    std::cout << "\n\nPress ENTER to go back to the game...\n";
    getchar();
    draw_interface();
}
