//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_HOTEL_H
#define HOTELRESERVATIONSYSTEM_HOTEL_H

#include <vector>
#include "models/rooms.h"
#include "models/guest_details.h"
#include "models/reservation.h"

class Hotel {

private:
    std::vector<Room*>rooms;
    std::vector<GuestDetails*>guests;
    std::vector<Reservation*>reservations;

public:
    std::vector<Room*> getRooms();
    void addRoom(Room* room);
    bool removeRoom(Room* room);
    std::vector<GuestDetails*>getGuests();
    void addGuest(GuestDetails* guest);
    bool removeGuest(GuestDetails* guest);
    void addReservation(Reservation * reservation);
    std::vector<Reservation*> getReservation();

};


#endif //HOTELRESERVATIONSYSTEM_HOTEL_H