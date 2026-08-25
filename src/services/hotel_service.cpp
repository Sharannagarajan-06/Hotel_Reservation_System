//
// Created by asus on 8/24/2026.
//

#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include "services/hotel_service.h"
#include "models/rooms.h"
#include "models/guest_details.h"
#include "models/availabilityindex.h"
#include "models/reservation.h"
#include "models/hotel.h"
#include "models/room_category.h"
#include "enums/reservation_status.h"
#include "services/auth_service.h"
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

std::chrono::year_month_day HotelService::getChronoDateFormat(std::string& date){

    int year=std::stoi(date.substr(0, 4));
    int month=std::stoi(date.substr(5, 2));
    int day=std::stoi(date.substr(8, 2));

    std::chrono::year_month_day result{
        std::chrono::year{year},
        std::chrono::month{static_cast<unsigned>(month)},
        std::chrono::day{static_cast<unsigned>(day)}
    };

    return result;
}

void HotelService::searchRooms(){

    std::cout<<"The Rooms that are available are :"<<std::endl;

    std::cout<<"1.Standard\n"<<"Base Rate:"<<
    room_catlog.getCategory(RoomNames::STANDARD).getRoomBaseRate()<<"\n"
    "Capacity:"<<room_catlog.getCategory(RoomNames::STANDARD).getRoomCapacity()<<std::endl;

    std::cout<<"2.Deluxe\n"<<"Base Rate:"<<
    room_catlog.getCategory(RoomNames::DELUXE).getRoomBaseRate()<<"\n"
    "Capacity:"<<room_catlog.getCategory(RoomNames::DELUXE).getRoomCapacity()<<std::endl;


    std::cout<<"3.Suite\n"<<"Base Rate:"<<
    room_catlog.getCategory(RoomNames::SUITE).getRoomBaseRate()<<"\n"
    "Capacity:"<<room_catlog.getCategory(RoomNames::SUITE).getRoomCapacity()<<std::endl;

    std::cout<<"Enter your Choice"<<std::endl;
    int choice;
    std::cin>>choice;

    RoomNames room_names;
    switch (choice) {
        case 1:
            room_names=RoomNames::STANDARD;
            break;
        case 2:
            room_names=RoomNames::DELUXE;
            break;

        case 3:
            room_names=RoomNames::SUITE;
            break;
        default:
            std::cout<<"Invalid category\n";
            return;
    }
    std::string check_in_date,check_out_date;
    std::cout<<"Enter The date for CheckIn:(YYYY-MM-DD)"<<std::endl;
    std::cin>>check_in_date;
    std::cout<<"Enter the date for CheckOut:(YYYY-MM-DD)"<<std::endl;
    std::cin>>check_out_date;

        std::chrono::year_month_day check_in=getChronoDateFormat(check_in_date);
       std::chrono::year_month_day check_out=getChronoDateFormat(check_out_date);

       std::vector<Room*>rooms=hotel.getRooms();
       std::vector<Room*>available_rooms;

        for(auto room:rooms){
               if(room->getRoomCategory()->getRoomName()==room_names &&
                        availability_index.isFree(room->getRoomNumber(),check_in,check_out)){

                               available_rooms.push_back(room);
               }
        }

        if(available_rooms.size()==0){
            std::cout<<"Type of the Room Not Available For the mentinoed Dates";
            return ;
        }

        std::cout<<"The available rooms are:"<<std::endl;

        for(auto room:available_rooms){
               std::cout<<room->getRoomNumber()<<" "<<std::endl;
       }
       std::cout<<"Enter the Room Number to Reserve a Booking:"<<std::endl;
       int room_number;
       std::cin>>room_number;
       reserveRoom(room_number,check_in,check_out);
}

