#include <iostream>
#include <chrono>
#include "models/room_category.h"
#include "models/rooms.h"
#include "enums/room_name.h"
#include "models/guest_details.h"
#include "models/hotel.h"
#include "models/reservation.h"
#include "services/hotel_service.h"

int main(){

    std::cout<<"Welcome to ABC Hotels "<<std::endl;

    RoomCategory* standard = new RoomCategory(RoomNames::STANDARD,2,1000);
    RoomCategory* deluxe = new RoomCategory(RoomNames::DELUXE,4,2000);
    RoomCategory* suite = new RoomCategory(RoomNames::SUITE,6,4000);

    Room* r1 = new Room(1, standard, false);
	std::cout<<r1->getRoomCategory()->getRoomCapacity()<<std::endl;

    Hotel hotel;
    hotel.addRoom(r1);

    GuestDetails* guest1= new GuestDetails("Sharan","9345480377","sharannagarajan06@gmail.com");
    std::cout<<guest1->getGuestName()<<std::endl;


/*
auto checkIn = std::chrono::year_month_day{
    std::chrono::year{2026},
    std::chrono::month{8},
    std::chrono::day{24}
};

auto checkOut = std::chrono::year_month_day{
    std::chrono::year{2026},
    std::chrono::month{8},
    std::chrono::day{28}
};

Reservation reservation(checkIn, checkOut);
	std::cout<<reservation.getReservationId()<<reservation.getCheckIn();
*/
    auto checkIn = std::chrono::year_month_day{
    std::chrono::year{2026},
    std::chrono::month{8},
    std::chrono::day{24}
};

auto checkOut = std::chrono::year_month_day{
    std::chrono::year{2026},
    std::chrono::month{8},
    std::chrono::day{28}
};
	std::cout<<"hello"<<std::endl;
       HotelService hs(hotel);
       hs.reserveRoom(RoomNames::STANDARD,checkIn,checkOut);

    int reservation_id;
    std::cin>>reservation_id;
    hs.cancelReservedRoom(reservation_id);
}