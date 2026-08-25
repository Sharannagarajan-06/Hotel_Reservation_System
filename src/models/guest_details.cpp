//
// Created by asus on 8/24/2026.
//

#include "models/guest_details.h"
#include "enums/user_roles.h"
#include <string>

/* This class Contains the defenitions of the fucntions declared in the guest_details.h file */


GuestDetails::GuestDetails(std::string user_name,
    std::string user_phone_number,
    std::string user_email,
    std::string user_password):UserDetails(
    user_name,
    user_phone_number,
    user_email,
    UserRoles::GUEST,
    user_password
){}

GuestDetails::GuestDetails(std::string user_name,
    std::string user_phone_number,
    std::string user_email):UserDetails(
    user_name,
    user_phone_number,
    user_email,
    UserRoles::GUEST,
    "guest@123"

){}