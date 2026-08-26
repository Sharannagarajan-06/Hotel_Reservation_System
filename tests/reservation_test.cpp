#include <gtest/gtest.h>
#include <chrono>
#include "models/reservation.h"
#include "enums/reservation_status.h"
#include "exceptions/reservation_exception.h"

class ReservationTest : public ::testing::Test
{

protected:
    std::chrono::year_month_day checkIn{
        std::chrono::year{2026},
        std::chrono::month{8},
        std::chrono::day{25}};

    std::chrono::year_month_day checkOut{
        std::chrono::year{2026},
        std::chrono::month{8},
        std::chrono::day{28}};

    int roomNumber = 101;
    int userId = 1;
};

TEST_F(ReservationTest, CreateReservationSuccessfully)
{
    EXPECT_NO_THROW({
        Reservation reservation(
            checkIn,
            checkOut,
            roomNumber,
            userId);
    });
}

TEST_F(ReservationTest, StoresCorrectRoomNumber)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);
    EXPECT_EQ(
        reservation.getRoomNumber(),
        roomNumber);
}

TEST_F(ReservationTest, StoresCorrectUserId)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);
    EXPECT_EQ(
        reservation.getUserId(),
        userId);
}

TEST_F(ReservationTest, StoresCorrectCheckInDate)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);

    EXPECT_EQ(
        reservation.getCheckIn(),
        checkIn);
}

TEST_F(ReservationTest, StoresCorrectCheckOutDate)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);
    EXPECT_EQ(
        reservation.getCheckOut(),
        checkOut);
}

TEST_F(ReservationTest, InitialStatusShouldBeReserved)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);
    EXPECT_EQ(
        reservation.getReservationStatus(),
        ReservationStatus::RESERVED);
}

TEST_F(ReservationTest, ReservationShouldHaveValidId)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);
    EXPECT_GT(
        reservation.getReservationId(),
        0);
}

TEST_F(ReservationTest, ReservationsShouldHaveUniqueIds)
{
    Reservation reservation1(
        checkIn,
        checkOut,
        roomNumber,
        userId);
    Reservation reservation2(
        checkIn,
        checkOut,
        102,
        2);
    EXPECT_NE(
        reservation1.getReservationId(),
        reservation2.getReservationId());
}

TEST_F(ReservationTest, CanCancelReservation)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);

    reservation.setReservationStatus(
        ReservationStatus::CANCELLED);

    EXPECT_EQ(
        reservation.getReservationStatus(),
        ReservationStatus::CANCELLED);
}

TEST_F(ReservationTest, CanCheckInReservation)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);

    reservation.setReservationStatus(
        ReservationStatus::CHECKED_IN);

    EXPECT_EQ(
        reservation.getReservationStatus(),
        ReservationStatus::CHECKED_IN);
}

TEST_F(ReservationTest, CanCheckOutReservation)
{
    Reservation reservation(
        checkIn,
        checkOut,
        roomNumber,
        userId);

    reservation.setReservationStatus(
        ReservationStatus::CHECKED_OUT);

    EXPECT_EQ(
        reservation.getReservationStatus(),
        ReservationStatus::CHECKED_OUT);
}

TEST_F(ReservationTest, InvalidDateRangeThrowsException)
{
    std::chrono::year_month_day invalidCheckOut{
        std::chrono::year{2026},
        std::chrono::month{8},
        std::chrono::day{20}};

    EXPECT_THROW(
        Reservation(
            checkIn,
            invalidCheckOut,
            roomNumber,
            userId),
        InvalidReservationException);
}

TEST_F(ReservationTest, SameCheckInAndCheckOutDateThrowsException)
{
    EXPECT_THROW(
        Reservation(
            checkIn,
            checkIn,
            roomNumber,
            userId),
        InvalidReservationException);
}
