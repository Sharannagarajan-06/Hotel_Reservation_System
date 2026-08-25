//
// Created by asus on 8/25/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_AUTH_SERVICE_H
#define HOTELRESERVATIONSYSTEM_AUTH_SERVICE_H

#include <string>
#include "models/hotel.h"
#include "models/user_details.h"

class AuthService{
    Hotel& hotel;

public:

    AuthService(Hotel& hotel);
    UserDetails* login(std::string email , std::string password);
    bool isAdmin(UserDetails* user);



};


#endif //HOTELRESERVATIONSYSTEM_AUTH_SERVICE_H