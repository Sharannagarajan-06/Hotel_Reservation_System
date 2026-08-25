#ifndef HOTELRESERVATIONSYSTEM_HOTEL_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_HOTEL_EXCEPTION_H

#include <exception>
#include <string>

class HotelException : public std::exception {
private:
    std::string message;

public:
    explicit HotelException(const std::string& message)
        : message(message) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

    ~HotelException() override = default;
};

#endif