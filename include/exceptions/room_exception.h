#ifndef HOTELRESERVATIONSYSTEM_ROOM_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_ROOM_EXCEPTION_H

#include "exceptions/hotel_exception.h"

/* This is an RoomException class dervied from the hotel exception it has various exceptions
    related to RoomException */

class RoomException:public HotelException {
public:
    explicit RoomException(const std::string& message)
        : HotelException(message) {
    }

    ~RoomException()override = default;
};

class RoomUnavailableException:public RoomException {
public:
    explicit RoomUnavailableException(const std::string& message)
        : RoomException(message) {
    }

    ~RoomUnavailableException() override = default;
};

class RoomNotFoundException:public RoomException {
public:
    explicit RoomNotFoundException(const std::string& message)
        : RoomException(message) {}

    ~RoomNotFoundException()override = default;
};

class RoomOccupiedException:public RoomException {
public:
    explicit RoomOccupiedException(const std::string& message)
        : RoomException(message) {}

    ~RoomOccupiedException()override = default;
};
class InvalidRoomCategoryException : public HotelException
{
public:
    explicit InvalidRoomCategoryException(const std::string& message)
        : HotelException(message)
    {
    }

    const char* what() const noexcept override
    {
        return "Invalid room category";
    }
};

#endif