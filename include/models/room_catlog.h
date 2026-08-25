//
// Created by asus on 8/25/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_ROOM_CATLOG_H
#define HOTELRESERVATIONSYSTEM_ROOM_CATLOG_H
#include "models/room_category.h"
#include "enums/room_name.h"
#include <map>

class RoomCatlog {
private:
    std::map<RoomNames,RoomCategory>categories;

public:
    RoomCatlog();

    RoomCategory& getCategory(RoomNames name);
};


#endif //HOTELRESERVATIONSYSTEM_ROOM_CATLOG_H