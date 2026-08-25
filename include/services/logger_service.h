//
// Created by asus on 8/25/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_LOGGER_SERVICE_H
#define HOTELRESERVATIONSYSTEM_LOGGER_SERVICE_H

#include "models/logger.h"
#include <vector>
#include <string>

class LoggerService {

private:
    std::vector<std::unique_ptr<Logger>>logs;
public:
    void printLogs();
    void addLog(std::unique_ptr<Logger> log);
    std::string printLogTypes(LogMessageType log_type);
};


#endif //HOTELRESERVATIONSYSTEM_LOGGER_SERVICE_H