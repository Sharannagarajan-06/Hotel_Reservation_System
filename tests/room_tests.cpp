#include <gtest/gtest.h>
#include <memory>

#include "models/rooms.h"
#include "models/room_category.h"
#include "enums/room_name.h"

class RoomTest : public ::testing::Test
{
protected:
    std::shared_ptr<RoomCategory> category;
    std::unique_ptr<Room> room;

    void SetUp() override
    {
        category = std::make_shared<RoomCategory>(
            RoomNames::STANDARD,
            2,
            2000);
        room = std::make_unique<Room>(category);
    }
};

TEST_F(RoomTest, RoomCreatedSuccessfully)
{
    EXPECT_NO_THROW({
        Room room(category);
    });
}

TEST_F(RoomTest, RoomHasValidRoomNumber)
{
    Room room(category);
    EXPECT_GT(room.getRoomNumber(), 0);
}

TEST_F(RoomTest, RoomNumbersAreUnique)
{
    Room room1(category);
    Room room2(category);
    EXPECT_NE(
        room1.getRoomNumber(),
        room2.getRoomNumber());
}

TEST_F(RoomTest, RoomStoresCorrectCategory)
{
    Room room(category);
    EXPECT_EQ(
        room.getRoomCategory(),
        category);
}

TEST_F(RoomTest, RoomInitiallyAvailable)
{
    Room room(category);
    EXPECT_FALSE(
        room.getRoomStatus());
}

TEST_F(RoomTest, RoomCanBeMarkedOccupied)
{
    Room room(category);
    room.setRoomStatus(true);
    EXPECT_TRUE(
        room.getRoomStatus());
}

TEST_F(RoomTest, RoomCanBeMarkedAvailable)
{
    Room room(category);
    room.setRoomStatus(true);
    room.setRoomStatus(false);
    EXPECT_FALSE(
        room.getRoomStatus());
}

TEST_F(RoomTest, MultipleRoomsCanUseSameCategory)
{
    Room room1(category);
    Room room2(category);
    EXPECT_EQ(
        room1.getRoomCategory(),
        room2.getRoomCategory());
}

TEST_F(RoomTest, ChangingOneRoomStatusDoesNotChangeAnother)
{
    Room room1(category);
    Room room2(category);
    room1.setRoomStatus(true);
    EXPECT_TRUE(room1.getRoomStatus());
    EXPECT_FALSE(room2.getRoomStatus());
}