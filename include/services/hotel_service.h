//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_HOTEL_SERVICE_H
#define HOTELRESERVATIONSYSTEM_HOTEL_SERVICE_H

#include "models/reservation.h"
#include "models/hotel.h"
#include "models/availabilityindex.h"

class HotelService {

private:
        Hotel& hotel;
        AvailabilityIndex  availability_index;
public:
        HotelService(Hotel& hotel);

        void reserveRoom(RoomNames room_names,
        std::chrono::year_month_day check_in,
        std::chrono::year_month_day check_out);

};


#endif //HOTELRESERVATIONSYSTEM_HOTEL_SERVICE_H