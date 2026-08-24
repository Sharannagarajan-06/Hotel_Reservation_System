//
// Created by asus on 8/24/2026.
//

#include <vector>
#include <iostream>
#include "services/hotel_service.h"
#include "models/rooms.h"
#include "models/guest_details.h"
#include "models/availabilityindex.h"
#include "models/reservation.h"
#include "models/hotel.h"
#include "models/room_category.h"
#include "enums/reservation_status.h"

bool checkRoom(int room_number,std::vector<Room*>& available_rooms){
       for(auto room:available_rooms){
              if(room->getRoomNumber()==room_number) return true;
       }
       return false;
}


HotelService::HotelService(Hotel& hotel)
    : hotel(hotel) {
}

void HotelService::reserveRoom(RoomNames room_names,
        std::chrono::year_month_day check_in,
        std::chrono::year_month_day check_out){
       std::vector<Room*>rooms=hotel.getRooms();
       std::vector<Room*>available_rooms;
        for(auto room:rooms){

               if(room->getRoomCategory()->getRoomName()==room_names &&
                        availability_index.isFree(room->getRoomNumber(),check_in,check_out)){

                               available_rooms.push_back(room);
               }
        }
        std::cout<<"The available rooms are:"<<std::endl;

        for(auto room:available_rooms){
               std::cout<<room->getRoomNumber()<<" "<<std::endl;
       }
       std::cout<<"Enter the Room Number to Reserve a Booking:"<<std::endl;

       int room_number;
       std::cin>>room_number;
       std::string guest_name,guest_phone_number,guest_email;
       std::cin.ignore();
       std::cout<<"Enter Your Name :";
       getline(std::cin,guest_name);
       std::cout<<std::endl;
       std::cout<<"Enter Your Phone Number";
       getline(std::cin,guest_phone_number);
       std::cout<<std::endl;
       std::cout<<"Enter Your Email";
       getline(std::cin,guest_email);
       std::cout<<std::endl;

       //name,phno,email
       GuestDetails* guest= new GuestDetails(guest_name,guest_phone_number,guest_email);
       Reservation* reservation = new Reservation(check_in,check_out,room_number,guest->getGuestId());
       availability_index.updateAvailability(room_number,check_in,check_out);
       hotel.addReservation(reservation);

		std::cout<<"Your Rooms has Been Reserved with the booking Id:"<<
                            reservation->getReservationId()<<" "<<std::endl;
}

void HotelService::cancelReservedRoom(int reservation_id){

		std::vector<Reservation*> reservations=hotel.getReservations();
		Reservation* reservation=isValidReservationid(reservation_id,reservations);

		if(!reservation) std::cout<<"Enter the valid Reservation Id"<<std::endl;

        availability_index.removeAvailability(reservation->getRoomNumber(),
                                                reservation->getCheckIn(),
                                                reservation->getCheckOut());
		reservation->setReservationStatus(ReservationStatus::CANCELLED);

        std::cout<<"Reservation Cancelled Successfully"<<std::endl;

}

Reservation* HotelService::isValidReservationid(int reservation_id,std::vector<Reservation*>& reservations){

	for(auto reservation : reservations){
		if(reservation->getReservationId()==reservation_id) return reservation;
	}
	return NULL;
}

