#include <iostream>
#include "models/room_category.h"
#include "models/rooms.h"
#include "enums/room_name.h"

int main(){

    std::cout<<"Welcome to ABC Hotels "<<std::endl;

    RoomCategory* standard = new RoomCategory(RoomNames::STANDARD,2,1000);
    RoomCategory* deluxe = new RoomCategory(RoomNames::DELUXE,4,2000);
    RoomCategory* suite = new RoomCategory(RoomNames::SUITE,6,4000);

    Rooms* r1 = new Rooms(1, standard, false);
	std::cout<<r1->getRoomCategory()->getRoomCapacity();

}