void HotelService::reserveRoom(int room_number,
    std::chrono::year_month_day check_in,
    std::chrono::year_month_day check_out){

       std::cout<<"1.Exisisting User"<<std::endl;
       std::cout<<"2.New User"<<std::endl;

       std::string guest_email,guest_password;
       UserDetails* guest=NULL;

    bool exit_flag=false;

    while(!exit_flag){
        std::cout<<"1.Exisisting User"<<std::endl;
       std::cout<<"2.New User"<<std::endl;
       int choice;
       std::cin>>choice;

    switch (choice){


       case 1:{
            std::cout<<"Enter your Email:";
            std::cin>>guest_email;
            std::cout<<std::endl;
            std::cout<<"Enter your Password:";
            std::cin>>guest_password;
           std::cout<<std::endl;
           AuthService authservice(hotel) ;
           UserDetails* user= authservice.login(guest_email,guest_password);
           if(user==NULL){
                std::cout << "User Not found" << std::endl;
                return;
            }
           else{
                std::cout<<"A default guest has been Created with password guest@123"
                    <<"you can later change it in Guest Options"<<std::endl;
                exit_flag=true;
                }

           }
        case 2:{
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
           guest= new GuestDetails(guest_name,guest_phone_number,guest_email);
           hotel.adduser(guest);
           exit_flag=true;
        }
    }
}

       Reservation* reservation = new Reservation(check_in,check_out,room_number,guest->getUserId());
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

Room* HotelService::findRoomByRoomNumber(int room_number,std::vector<Room*>Rooms){

    for(auto room:Rooms){
        if(room->getRoomNumber()==room_number) return room;
    }
    return NULL;
}
void HotelService::setCheckInStatus(){

        int reservation_id;
        std::cout<<"Enter Your Reservation Id:";
        std::cin>>reservation_id;
        std::cout<<std::endl;

        std::vector<Reservation*> reservations=hotel.getReservations();

        std::vector<Room*>Rooms=hotel.getRooms();

		Reservation* reservation=isValidReservationid(reservation_id,reservations);

        Room*room =findRoomByRoomNumber(reservation->getRoomNumber(),Rooms);

        if(room->getRoomStatus()==true)std::cout<<"The Room is Already Been ocuupied"<<std::endl;

		if(!reservation) std::cout<<"Enter the valid Reservation Id"<<std::endl;

        reservation->setReservationStatus(ReservationStatus::CHECKED_IN);

}

void HotelService::setCheckOutStatus(){

        int reservation_id;
        std::cout<<"Enter Your Reservation Id:";
        std::cin>>reservation_id;
        std::cout<<std::endl;


        std::vector<Reservation*> reservations=hotel.getReservations();

        std::vector<Room*>Rooms=hotel.getRooms();

		Reservation* reservation=isValidReservationid(reservation_id,reservations);

        Room*room =findRoomByRoomNumber(reservation->getRoomNumber(),Rooms);

        if(room->getRoomStatus()==false)std::cout<<"The Room is Not Been ocuupied"<<std::endl;

		if(!reservation) std::cout<<"Enter the valid Reservation Id"<<std::endl;

        reservation->setReservationStatus(ReservationStatus::CHECKED_OUT);

}

void HotelService::addRoom(){

    int choice;
    std::cout<<"1.Standard\n";
    std::cout<<"2.Deluxe\n";
    std::cout<<"3.Suite\n";
    std::cin>>choice;
    RoomNames category_name;
    switch (choice) {
        case 1:
            category_name=RoomNames::STANDARD;
            break;
        case 2:
            category_name=RoomNames::DELUXE;
            break;

        case 3:
            category_name=RoomNames::SUITE;
            break;
        default:
            std::cout<<"Invalid category\n";
            return;
    }
    RoomCategory& category=room_catlog.getCategory(category_name);
    Room* room=new Room(const_cast<RoomCategory*>(&category));
    hotel.addRoom(room);

}
void HotelService::deleteRoom(){

    int room_number;
    std::cout<<"Enter Your Room Number:";
    std::cin>>room_number;

    std::vector<Room*>rooms=hotel.getRooms();

    for(auto room:rooms){
        if(room->getRoomNumber()==room_number){
            if(room->getRoomStatus()==true){
            std::cout<<"The Given RoomNumber is Being Currently occupied By guest so it cannotbe deleted"<<std::endl;
             return ;
            }
            else{
                hotel.removeRoom(room);
                std::cout<<"Room Successfully Removed"<<std::endl;
                return ;
            }
        }
    }
    std::cout<<"The Paticular Cannot be Found Please Enter a Valid room Number"<<std::endl;
}
void HotelService::generateReport(){

    std::vector<Reservation*>reservations=hotel.getReservations();

    int total_reservation=reservations.size();

    int cancelled_reservations=0,current_reservations=0,current_check_in=0,current_check_out=0;

    for(auto reservation : reservations){

        if(reservation->getReservationStatus()==ReservationStatus::CANCELLED){
            cancelled_reservations++;
        }
        else if(reservation->getReservationStatus()==ReservationStatus::CHECKED_IN){
            current_check_in++;
        }
        else if(reservation->getReservationStatus()==ReservationStatus::CHECKED_OUT){
            current_check_out++;
        }
        else if(reservation->getReservationStatus()==ReservationStatus::RESERVED){
            current_reservations++;
        }


    }
         std::cout<<"REPORT OF ABC HOTEL"<<std::endl;
         std::cout<<"Total Number of Reservation: "<<total_reservation<<std::endl;
         std::cout<<"Current Active Reservation:"<<current_reservations<<std::endl;
         std::cout<<"Current Active CHECK-IN:"<<current_check_in<<std::endl;
         std::cout<<"Current Active CHECK_OUT:"<<current_check_out<<std::endl;
         std::cout<<"Cancellations:"<<cancelled_reservations<<std::endl;
         std::cout<<"Reservation to CHECK-IN Percentage "<<(total_reservation-cancelled_reservations)*100<<std::endl;



}

