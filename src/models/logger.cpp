//
// Created by asus on 8/25/2026.
//

#include "models/logger.h"
#include "enums/log_message_type.h"
#include <chrono>
    int Logger::getGuestId(){
        return guest_id;
    }
    int Logger::getReservationId(){
            return reservation_id;
    }
    LogMessageType Logger::getLogType(){
        return log_type;
    }
    std::chrono::system_clock::time_point Logger::getLogTimeStamp(){
        return timestamp;
    }

    Logger::Logger( int guest_id,
    int reservation_id,
    LogMessageType log_type){
        this->guest_id=guest_id,
        this->reservation_id=reservation_id,
        this->log_type=log_type,
        this->timestamp = std::chrono::system_clock::now();
    }