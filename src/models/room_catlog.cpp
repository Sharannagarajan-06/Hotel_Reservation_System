//
// Created by asus on 8/25/2026.
//

#include "models/room_catlog.h"
#include "models/room_category.h"
#include "enums/room_name.h"
#include <memory>

RoomCatlog::RoomCatlog()
{
    categories.emplace(
        RoomNames::STANDARD,
        std::make_shared<RoomCategory>(RoomNames::STANDARD, 2, 2000));

    categories.emplace(
        RoomNames::DELUXE,
        std::make_shared<RoomCategory>(RoomNames::DELUXE, 3, 3000));

    categories.emplace(
        RoomNames::SUITE,
        std::make_shared<RoomCategory>(RoomNames::SUITE, 4, 4000));
}

std::shared_ptr<RoomCategory> RoomCatlog::getCategory(RoomNames name)
{
    return categories.at(name);
}