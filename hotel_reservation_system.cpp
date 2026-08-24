#include <iostream>
#include "models/room_category.h"
#include "models/rooms.h"
#include "enums/room_name.h"
#include "models/guest_details.h"
#include "models/hotel.h"

int main(){

    std::cout<<"Welcome to ABC Hotels "<<std::endl;

    RoomCategory* standard = new RoomCategory(RoomNames::STANDARD,2,1000);
    RoomCategory* deluxe = new RoomCategory(RoomNames::DELUXE,4,2000);
    RoomCategory* suite = new RoomCategory(RoomNames::SUITE,6,4000);

    Room* r1 = new Room(1, standard, false);
	std::cout<<r1->getRoomCategory()->getRoomCapacity()<<std::endl;
    Hotel* h = new Hotel();
    h->addRoom(r1);
    GuestDetails* guest1= new GuestDetails("Sharan","9345480377","sharannagarajan06@gmail.com");
    std::cout<<guest1->getGuestName()<<std::endl;

}