//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_HOTEL_SERVICE_H
#define HOTELRESERVATIONSYSTEM_HOTEL_SERVICE_H

#include "models/reservation.h"
#include "models/hotel.h"
#include "models/availabilityindex.h"
#include "models/room_category.h"
#include "models/room_catlog.h"
class HotelService {

private:
        Hotel& hotel;
        AvailabilityIndex  availability_index;
        RoomCatlog room_catlog;


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

        void addRoom();
        void deleteRoom();
        void generateReport();
        void CreateRoomCategoy();

};


#endif //HOTELRESERVATIONSYSTEM_HOTEL_SERVICE_H