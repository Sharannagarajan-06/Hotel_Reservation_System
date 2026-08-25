//
// Created by asus on 8/25/2026.
//

#include "models/user_details.h"
#include "enums/user_roles.h"


UserDetails::UserDetails(
    std::string user_name,
    std::string user_phone_number,
    std::string user_email,
    UserRoles user_role,
    std::string password
)
    : user_id(next_user_id++),
      user_name(std::move(user_name)),
      user_phone_number(std::move(user_phone_number)),
      user_email(std::move(user_email)),
      user_role(user_role),
      password(std::move(password))
{
}


int UserDetails::getUserId()  {
    return user_id;
}

std::string UserDetails::getUserName()  {
    return user_name;
}

std::string UserDetails::getUserPhoneNumber()  {
    return user_phone_number;
}

std::string UserDetails::getUserEmail()  {
    return user_email;
}

UserRoles UserDetails::getUserRole()  {
    return user_role;
}