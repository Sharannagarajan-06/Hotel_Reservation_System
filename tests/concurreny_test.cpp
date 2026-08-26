//
// Created by asus on 8/26/2026.
//

#include <gtest/gtest.h>

#include <vector>
#include <chrono>
#include <memory>
#include <thread>

#include "models/hotel.h"
#include "models/guest_details.h"
#include "models/room_category.h"
#include "services/hotel_service.h"
#include "services/logger_service.h"

class ConcurrencyTest : public ::testing::Test {
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

TEST_F(ConcurrencyTest,SameRoomCannotBeDoubleBooked) {
    Hotel hotel;
    LoggerService loggerService;

    HotelService service(
        hotel,
        loggerService
    );

    auto guest1=std::make_unique<GuestDetails>(
        "Guest One",
        "9094567801",
        "guest1@gmail.com"
    );

    auto guest2=std::make_unique<GuestDetails>(
        "Guest Two",
        "9273683012",
        "guest2@gmail.com"
    );

    auto guest3=std::make_unique<GuestDetails>(
        "Guest Three",
        "9098765478",
        "guest3@gmail.com"
    );

    int user1_id = guest1->getUserId();
    int user2_id = guest2->getUserId();
    int user3_id = guest3->getUserId();

    hotel.adduser(std::move(guest1));
    hotel.adduser(std::move(guest2));
    hotel.adduser(std::move(guest3));

    auto category =
        std::make_shared<RoomCategory>(
            RoomNames::STANDARD,
            1000,
            2
        );

    auto room =
        std::make_unique<Room>(category);

    int room_number =
        room->getRoomNumber();

    hotel.addRoom(std::move(room));

    auto check_in = date(2026,9,1);
    auto check_out = date(2026,9,5);

       std::vector<int>results={false,false,false};

    std::thread thread1([&]() {
        results[0] = service.bookRoom(
            room_number,
            check_in,
            check_out,
            user1_id
        );
    });

    std::thread thread2([&]() {
        results[1] = service.bookRoom(
            room_number,
            check_in,
            check_out,
            user2_id
        );
    });

    std::thread thread3([&]() {
        results[2] = service.bookRoom(
            room_number,
            check_in,
            check_out,
            user3_id
        );
    });

    thread1.join();
    thread2.join();
    thread3.join();

    int successful_bookings = 0;

    for (bool result:results) {
        if (result) {
            successful_bookings++;
        }
    }

    EXPECT_EQ(successful_bookings, 1);

    EXPECT_EQ(
        hotel.getReservations().size(),
        1
    );
}