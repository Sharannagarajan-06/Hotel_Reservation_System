//
// Created by asus on 8/24/2026.
//

#include "models/rooms.h"
#include "models/room_category.h"

// This file is the implementation of the declerations in the file named rooms.h

Room::Room(std::shared_ptr<RoomCategory> room_category){
        this->room_number=next_room_number++;
        this->room_category=room_category;
        this->room_status=false;
}
std::shared_ptr<RoomCategory> Room::getRoomCategory() {
    return this->room_category;
}

bool Room::getRoomStatus(){
    return this->room_status;
}

void Room::setRoomStatus(bool room_status){
    this->room_status=room_status;
}


int Room::getRoomNumber(){
    return this->room_number;
}