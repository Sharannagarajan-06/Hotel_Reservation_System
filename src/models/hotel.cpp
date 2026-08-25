//
// Created by asus on 8/24/2026.
//

#include <memory>
#include <vector>
#include "models/hotel.h"
#include "models/rooms.h"
#include "models/user_details.h"


    void Hotel::addRoom(std::unique_ptr<Room> room){
          rooms.push_back(std::move(room));
    }

    bool Hotel::removeRoom(Room* room) {
        for (auto it=rooms.begin(); it != rooms.end(); ++it) {
            if (it->get()==room) {
                rooms.erase(it);
                return true;
            }
        }
        return false;
    }

    void Hotel::adduser(std::unique_ptr<UserDetails> user){
          users.push_back(std::move(user));
    }

    bool Hotel::removeuser(UserDetails* user){
        for (auto it=users.begin(); it != users.end(); ++it) {
            if (it->get()==user) {
                users.erase(it);
                return true;
            }
        }
        return false;
    }

    std::vector<std::unique_ptr<Room>>& Hotel:: getRooms(){
            return Hotel::rooms;
    }

    std::vector<std::unique_ptr<UserDetails>>& Hotel::getUsers(){
        return Hotel::users;
    }

    void Hotel::addReservation(std::unique_ptr<Reservation> reservation){
            reservations.push_back(std::move(reservation));
    }

    std::vector<std::unique_ptr<Reservation>>& Hotel::getReservations(){
        return reservations;
    }



