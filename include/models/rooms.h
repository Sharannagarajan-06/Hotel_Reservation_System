//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_Room_H
#define HOTELRESERVATIONSYSTEM_Room_H

#include "models/room_category.h"

// This is class is a room entity which conatins the propertites of Room such as number , roomcategory ad its status
class Room {
private:
        int room_number;
        RoomCategory * room_category;
        bool room_status;
public:
        Room(int room_number,
        RoomCategory * room_category,
        bool room_status);
		RoomCategory* getRoomCategory();
        int getRoomNumber();
};

#endif //HOTELRESERVATIONSYSTEM_Room_H