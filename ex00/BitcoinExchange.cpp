#include "BitcoinExchange.hpp"
#include <cctype>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other)
        _db = other._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    for (std::size_t i = 0; i < date.size(); ++i) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    const int year = std::atoi(date.substr(0, 4).c_str());
    const int month = std::atoi(date.substr(5, 2).c_str());
    const int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    if (month == 2 && isLeapYear(year))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, double& value) const {
    char* end = NULL;

    value = std::strtod(valueStr.c_str(), &end);
    if (end == valueStr.c_str())
        return false;

    while (*end != '\0') {
        if (!std::isspace(static_cast<unsigned char>(*end)))
            return false;
        ++end;
    }

    return value >= 0.0 && value <= 1000.0;
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    (void)filename;
}

void BitcoinExchange::processInput(const std::string& filename) {
    (void)filename;
}
