//
// Created by asus on 8/25/2026.
//

#include "services/logger_service.h"
#include "enums/log_message_type.h"
#include <iostream>
#include <string>


std::string LoggerService::printLogTypes(LogMessageType log_type){

       switch(log_type){

        case LogMessageType::BOOKING:
                return "BOOKING";
                   break;
        case LogMessageType::CANCELLATION:
                return "CANCELLATION";
                break;
         case LogMessageType::CHECK_IN:
                return "CHECK_IN";
                break;
         case LogMessageType::CHECK_OUT:
                return "CHECK_OUT";
                break;
         case LogMessageType::BILLING:
                return "BILLING";
                break;
         default:
               std::cout<<"Invalid category\n";
               return "";
        }
    return "";
}
void LoggerService::printLogs(){
        for(auto log:logs){
                std::cout<<"Guest Id:"<<log->getGuestId()<<std::endl;
                std::cout<<"Reservation Id:"<<log->getReservationId()<<std::endl;
                std::cout<<"Log Type:"<<printLogTypes(log->getLogType())<<std::endl;
                std::cout<<"Timestamp:"<<log->getLogTimeStamp()<<std::endl;
        }
}

void LoggerService::addLog(Logger* log){
        logs.push_back(log);
}