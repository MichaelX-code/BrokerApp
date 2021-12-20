#include "broker_game.h"

// Constructors:

BrokerGame::BrokerGame(size_t game_end, rubles default_fund_budget) :
_market(new Market()), _fund(new Fund(default_fund_budget)), _game_duration(0),
_game_end(game_end), _status(PLAYING)
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

void
BrokerGame::_draw_available()
{
    set_cursor_pos(0, 0);
    _cursor_row = 1;
    std::stringstream buffer;
    buffer << "   Investments available on the market:\n";
    buffer << table_header(); _cursor_row += 2;

    for (auto& investment : _market->get_available())
    {
        buffer << get_table_style_info(investment);
        ++_cursor_row;
    }

    std::cout << buffer.str();
    buffer.clear();
}

void
BrokerGame::_draw_owned()
{
    std::stringstream buffer;
    std::pair<int, int> term_size = get_term_size();
    if (term_size.first < 100)
    {
        if (_fund->get_owned().size() == 0)
        {
            std::cout << "\nYou don't own any investments at the moment\n";
            _cursor_row += 2;
            return;
        }

        std::cout << "\n           Investments you own:\n";

        std::cout << std::left
               << std::setw(2)  << "n"      << '|'
               << std::setw(3)  << "Id"     << '|'
               << std::setw(10) << "Type"   << '|'
               << std::setw(12) << "Name"   << '|'
               << std::setw(7)  << "Price"  << '|'
               << std::setw(6)  << "Profit" << '|'
               << std::setw(4)  << "Risk" << '\n';
        std::cout << std::string(2,  '-') << '+'
               << std::string(3,  '-') << '+'
               << std::string(10, '-') << '+'
               << std::string(12, '-') << '+'
               << std::string(7,  '-') << '+'
               << std::string(6,  '-') << '+'
               << std::string(4,  '-') << '\n';

        _cursor_row += 4;

        for (auto& inv: _fund->get_owned())
        {
            std::cout << get_table_style_info(inv.first, inv.second);
            ++_cursor_row;
        }
        
    }
    else
    {
        int cur_cursor_row = 0;
        int second_col = 50;
        set_cursor_pos(second_col, cur_cursor_row++);
        if (_fund->get_owned().size() == 0)
        {
            std::cout << "     You don't own any investments at the moment";
            set_cursor_pos(0, _cursor_row);
            return;
        }

        std::cout << "           Investments you own:";
        set_cursor_pos(second_col, cur_cursor_row++);

        std::cout << std::left
                  << std::setw(2)  << "n"      << '|'
                  << std::setw(3)  << "Id"     << '|'
                  << std::setw(10) << "Type"   << '|'
                  << std::setw(12) << "Name"   << '|'
                  << std::setw(7)  << "Price"  << '|'
                  << std::setw(6)  << "Profit" << '|'
                  << std::setw(4)  << "Risk";
        set_cursor_pos(second_col, cur_cursor_row++);
        std::cout << std::string(2,  '-') << '+'
                  << std::string(3,  '-') << '+'
                  << std::string(10, '-') << '+'
                  << std::string(12, '-') << '+'
                  << std::string(7,  '-') << '+'
                  << std::string(6,  '-') << '+'
                  << std::string(4,  '-');

        set_cursor_pos(second_col, cur_cursor_row++);

        for (auto& inv: _fund->get_owned())
        {
            std::cout << get_table_style_info(inv.first, inv.second);
            set_cursor_pos(second_col, cur_cursor_row++);
        }
        set_cursor_pos(0, _cursor_row);
    }

    std::cout << buffer.str();
    buffer.clear();
}

void
BrokerGame::_draw_stats()
{
    std::cout << "\nStats:\n";
    std::cout << "Current date: " << _market->get_date().get_formated() << '\n';
    std::cout << "Fund budget: " << _fund->get_budget() << "rub" << '\n';

    _cursor_row += 4;
}

void
BrokerGame::_draw_console()
{
    std::cout << "\nEnter a command (\"help\" to see all commands):\n";
    std::cout << "> ";
    _cursor_row += 2;
}

void
BrokerGame::draw_interface()
{
    clear_terminal();
    _draw_available();
    _draw_owned();
    _draw_stats();
    _draw_console();
}

void
BrokerGame::_draw_help()
{
    static list<std::pair<std::string, std::string>> commands_help = {
        { "help", "Opens this help menu" },
        { "next", "End turn and go to the next month" },
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
BrokerGame::get_command()
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
        else if (cmd_sz == 3 && cmd_split[0] == "buy")
        {
            inv_id_t id_to_buy = stoi(cmd_split[1]);
            int n_to_buy = stoi(cmd_split[2]);
            investment_ptr_t inv_to_buy = find_by_id(_market->get_available(),
                                                     id_to_buy);

            if (_fund->buy(inv_to_buy, n_to_buy))
                error_cmd_msg("Purchase was a success!", set_tem_color_green);
            else
                error_cmd_msg("Could make such purchase!", set_tem_color_red);

            draw_interface();
        }
        else if (cmd_sz == 3 && cmd_split[0] == "sell")
        {
            inv_id_t id_to_sell = stoi(cmd_split[1]);
            int n_to_sell = stoi(cmd_split[2]);
            investment_ptr_t inv_to_sell = find_by_id(_market->get_available(),
                                                      id_to_sell);

            if (_fund->sell(inv_to_sell, n_to_sell))
                error_cmd_msg("Sold successfully!", set_tem_color_green);
            else
                error_cmd_msg("You don't own that!", set_tem_color_red);

            draw_interface();
        }
        else
        {
            error_cmd_msg("Unknown command!", set_tem_color_red);
        }
    }
}

void
BrokerGame::error_cmd_msg(std::string msg, void color())
{
    // clear msg line
    set_cursor_pos(0, _cursor_row + 1);
    std::cout << std::string(get_term_size().first, ' ');

    // write msg
    set_cursor_pos(0, _cursor_row + 1);
    color();
    std::cout << msg;

    // clear console
    set_tem_color_default();
    set_cursor_pos(0, _cursor_row);
    std::cout << std::string(get_term_size().first, ' ');
    std::cout << '\r' << "> ";
}