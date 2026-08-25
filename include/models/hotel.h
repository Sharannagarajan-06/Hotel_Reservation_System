//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_HOTEL_H
#define HOTELRESERVATIONSYSTEM_HOTEL_H

#include <vector>
#include "models/rooms.h"

#include "models/reservation.h"
#include "models/user_details.h"
class Hotel {

private:
    std::vector<Room*>rooms;
    std::vector<UserDetails*>users;
    std::vector<Reservation*>reservations;

public:
    std::vector<Room*> getRooms();
    void addRoom(Room* room);
    bool removeRoom(Room* room);
    std::vector<UserDetails*>getUsers();
    void adduser(UserDetails* user);
    bool removeuser(UserDetails* user);
    void addReservation(Reservation * reservation);
    std::vector<Reservation*> getReservations();

};


#endif //HOTELRESERVATIONSYSTEM_HOTEL_H