
#include "interface.h"
#include <string.h>
#include <iostream>
using namespace std;

// Check the validity of the specified date. The format of a date is: YYYY-MM-DD.
void validityCheck(string date) {
    // General validy checks of the format.
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        throw std::invalid_argument("The specified date is not valid. The format of a date is: YYYY-MM-DD.");
    }
    // Validity check of the year.
    for (int i = 0; i < 4; i++) {
        if (date[i] - '0' < 0 || date[i] - '0' > 9) {
            throw std::invalid_argument("The specified date is not valid. The format of a date is: YYYY-MM-DD.");
        }
    }
    // Validity check of the month.
    if (date[5] - '0' < 0 || date[5] - '0' > 1 || date[6] - '0' < 0 || date[6] - '0' > 9) {
        throw std::invalid_argument("The specified date is not valid. The format of a date is: YYYY-MM-DD.");
    }
    int month = stoi(date.substr(5, 2));
    if (month < 1 || month > 12) {
        throw std::invalid_argument("The specified date is not valid. The format of a date is: YYYY-MM-DD.");
    }
    // Validity check of the day.
    if (date[8] - '0' < 0 || date[8] - '0' > 3 || date[9] - '0' < 0 || date[9] - '0' > 9) {
        throw std::invalid_argument("The specified date is not valid. The format of a date is: YYYY-MM-DD.");
    }
    int day = stoi(date.substr(8, 2));
    if (day < 1 || day > 31) {
        throw std::invalid_argument("The specified date is not valid. The format of a date is: YYYY-MM-DD.");
    }
}

Date:: Date(string date) {
    validityCheck(date);
    this->date = date;
}

// Return true if the current date is smaller than the given date, otherwise return false.
bool Date::operator<(const Date& d) const {
    if (date.length() != 10) {
        throw std::invalid_argument("Invalid argument.");
    }
    int currentNumber;
    int otherNumber;
    bool areEquael = true;
    for (int i = 0; i < date.length(); i++) {
        // Convert the characters to integers.
        currentNumber = date[0] - '0';
        otherNumber = d.getDate()[0] - '0';
        if (otherNumber < currentNumber) {
            return false;
        }
        if (otherNumber > currentNumber) {
            areEquael = false;
        }
    }
    if (!areEquael) {
        return true;
    }
    else {
        return false;
    }
}

// Return true if the current date and the given date are equal, otherwise return false.
bool Date::operator==(const Date& d) const {
    int currentNumber;
    int otherNumber;
    for (int i = 0; i < date.length(); i++) {
        // Convert the characters to integers.
        currentNumber = date[0] - '0';
        otherNumber = d.getDate()[0] - '0';
        if (currentNumber != otherNumber) {
            return false;
        }
    }
    return true;
}

// Return true if the current date is bigger than the given date, otherwise return false.
bool Date::operator>(const Date& d) const {
    return !(*this == d || *this < d);
}