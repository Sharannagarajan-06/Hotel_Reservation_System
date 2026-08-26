#ifndef HOTELRESERVATIONSYSTEM_DATE_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_DATE_EXCEPTION_H

#include <string>
#include "exceptions/hotel_exception.h"

class DateException : public HotelException {
public:
    explicit DateException(const std::string& message)
        : HotelException(message) {
    }

    ~DateException() override = default;
};

#endif