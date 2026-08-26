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
#include "services/logger_service.h"
#include <mutex>

class HotelService {

private:
        Hotel& hotel;
        AvailabilityIndex  availability_index;
        RoomCatlog room_catlog;
        LoggerService& loggerservice;
        std::mutex reservation_mutex;


public:
        HotelService(Hotel& hotel , LoggerService& loggerservice);

        void reserveRoom(int room_number,
        std::chrono::year_month_day check_in,
        std::chrono::year_month_day check_out);

		void cancelReservedRoom();
        Reservation* isValidReservationid(int reservation_id,std::vector<std::unique_ptr<Reservation>>& reservations);
        void setCheckInStatus();
        Room* findRoomByRoomNumber(int room_number,std::vector<std::unique_ptr<Room>>& rooms);
        void setCheckOutStatus();

        void addRoom();
        void deleteRoom();
        void generateReport();
        void CreateRoomCategoy();
        void searchRooms();
        std::chrono::year_month_day getChronoDateFormat(std::string& date);

};


#endif //HOTELRESERVATIONSYSTEM_HOTEL_SERVICE_H