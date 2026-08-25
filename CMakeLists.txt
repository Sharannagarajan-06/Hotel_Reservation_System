cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(hotel_reservation_system)

# Make Library
add_library(rooms STATIC src/models/room_category.cpp
                         src/models/rooms.cpp   )

add_library(user STATIC src/models/guest_details.cpp
                        src/models/user_details.cpp
                        src/models/admin_details.cpp)

add_library(hotel STATIC src/models/hotel.cpp)

add_library(reservation STATIC src/models/reservation.cpp)
add_library( hotelservice STATIC    src/services/hotel_service.cpp
                                    src/models/availabilityindex.cpp)

add_library(authservice STATIC src/services/auth_service.cpp)

# Include .h files directory
target_include_directories(rooms PUBLIC include)

target_include_directories(user PUBLIC include)

target_include_directories(hotel PUBLIC include)

target_include_directories(reservation PUBLIC include)

target_include_directories(hotelservice PUBLIC include)

target_include_directories(authservice PUBLIC include)

target_link_libraries(hotelservice PUBLIC   rooms
                                            user
                                            hotel
                                            reservation
                                            authservice)
add_executable(hotel_reservation_system hotel_reservation_system.cpp)

target_link_libraries(hotel_reservation_system
        PRIVATE
        hotelservice
)
