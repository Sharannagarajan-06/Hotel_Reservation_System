//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_ROOM_CATEGORY_H
#define HOTELRESERVATIONSYSTEM_ROOM_CATEGORY_H

/* This is a RoomCategory Class which has details about all the each category rooms's price and capacity */

#include "enums/room_name.h"

class RoomCategory {
private:
       RoomNames room_name;
       int  room_capacity;
       int  room_base_rate;
public:
        /*Constructor for setting values of the Class*/
       RoomCategory( RoomNames room_name, int  room_capacity, int  room_base_rate);

        //Getters and setters for RoomName
       void setRoomName(RoomNames room_name);
       RoomNames getRoomName();

        //Getters and setters for Room capacity
       void setRoomCapacity(int room_capacity);
       int getRoomCapacity();

        //Getters and setters for Room Base rate
       void setRoomBaseRate(int room_base_rate);
       int getRoomBaseRate();

};


#endif //HOTELRESERVATIONSYSTEM_ROOM_CATEGORY_H