find_package(GTest REQUIRED)

add_executable(HotelTests
        reservation_test.cpp
        room_tests.cpp
        user_tests.cpp
        auth_service_test.cpp
        hotel_service_test.cpp
        availability_index_test.cpp
        billing_test.cpp
        concurreny_test.cpp
        hotel_reservation_system.cpp
)

target_link_libraries(HotelTests
        PRIVATE
        hotelservice
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(HotelTests)