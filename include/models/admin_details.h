#ifndef HOTELRESERVATIONSYSTEM_ADMIN_DETAILS_H
#define HOTELRESERVATIONSYSTEM_ADMIN_DETAILS_H

#include <string>
#include "models/user_details.h"
#include "enums/user_roles.h"

/* This is class AdminDetils is a dervied class form the UserDetails it used to handle adminAccount*/
class AdminDetails : public UserDetails {

public:

    AdminDetails(
        std::string user_name,
        std::string user_phone_number,
        std::string user_email,
        std::string password
    );
};

#endif