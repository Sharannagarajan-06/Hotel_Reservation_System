//
// Created by asus on 8/26/2026.
//

#include <gtest/gtest.h>
#include <memory>
#include <chrono>
#include "services/hotel_service.h"
#include "services/logger_service.h"
#include "models/hotel.h"
#include "models/guest_details.h"
#include "models/rooms.h"
#include "models/room_category.h"
#include "enums/reservation_status.h"
#include "exceptions/reservation_exception.h"
#include "exceptions/room_exception.h"
#include "models/reservation.h"

class HotelServiceTest : public ::testing::Test
{
protected:
    Hotel hotel;
    LoggerService loggerService;
    std::unique_ptr<HotelService> hotelService;

    std::chrono::year_month_day checkIn{
        std::chrono::year{2026},
        std::chrono::month{9},
        std::chrono::day{10}};

    std::chrono::year_month_day checkOut{
        std::chrono::year{2026},
        std::chrono::month{12},
        std::chrono::day{10}};

    void SetUp() override
    {
        hotelService = std::make_unique<HotelService>(
            hotel,
            loggerService);
    }
    Room *addRoom()
    {
        auto category = std::make_shared<RoomCategory>(
            RoomNames::STANDARD,
            2,
            1000);
        auto room = std::make_unique<Room>(category);
        Room *roomPtr = room.get();
        hotel.addRoom(std::move(room));
        return roomPtr;
    }
    GuestDetails *addGuest()
    {
        auto guest = std::make_unique<GuestDetails>(
            "Sharan",
            "9876543210",
            "sharan@gmail.com");
        GuestDetails *guestPtr = guest.get();
        hotel.adduser(std::move(guest));
        return guestPtr;
    }
    Reservation *addReservation(
        int roomNumber,
        int userId)
    {
        auto reservation = std::make_unique<Reservation>(
            checkIn,
            checkOut,
            roomNumber,
            userId);
        Reservation *reservationPtr = reservation.get();
        hotel.addReservation(std::move(reservation));

        return reservationPtr;
    }
};

TEST_F(HotelServiceTest, FindsValidReservation)
{
    Room *room = addRoom();
    GuestDetails *guest = addGuest();
    Reservation *reservation = addReservation(
        room->getRoomNumber(),
        guest->getUserId());
    auto &reservations = hotel.getReservations();
    Reservation *result =
        hotelService->isValidReservationid(
            reservation->getReservationId(),
            reservations);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(
        result->getReservationId(),
        reservation->getReservationId());
}

TEST_F(HotelServiceTest, InvalidReservationIdReturnsNull)
{
    auto &reservations = hotel.getReservations();
    Reservation *result =
        hotelService->isValidReservationid(
            99999,
            reservations);
    EXPECT_EQ(result, nullptr);
}

TEST_F(HotelServiceTest, FindsExistingRoom)
{
    Room *room = addRoom();
    auto &rooms = hotel.getRooms();
    Room *result =
        hotelService->findRoomByRoomNumber(
            room->getRoomNumber(),
            rooms);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(
        result->getRoomNumber(),
        room->getRoomNumber());
}

TEST_F(HotelServiceTest, InvalidRoomNumberReturnsNull)
{
    addRoom();

    auto &rooms = hotel.getRooms();

    Room *result =
        hotelService->findRoomByRoomNumber(
            99999,
            rooms);
    EXPECT_EQ(result, nullptr);
}

TEST_F(HotelServiceTest, ReservationInitiallyReserved)
{
    Room *room = addRoom();
    GuestDetails *guest = addGuest();
    Reservation *reservation = addReservation(
        room->getRoomNumber(),
        guest->getUserId());
    EXPECT_EQ(
        reservation->getReservationStatus(),
        ReservationStatus::RESERVED);
}

TEST_F(HotelServiceTest, ReservationCanBeMarkedCheckedIn)
{
    Room *room = addRoom();
    GuestDetails *guest = addGuest();
    Reservation *reservation = addReservation(
        room->getRoomNumber(),
        guest->getUserId());
    reservation->setReservationStatus(
        ReservationStatus::CHECKED_IN);
    room->setRoomStatus(true);
    EXPECT_EQ(
        reservation->getReservationStatus(),
        ReservationStatus::CHECKED_IN);
    EXPECT_TRUE(room->getRoomStatus());
}

TEST_F(HotelServiceTest, ReservationCanBeCancelled)
{
    Room *room = addRoom();
    GuestDetails *guest = addGuest();
    Reservation *reservation = addReservation(
        room->getRoomNumber(),
        guest->getUserId());
    reservation->setReservationStatus(
        ReservationStatus::CANCELLED);
    EXPECT_EQ(
        reservation->getReservationStatus(),
        ReservationStatus::CANCELLED);
}

TEST_F(HotelServiceTest, ReservationCanBeCheckedOut)
{
    Room *room = addRoom();
    GuestDetails *guest = addGuest();
    Reservation *reservation = addReservation(
        room->getRoomNumber(),
        guest->getUserId());
    room->setRoomStatus(true);
    reservation->setReservationStatus(
        ReservationStatus::CHECKED_OUT);
    room->setRoomStatus(false);
    EXPECT_EQ(
        reservation->getReservationStatus(),
        ReservationStatus::CHECKED_OUT);
    EXPECT_FALSE(room->getRoomStatus());
}

TEST_F(HotelServiceTest, RoomStatusChangesIndependently)
{
    Room *room1 = addRoom();
    Room *room2 = addRoom();
    room1->setRoomStatus(true);
    EXPECT_TRUE(room1->getRoomStatus());
    EXPECT_FALSE(room2->getRoomStatus());
}

TEST_F(HotelServiceTest, ReservationStoresCorrectRoomAndUser)
{
    Room *room = addRoom();
    GuestDetails *guest = addGuest();
    Reservation *reservation = addReservation(
        room->getRoomNumber(),
        guest->getUserId());
    EXPECT_EQ(
        reservation->getRoomNumber(),
        room->getRoomNumber());
    EXPECT_EQ(
        reservation->getUserId(),
        guest->getUserId());
}
