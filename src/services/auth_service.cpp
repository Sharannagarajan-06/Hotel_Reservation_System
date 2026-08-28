//
// Created by asus on 8/25/2026.
//

#include "services/auth_service.h"
#include "exceptions/user_exception.h"

AuthService::AuthService(Hotel &hotel) : hotel(hotel) {}

UserDetails *AuthService::login(std::string email, std::string password)
{
    auto &users = hotel.getUsers();

    for (auto &user : users)
    {
        if (user->getUserEmail() == email && user->getUserPassword() == password)
            return user.get();
    }
    throw AuthenticationFailedException(
        "Invalid email or password");
}

bool AuthService::isAdmin(UserDetails *user)
{
    return user->getUserRole() == UserRoles::ADMIN;
}