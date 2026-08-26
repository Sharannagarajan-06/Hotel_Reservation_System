//
// Created by asus on 8/26/2026.
//

#include <gtest/gtest.h>
#include <chrono>
#include "models/availabilityindex.h"

class AvailabilityTest : public ::testing::Test
{
protected:
    AvailabilityIndex availability;

    std::chrono::year_month_day date(int year, unsigned month, unsigned day)
    {
        return std::chrono::year_month_day{
            std::chrono::year{year},
            std::chrono::month{month},
            std::chrono::day{day}};
    }
};

TEST_F(AvailabilityTest, NewRoomIsAvailable)
{
    auto checkIn = date(2026, 9, 1);
    auto checkOut = date(2026, 9, 5);

    EXPECT_TRUE(
        availability.isFree(101, checkIn, checkOut));
}

TEST_F(AvailabilityTest, RoomBecomesUnavailableAfterBooking)
{
    auto checkIn = date(2026, 9, 1);
    auto checkOut = date(2026, 9, 5);

    availability.updateAvailability(
        101,
        checkIn,
        checkOut);

    EXPECT_FALSE(
        availability.isFree(101, checkIn, checkOut));
}

TEST_F(AvailabilityTest, SameDatesCannotBeBookedAgain)
{
    auto checkIn = date(2026, 9, 1);
    auto checkOut = date(2026, 9, 5);

    availability.updateAvailability(
        101,
        checkIn,
        checkOut);

    EXPECT_FALSE(
        availability.isFree(101, checkIn, checkOut));
}

TEST_F(AvailabilityTest, OverlappingBookingIsRejected)
{
    auto existingCheckIn = date(2026, 9, 5);
    auto existingCheckOut = date(2026, 9, 10);

    availability.updateAvailability(
        101,
        existingCheckIn,
        existingCheckOut);

    auto newCheckIn = date(2026, 9, 7);
    auto newCheckOut = date(2026, 9, 12);

    EXPECT_FALSE(
        availability.isFree(101, newCheckIn, newCheckOut));
}

TEST_F(AvailabilityTest, BookingBeforeExistingBookingIsAllowed)
{
    auto existingCheckIn = date(2026, 9, 10);
    auto existingCheckOut = date(2026, 9, 15);

    availability.updateAvailability(
        101,
        existingCheckIn,
        existingCheckOut);

    auto newCheckIn = date(2026, 9, 1);
    auto newCheckOut = date(2026, 9, 10);

    EXPECT_TRUE(
        availability.isFree(101, newCheckIn, newCheckOut));
}

TEST_F(AvailabilityTest, BookingAfterExistingBookingIsAllowed)
{
    auto existingCheckIn = date(2026, 9, 1);
    auto existingCheckOut = date(2026, 9, 5);

    availability.updateAvailability(
        101,
        existingCheckIn,
        existingCheckOut);

    auto newCheckIn = date(2026, 9, 5);
    auto newCheckOut = date(2026, 9, 10);

    EXPECT_TRUE(
        availability.isFree(101, newCheckIn, newCheckOut));
}

TEST_F(AvailabilityTest, AdjacentBookingIsAllowed)
{
    auto firstCheckIn = date(2026, 9, 1);
    auto firstCheckOut = date(2026, 9, 5);

    availability.updateAvailability(
        101,
        firstCheckIn,
        firstCheckOut);

    auto secondCheckIn = date(2026, 9, 5);
    auto secondCheckOut = date(2026, 9, 10);

    EXPECT_TRUE(
        availability.isFree(
            101,
            secondCheckIn,
            secondCheckOut));
}

TEST_F(AvailabilityTest, DifferentRoomsCanBeBookedForSameDates)
{
    auto checkIn = date(2026, 9, 1);
    auto checkOut = date(2026, 9, 5);

    availability.updateAvailability(
        101,
        checkIn,
        checkOut);

    EXPECT_FALSE(
        availability.isFree(101, checkIn, checkOut));

    EXPECT_TRUE(
        availability.isFree(102, checkIn, checkOut));
}

TEST_F(AvailabilityTest, CancelledBookingMakesRoomAvailable)
{
    auto checkIn = date(2026, 9, 1);
    auto checkOut = date(2026, 9, 5);

    availability.updateAvailability(
        101,
        checkIn,
        checkOut);

    EXPECT_FALSE(
        availability.isFree(101, checkIn, checkOut));

    availability.removeAvailability(
        101,
        checkIn,
        checkOut);

    EXPECT_TRUE(
        availability.isFree(101, checkIn, checkOut));
}

TEST_F(AvailabilityTest, DifferentDateRangesCanUseSameRoom)
{
    auto firstCheckIn = date(2026, 9, 1);
    auto firstCheckOut = date(2026, 9, 5);

    availability.updateAvailability(
        101,
        firstCheckIn,
        firstCheckOut);

    auto secondCheckIn = date(2026, 9, 5);
    auto secondCheckOut = date(2026, 9, 10);

    EXPECT_TRUE(
        availability.isFree(
            101,
            secondCheckIn,
            secondCheckOut));
}