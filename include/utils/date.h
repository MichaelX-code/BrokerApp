#ifndef BROKERAPP_UTILS_DATE_H
#define BROKERAPP_UTILS_DATE_H

#include "utils.h"

class date_t
{
public:
    // Constructors:
    date_t();
    date_t(const std::string& date);

    // Functions: selectors (get)
    unsigned get_day() const noexcept;
    unsigned get_month() const noexcept;
    unsigned get_year() const noexcept;
    std::string get_formated() const;

    // Functions: modifiers (set)
    void set_day(unsigned day);
    void set_month(unsigned month);
    void set_year(unsigned year);

    // Operators overloads:
    friend bool operator < (const date_t &a, const date_t &b);
    friend bool operator > (const date_t &a, const date_t &b);
    friend bool operator <= (const date_t &a, const date_t &b);
    friend bool operator >= (const date_t &a, const date_t &b);
    friend bool operator == (const date_t &a, const date_t &b);
    friend bool operator != (const date_t &a, const date_t &b);

private:
    // Members:
    unsigned _year, _month, _day;

    // Helpful private methods:
    inline bool _check_valid() const;
    static inline unsigned _end_of_month(unsigned int m, unsigned int y);
    static inline bool _is_leap(unsigned int y);
};

#endif // BROKERAPP_UTILS_DATE_H