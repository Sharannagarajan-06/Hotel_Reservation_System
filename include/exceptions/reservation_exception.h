#ifndef HOTELRESERVATIONSYSTEM_RESERVATION_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_RESERVATION_EXCEPTION_H

#include "exceptions/hotel_exception.h"

/* This is an ReservationException class dervied from the hotel exception it has various exceptions
    related to Reservation */



class ReservationException:public HotelException {
public:
    explicit ReservationException(const std::string& message)
        : HotelException(message) {}

    ~ReservationException()override=default;
};



class InvalidReservationException:public ReservationException {
public:
    explicit InvalidReservationException
(const std::string& message)
        : ReservationException(message) {}

    ~InvalidReservationException()override=default;
};



class ReservationNotFoundException:public ReservationException {
public:
    explicit ReservationNotFoundException(const std::string& message)
        : ReservationException(message) {}

    ~ReservationNotFoundException()override =default;
};



class ReservationConflictException : public ReservationException {
public:
    explicit ReservationConflictException
(const std::string& message): ReservationException(message) {}

    ~ReservationConflictException()override= default;
};

#endif