#include "broker_game.h"

// Constructors:

BrokerGame::BrokerGame(size_t game_end) :
_market(new Market()), _fund(new Fund()), _game_duration(0),
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
            return;
        }

        buffer << "\n           Investments you own:\n";
        buffer << table_header();

        for (auto& investment : _fund->get_owned())
            buffer << get_table_style_info(investment, 1);
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
                  << std::setw(10) << "Type"   << '|'
                  << std::setw(12) << "Name"   << '|'
                  << std::setw(7)  << "Price"  << '|'
                  << std::setw(6)  << "Profit" << '|'
                  << std::setw(4)  << "Risk";
        set_cursor_pos(second_col, cur_cursor_row++);
        std::cout << std::string(2,  '-') << '+'
                  << std::string(10, '-') << '+'
                  << std::string(12, '-') << '+'
                  << std::string(7,  '-') << '+'
                  << std::string(6,  '-') << '+'
                  << std::string(4,  '-');

        set_cursor_pos(second_col, cur_cursor_row++);

        for (auto& investment : _fund->get_owned())
        {
            std::cout << get_table_style_info(investment, 1);
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
            return;
        }
        else if (cmd_sz == 3 && cmd_split[0] == "buy")
        {
            inv_id_t id_to_buy = stoi(cmd_split[1]);
            int n_to_buy [[maybe_unused]] = stoi(cmd_split[2]);
            investment_ptr_t inv_to_buy = find_by_id(_market->get_available(),
                                                     id_to_buy);
            _fund->buy(inv_to_buy);
            draw_interface();
        }
        else if (cmd_sz == 3 && cmd_split[0] == "sell")
        {
            inv_id_t id_to_sell = stoi(cmd_split[1]);
            int n_to_sell [[maybe_unused]] = stoi(cmd_split[2]);
            investment_ptr_t inv_to_sell = find_by_id(_market->get_available(),
                                                      id_to_sell);
            _fund->sell(inv_to_sell);
            draw_interface();
        }
        else
        {
            set_cursor_pos(0, _cursor_row + 1);
            set_tem_color_red();
            std::cout << "Unknown command!";
            set_tem_color_default();
            set_cursor_pos(0, _cursor_row);
            std::cout << std::string(get_term_size().first, ' ');
            std::cout << '\r' << "> ";
        }
    }
}