//
// Created by asus on 8/25/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_USER_DETAILS_H
#define HOTELRESERVATIONSYSTEM_USER_DETAILS_H

#include <string>
#include "enums/user_roles.h"

/*
    The userDetails class is the base class of the users it is being further inherited
        by AdminDetails and GuestDetails to have theri own hireachy works
*/
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

    void setUserPassword(std::string user_password);

    
};


#endif //HOTELRESERVATIONSYSTEM_USER_DETAILS_H