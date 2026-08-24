//
// Created by asus on 8/24/2026.
//

#include <vector>
#include "models/hotel.h"
#include "models/rooms.h"
#include "models/guest_details.h"


    void Hotel::addRoom(Room* room){
          Hotel::rooms.push_back(room);
    }

    bool Hotel::removeRoom(Room* room) {
        for (auto it=rooms.begin(); it != rooms.end(); ++it) {
            if (*it==room) {
                rooms.erase(it);
                return true;
            }
        }
        return false;
    }

    void Hotel::addGuest(GuestDetails* guest){
          Hotel::guests.push_back(guest);
    }

    bool Hotel::removeGuest(GuestDetails* guest){
        for (auto it=guests.begin(); it != guests.end(); ++it) {
            if (*it==guest) {
                guests.erase(it);
                return true;
            }
        }
        return false;
    }

    std::vector<Room*> Hotel:: getRooms(){
            return Hotel::rooms;
    }

    std::vector<GuestDetails*> Hotel::getGuests(){
        return Hotel::guests;
    }

    void Hotel::addReservation(Reservation * reservation){
            reservations.push_back(reservation);
    }

    std::vector<Reservation*> Hotel::getReservation(){
        return reservations;
    }



