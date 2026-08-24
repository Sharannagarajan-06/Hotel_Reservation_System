cmake_minimum_required(VERSION 4.0)
project(hotel_reservation_system)
add_library(rooms STATIC src/models/room_category.cpp
                         src/models/rooms.cpp   )

add_library(user STATIC src/models/guest_details.cpp)
target_include_directories(rooms PUBLIC include)
target_include_directories(user PUBLIC include)
add_executable(hotel_reservation_system hotel_reservation_system.cpp)
target_link_libraries(hotel_reservation_system PUBLIC   rooms
                                                        user)