//
// Created by asus on 8/24/2026.
//

#include "models/room_category.h"
#include "enums/room_name.h"

// This is file is the implementation of the declerations in the file room_category.h
    RoomCategory::RoomCategory( RoomNames room_name,int  room_capacity,int  room_base_rate){
            this->room_name=room_name;
            this->room_capacity=room_capacity;
            this->room_base_rate=room_base_rate;
        }
    void RoomCategory::setRoomName(RoomNames room_name){
        this->room_name=room_name;
    }
    void RoomCategory::setRoomCapacity(int room_capacity){
        this->room_capacity=room_capacity;
    }
    int RoomCategory:: getRoomCapacity(){
        return this->room_capacity;
    }
    void RoomCategory::setRoomBaseRate(int room_base_rate){
        this->room_capacity=room_capacity;
    }
    int RoomCategory::getRoomBaseRate(){
        return this->room_base_rate;
    }