//
// Created by asus on 8/25/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_USER_DETAILS_H
#define HOTELRESERVATIONSYSTEM_USER_DETAILS_H

#include <string>
#include "enums/user_roles.h"
class UserDetails {
    
private :

    inline static int next_user_id = 1;
    int user_id;
    std::string user_name;
    std::string user_phone_number;
    std::string user_email;
    UserRoles user_role;
    std::string user_password;

public:

    //Constructor for Intializing the userDetails

    UserDetails( std::string user_name,
    std::string user_phone_number,
    std::string user_email,UserRoles user_role,
    std::string user_password);

    int getUserId() ;

    std::string getUserName();

    std::string getUserPhoneNumber();

    std::string getUserEmail();

    UserRoles getUserRole();

    std::string getUserPassword();

    
};


#endif //HOTELRESERVATIONSYSTEM_USER_DETAILS_H