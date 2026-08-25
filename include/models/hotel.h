//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_HOTEL_H
#define HOTELRESERVATIONSYSTEM_HOTEL_H

#include <vector>
#include "models/rooms.h"

#include "models/reservation.h"
#include "models/user_details.h"
#include <memory>

class Hotel {

private:
    std::vector<std::unique_ptr<Room>>rooms;
    std::vector<std::unique_ptr<UserDetails>>users;
    std::vector<std::unique_ptr<Reservation>>reservations;

public:
    std::vector<std::unique_ptr<Room>>&getRooms();
    void addRoom(std::unique_ptr<Room> room);
    bool removeRoom(Room* room);

    std::vector<std::unique_ptr<UserDetails>>&getUsers();
    void adduser(std::unique_ptr<UserDetails> user);
    bool removeuser(UserDetails* user);

    void addReservation(std::unique_ptr<Reservation> reservation);
    std::vector<std::unique_ptr<Reservation>>& getReservations();

};


#endif //HOTELRESERVATIONSYSTEM_HOTEL_H