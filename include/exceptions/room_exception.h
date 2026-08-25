#ifndef HOTELRESERVATIONSYSTEM_ROOM_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_ROOM_EXCEPTION_H

#include "exceptions/hotel_exception.h"

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

#endif