//
// Created by asus on 8/25/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_LOGGER_H
#define HOTELRESERVATIONSYSTEM_LOGGER_H

#include "enums/log_message_type.h"
#include <iostream>
#include <chrono>

/*
    the logger class is used to act as a log msg templeate for the log msg service it includes the
    guest id, reservation id , log type and timestamp
*/

class Logger {

private:
    int guest_id;
    int reservation_id;
    LogMessageType log_type;
    std::chrono::system_clock::time_point timestamp;
public:
    Logger( int guest_id,
    int reservation_id,
    LogMessageType log_type);

    int getGuestId();
    int getReservationId();
    LogMessageType getLogType();
    std::chrono::system_clock::time_point getLogTimeStamp();

};


#endif //HOTELRESERVATIONSYSTEM_LOGGER_H