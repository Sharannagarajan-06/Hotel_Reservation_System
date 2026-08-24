//
// Created by asus on 8/24/2026.
//

#include "models/rooms.h"
#include "models/room_category.h"

// This file is the implementation of the declerations in the file named rooms.h

Rooms::Rooms(int room_number, RoomCategory* room_category, bool room_status){
        this->room_number=room_number;
        this->room_category=room_category;
        this->room_status=room_status;
}
RoomCategory* Rooms::getRoomCategory() {
    return room_category;
}