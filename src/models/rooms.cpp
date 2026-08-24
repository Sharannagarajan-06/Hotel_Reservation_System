//
// Created by asus on 8/24/2026.
//

#include "models/rooms.h"
#include "models/room_category.h"

// This file is the implementation of the declerations in the file named rooms.h

Room::Room(int room_number, RoomCategory* room_category){
        this->room_number=room_number;
        this->room_category=room_category;
        this->room_status=false;
}
RoomCategory* Room::getRoomCategory() {
    return this->room_category;
}

bool Room::getRoomStatus(){
    return this->room_status;
}

void Room::setRoomStatus(){
    this->room_status=true;
}


int Room::getRoomNumber(){
    return this->room_number;
}