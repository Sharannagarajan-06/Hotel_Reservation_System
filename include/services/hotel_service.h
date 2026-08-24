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

		void cancelReservedRoom(int reservation_id);
        Reservation* isValidReservationid(int reservation_id,std::vector<Reservation*>& reservations);
        void setCheckInStatus(int reservation_id);
        Room* findRoomByRoomNumber(int room_number,std::vector<Room*>Rooms);
        void setCheckOutStatus(int reservation_id);

};


#endif //HOTELRESERVATIONSYSTEM_HOTEL_SERVICE_H