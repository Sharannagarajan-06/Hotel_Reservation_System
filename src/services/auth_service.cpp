//
// Created by asus on 8/25/2026.
//

#include "services/auth_service.h"

AuthService::AuthService(Hotel& hotel):hotel(hotel){}

UserDetails* AuthService::login(std::string email , std::string password){
    std::vector<UserDetails*>users=hotel.getUsers();

    for(auto user:users){
        if(user->getUserEmail()==email &&user->getUserPassword()==password)  return user;
    }
    return NULL;
}

bool AuthService::isAdmin(UserDetails* user){
    return user->getUserRole() == UserRoles::ADMIN;
}