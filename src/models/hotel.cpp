//
// Created by asus on 8/24/2026.
//

#include <vector>
#include "models/hotel.h"
#include "models/rooms.h"
#include "models/user_details.h"


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

    void Hotel::adduser(UserDetails* user){
          Hotel::users.push_back(user);
    }

    bool Hotel::removeuser(UserDetails* user){
        for (auto it=users.begin(); it != users.end(); ++it) {
            if (*it==user) {
                users.erase(it);
                return true;
            }
        }
        return false;
    }

    std::vector<Room*> Hotel:: getRooms(){
            return Hotel::rooms;
    }

    std::vector<UserDetails*> Hotel::getUsers(){
        return Hotel::users;
    }

    void Hotel::addReservation(Reservation * reservation){
            reservations.push_back(reservation);
    }

    std::vector<Reservation*> Hotel::getReservations(){
        return reservations;
    }



