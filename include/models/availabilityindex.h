//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_AVAILABILITYINDEX_H
#define HOTELRESERVATIONSYSTEM_AVAILABILITYINDEX_H

#include <map>
#include <chrono>
#include <set>
class AvailabilityIndex {

private:
    //map<roomId, set< checkIn , checkOut >>
    std::map<int,std::set<std::pair<std::chrono::year_month_day,std::chrono::year_month_day>>>availability;

public:

    bool isFree(
    int roomId,
    std::chrono::year_month_day checkIn,
    std::chrono::year_month_day checkOut);

    void updateAvailability( int roomId,
    std::chrono::year_month_day checkIn,
    std::chrono::year_month_day checkOut);

};


#endif //HOTELRESERVATIONSYSTEM_AVAILABILITYINDEX_H