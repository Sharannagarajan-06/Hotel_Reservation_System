#ifndef HOTELRESERVATIONSYSTEM_DATE_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_DATE_EXCEPTION_H

#include <string>
#include "exceptions/hotel_exception.h"

/* This is an DateException class dervied from the hotel exception it has various exceptions
    related to Date it arises when the date provided by the user is not in the preferred format*/


class DateException : public HotelException {
public:
    explicit DateException(const std::string& message)
        : HotelException(message) {
    }

    ~DateException() override = default;
};

class InvalidDateException : public HotelException {
public:
    explicit InvalidDateException(const std::string& message)
        : HotelException(message) {
    }

    ~InvalidDateException() override = default;
};

#endif