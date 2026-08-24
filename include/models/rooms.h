//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_ROOMS_H
#define HOTELRESERVATIONSYSTEM_ROOMS_H

#include "models/room_category.h"

// This is class is a room entity which conatins the propertites of rooms such as number , roomcategory ad its status
class Rooms {
private:
        int room_number;
        RoomCategory * room_category;
        bool room_status;
public:
        Rooms(int room_number,
        RoomCategory * room_category,
        bool room_status);
		RoomCategory* getRoomCategory();
};

#endif //HOTELRESERVATIONSYSTEM_ROOMS_H