//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_GUEST_DETAILS_H
#define HOTELRESERVATIONSYSTEM_GUEST_DETAILS_H
#include <string>
#include "enums/user_roles.h"
#include "models/user_details.h"


/* This isthe guest_details which has the declearation for the class such as guest name , phone number and etc..*/


class GuestDetails :public UserDetails {


public:

//Constructor for Intializing the GuestDetails

    GuestDetails( std::string user_name,
    std::string user_phone_number,
    std::string user_email,
    std::string password);

GuestDetails(std::string user_name,
    std::string user_phone_number,
    std::string user_email);

};


#endif //HOTELRESERVATIONSYSTEM_GUEST_DETAILS_H