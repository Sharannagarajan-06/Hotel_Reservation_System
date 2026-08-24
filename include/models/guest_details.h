//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_GUEST_DETAILS_H
#define HOTELRESERVATIONSYSTEM_GUEST_DETAILS_H
#include <string>

/* This isthe guest_details which has the declearation for the class such as guest name , phone number and etc..*/


class GuestDetails {

private :

    inline static int next_guest_id = 1;
    int guest_id;
    std::string guest_name;
    std::string guest_phone_number;
    std::string guest_email;

public:

//Constructor for Intializing the GuestDetails

    GuestDetails( std::string guest_name,
    std::string guest_phone_number,
    std::string guest_email);

//Getter for Getting the Guest ID
    int getGuestId();

//Getter for Getting the Guest Name
    std::string getGuestName();

// Getter for getting the GuestPhoneNumber
    std::string getGuestPhoneNumber();

// Getter for Getting the GuestEmail
    std::string getGuestEmail();

};


#endif //HOTELRESERVATIONSYSTEM_GUEST_DETAILS_H