#include "date.h"

// Default constructor sets current date (local)
date_t::date_t()
{
    std::time_t cur_time = std::time(NULL);
    std::tm* local_time = std::localtime(&cur_time);

    this->_day = 1;
    this->_month = local_time->tm_mon + 1;
    this->_year = local_time->tm_year + 1900;

    // if date is not correct, throw an error
    if (!_check_valid())
        throw std::invalid_argument("ERROR: Impossible date");
}

// Construct out of string "dd?mm?yyyy"
date_t::date_t(const std::string& date)
{
    if (date.length() != 10)
        throw std::invalid_argument("ERROR: Wrong date format");

    this->_day   = std::stoi(date.substr(0, 2));
    this->_month = std::stoi(date.substr(3, 2));
    this->_year  = std::stoi(date.substr(6, 4));

    // if date is not correct, throw an error
    if (!_check_valid())
        throw std::invalid_argument("ERROR: Impossible date");
}

unsigned
date_t::get_day()
const noexcept
{
   return this->_day;
}

unsigned
date_t::get_month()
const noexcept
{
    return this->_month;
}

unsigned
date_t::get_year()
const noexcept
{
    return this->_year;
}

std::string
date_t::get_formated()
const
{
    std::string day = (this->_day < 10 ? "0" : "");
    day += std::to_string(this->_day);

    std::string month = (this->_month < 10 ? "0" : "");
    month += std::to_string(this->_month);

    return day + '.' + month + '.' + std::to_string(this->_year);
}

void
date_t::set_day(unsigned day)
{
    if (day <= _end_of_month(_month, _year) && day != 0)
        this->_day = day;
    else
        throw std::invalid_argument("Impossible date or wrong format");
}

void
date_t::set_month(unsigned month)
{
    if (_day <= _end_of_month(month, _year))
        this->_month = month;
    else
        throw std::invalid_argument("Impossible date or wrong format");
}

void
date_t::set_year(unsigned year)
{
    if (_day <= _end_of_month(_month, year))
        this->_year = year;
    else
        throw std::invalid_argument("Impossible date or wrong format");
}

bool
operator < (const date_t &a, const date_t &b)
{
    return ((a._year < b._year) ||
            (a._year == b._year && a._month < b._month) ||
            (a._year == b._year && a._month == b._month && a._day < b._day));
}

bool
operator > (const date_t &a, const date_t &b)
{
    return (b < a);
}

bool
operator <= (const date_t &a, const date_t &b)
{
    return !(a > b);
}

bool
operator >= (const date_t &a, const date_t &b)
{
    return !(a < b);
}

bool
operator == (const date_t &a, const date_t &b)
{
    return (a._year == b._year && a._month == b._month && a._day == b._day);
}

bool
operator != (const date_t &a, const date_t &b)
{
    return !(a == b);
}

inline bool
date_t::_check_valid()
const
{
    return (_month <= 12 && _day <= _end_of_month(_month, _year));
}

inline unsigned
date_t::_end_of_month(unsigned int month, unsigned int year)
{
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (_is_leap(year) ? 29 : 28);
        default: return 0;
    }
}

inline bool
date_t::_is_leap(unsigned int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}