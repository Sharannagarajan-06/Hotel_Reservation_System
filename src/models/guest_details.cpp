//
// Created by asus on 8/24/2026.
//

#include "models/guest_details.h"
#include <string>

/* This class Contains the defenitions of the fucntions declared in the guest_details.h file */


GuestDetails::GuestDetails( std::string guest_name,
    std::string guest_phone_number,
    std::string guest_email){
        this->guest_id=GuestDetails::next_guest_id++;
        this->guest_name=guest_name;
        this->guest_phone_number=guest_phone_number;
        this->guest_email=guest_email;
}

int GuestDetails::getGuestId(){
    return this->guest_id;
}
std::string GuestDetails::getGuestName(){
    return this->guest_name;
}
std::string GuestDetails::getGuestPhoneNumber(){
    return this->guest_phone_number;
}
std::string GuestDetails::getGuestEmail(){
    return this->guest_email;
}