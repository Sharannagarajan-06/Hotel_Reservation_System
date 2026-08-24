cmake_minimum_required(VERSION 4.0)
project(hotel_reservation_system)
add_library(rooms STATIC src/models/room_category.cpp
                         src/models/rooms.cpp   )
target_include_directories(rooms PUBLIC include)
add_executable(hotel_reservation_system hotel_reservation_system.cpp)
target_link_libraries(hotel_reservation_system PUBLIC rooms)