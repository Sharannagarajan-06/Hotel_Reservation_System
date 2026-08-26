//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_Room_H
#define HOTELRESERVATIONSYSTEM_Room_H

#include "models/room_category.h"
#include <memory>

// This is class is a room entity which conatins the propertites of Room such as number , roomcategory ad its status
class Room {
private:
        inline static int next_room_number=1;
        int room_number;
        std::shared_ptr<RoomCategory> room_category;
        bool room_status;
public:
        Room(std::shared_ptr<RoomCategory> room_category);

		std::shared_ptr<RoomCategory> getRoomCategory();
        int getRoomNumber();
        bool getRoomStatus();
        void setRoomStatus(bool room_status);
};

#endif //HOTELRESERVATIONSYSTEM_Room_H