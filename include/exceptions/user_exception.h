#ifndef HOTELRESERVATIONSYSTEM_USER_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_USER_EXCEPTION_H

#include "exceptions/hotel_exception.h"

/* This is an UserException class dervied from the hotel exception it has various exceptions
    related to User */



class UserException : public HotelException {
public:
    explicit UserException(const std::string& message)
        : HotelException(message) {
    }

    ~UserException() override = default;
};

class UserNotFoundException : public UserException {
public:
    explicit UserNotFoundException(const std::string& message)
        : UserException(message) {
    }

    ~UserNotFoundException() override = default;
};

class UnauthorizedException : public UserException {
public:
    explicit UnauthorizedException(const std::string& message)
        : UserException(message) {
    }

    ~UnauthorizedException() override = default;
};

class AuthenticationException : public UserException {
public:
    explicit AuthenticationException(const std::string& message)
        : UserException(message) {
    }

    ~AuthenticationException() override = default;
};

class AuthenticationFailedException : public AuthenticationException {
public:
    explicit AuthenticationFailedException(const std::string& message)
        : AuthenticationException(message) {
    }

    ~AuthenticationFailedException() override = default;
};

#endif