cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(hotel_reservation_system)
add_library(rooms STATIC src/models/room_category.cpp
                         src/models/rooms.cpp   )

add_library(user STATIC src/models/guest_details.cpp)

add_library(hotel STATIC src/models/hotel.cpp)

add_library(reservation STATIC src/models/reservation.cpp)

target_include_directories(rooms PUBLIC include)

target_include_directories(user PUBLIC include)

target_include_directories(hotel PUBLIC include)

target_include_directories(reservation PUBLIC include)

add_executable(hotel_reservation_system hotel_reservation_system.cpp)
target_link_libraries(hotel_reservation_system PUBLIC   rooms
                                                        user
                                                        hotel
                                                        reservation)