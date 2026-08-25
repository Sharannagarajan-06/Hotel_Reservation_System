//
// Created by asus on 8/25/2026.
//

#include "models/room_catlog.h"
#include "models/room_category.h"
#include "enums/room_name.h"


RoomCatlog::RoomCatlog() {
    categories.emplace(
        RoomNames::STANDARD,
        RoomCategory(RoomNames::STANDARD, 1000, 2)
    );

    categories.emplace(
        RoomNames::DELUXE,
        RoomCategory(RoomNames::DELUXE, 3000, 3)
    );

    categories.emplace(
        RoomNames::SUITE,
        RoomCategory(RoomNames::SUITE, 4000, 4)
    );
}

RoomCategory& RoomCatlog::getCategory(RoomNames name){
    return categories.at(name);
}