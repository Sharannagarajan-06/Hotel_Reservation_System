/*#include <gtest/gtest.h>
#include <chrono>
#include <memory>
#include "models/hotel.h"
#include "models/guest_details.h"
#include "models/room_category.h"
#include "models/rooms.h"
#include "models/reservation.h"
#include "services/hotel_service.h"
#include "services/logger_service.h"
#include "enums/reservation_status.h"

class HotelReservationSystemTest : public ::testing::Test {
protected:

    std::chrono::year_month_day date(
        int year,
        unsigned month,
        unsigned day
    ) {
        return std::chrono::year_month_day{
            std::chrono::year{year},
            std::chrono::month{month},
            std::chrono::day{day}
        };
    }
};

TEST_F(
    HotelReservationSystemTest,
    CompleteBookingLifeCycle
) {
    Hotel hotel;
    LoggerService loggerService;

    HotelService service(
        hotel,
        loggerService
    );

    auto guest = std::make_unique<GuestDetails>(
        "Guest One",
        "9094567801",
        "guest1@gmail.com"
    );

    int user_id = guest->getUserId();

    hotel.adduser(
        std::move(guest)
    );

    auto category =
        std::make_shared<RoomCategory>(
            RoomNames::STANDARD,
            1000,
            2
        );

    auto room =
        std::make_unique<Room>(
            category
        );

    int room_number =
        room->getRoomNumber();

    hotel.addRoom(
        std::move(room)
    );

    auto check_in =
        date(2026, 9, 1);

    auto check_out =
        date(2026, 9, 2);

    bool bookingResult =
        service.bookRoom(
            room_number,
            check_in,
            check_out,
            user_id
        );

    EXPECT_TRUE(
        bookingResult
    );

    ASSERT_EQ(
        hotel.getReservations().size(),
        1
    );

    Reservation* reservation =
        hotel.getReservations()[0].get();

    ASSERT_NE(
        reservation,
        nullptr
    );

    int reservation_id =
        reservation->getReservationId();

    EXPECT_EQ(
        reservation->getUserId(),
        user_id
    );

    EXPECT_EQ(
        reservation->getRoomNumber(),
        room_number
    );

    EXPECT_EQ(
        reservation->getCheckIn(),
        check_in
    );

    EXPECT_EQ(
        reservation->getCheckOut(),
        check_out
    );

    EXPECT_EQ(
        reservation->getReservationStatus(),
        ReservationStatus::RESERVED
    );

    service.setCheckInStatus(
        reservation_id
    );

    EXPECT_EQ(
        reservation->getReservationStatus(),
        ReservationStatus::CHECKED_IN
    );

    double bill=service.setCheckOutStatus(
        reservation_id
    );

    EXPECT_EQ(
        reservation->getReservationStatus(),
        ReservationStatus::CHECKED_OUT
    );
    EXPECT_EQ(bill,1280);

}*/