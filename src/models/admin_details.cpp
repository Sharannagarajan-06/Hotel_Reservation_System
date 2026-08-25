//
// Created by asus on 8/25/2026.
//

#include "models/admin_details.h"

AdminDetails::AdminDetails(
    std::string user_name,
    std::string user_phone_number,
    std::string user_email,
    std::string password
)
    : UserDetails(
        user_name,
        user_phone_number,
        user_email,
        UserRoles::ADMIN,
        password
    )
{
}