//
// Created by asus on 8/24/2026.
//
#include <cctype>
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
#include "services/logger_service.h"
#include "enums/log_message_type.h"
#include <memory>
#include "models/seasonal_billing.h"
#include "models/standard_billing.h"
#include "models/billing_strategy.h"
#include <mutex>
#include <memory>
#include "exceptions/hotel_exception.h"
#include "exceptions/user_exception.h"
#include "exceptions/room_exception.h"
#include "exceptions/reservation_exception.h"
#include "exceptions/billing_exception.h"
#include "exceptions/date_exception.h"



/*
    This Class is the Heart of the Hotel Reservation system this class
        does a lot of major operations
*/


//the checkRoom() function is used to check whether a room exists or not
bool checkRoom(int room_number, std::vector<Room *> &available_rooms)
{
    for (auto room : available_rooms)
    {
        if (room->getRoomNumber() == room_number)
            return true;
    }
    return false;
}

//this is an constructor for the HotelServics it takes hotel and Loggerservice object and assign them using constructor
HotelService::HotelService(Hotel &hotel, LoggerService &loggerservice)
    : hotel(hotel), loggerservice(loggerservice)
{
}


/*
    the BookRoom Function is a test function written in the same exact logic of the
    ReserveRoom to test the threads
*/
bool HotelService::bookRoom(int room_number,std::chrono::year_month_day check_in,
            std::chrono::year_month_day check_out,int user_id){

         std::lock_guard<std::mutex> lock(reservation_mutex);

    if (!availability_index.isFree(room_number,check_in,check_out)) {
        return false;
    }

    auto reservation = std::make_unique<Reservation>(
        check_in,
        check_out,
        room_number,
        user_id
    );

    Reservation* reservation_ptr = reservation.get();

    availability_index.updateAvailability(
        room_number,
        check_in,
        check_out
    );

    hotel.addReservation(std::move(reservation));

    loggerservice.addLog(
        std::make_unique<Logger>(
            user_id,
            reservation_ptr->getReservationId(),
            LogMessageType::BOOKING
        )
    );

    return true;

   }


/*
    getChronoDateFormat() is used to convert the normal string date to chrono format and give output
*/
std::chrono::year_month_day HotelService::getChronoDateFormat(std::string &date)
{

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    std::chrono::year_month_day result{
        std::chrono::year{year},
        std::chrono::month{static_cast<unsigned>(month)},
        std::chrono::day{static_cast<unsigned>(day)}};

    return result;
}

bool HotelService::isValidDateFormat(const std::string& date)
{
    if (date.length()!=10)
        return false;

    if (date[4]!='-'||date[7]!='-')
        return false;

    for (int i=0;i<date.length();i++)
    {
        if (i==4||i==7)
            continue;

        if (!std::isdigit(date[i]))
            return false;
    }

    return true;
}

/*
    searchRooms() is used to search the available rooms for the paticualr type and date ranges
    and book them using revserveRoom() to reserveRooms it internally uses AvailabilityIndex to
    searching the available Rooms

    The TimeComplexity of the Fucntion is O(M x N)

    NOTE:
        Considering M=number of rooms
                    N=number of Bookings made for a room
*/
void HotelService::searchRooms()
{

    std::cout << "The Rooms that are available are :" << std::endl;

    std::cout << "1.Standard\n"
              << "Base Rate:" << room_catlog.getCategory(RoomNames::STANDARD)->getRoomBaseRate() << "\n"
                                                                                                    "Capacity:"
              << room_catlog.getCategory(RoomNames::STANDARD)->getRoomCapacity() << std::endl;

    std::cout << "2.Deluxe\n"
              << "Base Rate:" << room_catlog.getCategory(RoomNames::DELUXE)->getRoomBaseRate() << "\n"
                                                                                                  "Capacity:"
              << room_catlog.getCategory(RoomNames::DELUXE)->getRoomCapacity() << std::endl;

    std::cout << "3.Suite\n"
              << "Base Rate:" << room_catlog.getCategory(RoomNames::SUITE)->getRoomBaseRate() << "\n"
                                                                                                 "Capacity:"
              << room_catlog.getCategory(RoomNames::SUITE)->getRoomCapacity() << std::endl;

    std::cout << "Prices of the Rooms May become 2X in Sesonal or Weekend Durations " << std::endl;
    std::cout << "Enter your Choice: ";
    int choice;
    std::cin >> choice;
    std::cout<<std::endl;
    RoomNames room_names;
    switch (choice)
    {
    case 1:
        room_names = RoomNames::STANDARD;
        break;
    case 2:
        room_names = RoomNames::DELUXE;
        break;

    case 3:
        room_names = RoomNames::SUITE;
        break;
    default:
        std::cout << "Invalid category\n";
        return;
    }
    std::string check_in_date, check_out_date;
    std::cout << "Enter The date for CheckIn:(YYYY-MM-DD)";
    std::cin >> check_in_date;
    std::cout << std::endl;
    std::cout << "Enter the date for CheckOut:(YYYY-MM-DD)";
    std::cin >> check_out_date;
    std::cout << std::endl;
    if (!isValidDateFormat(check_in_date)||!isValidDateFormat(check_out_date)){
        throw InvalidDateException("Invalid date format. Please use YYYY-MM-DD.\n");
    }


    std::chrono::year_month_day check_in = getChronoDateFormat(check_in_date);
    std::chrono::year_month_day check_out = getChronoDateFormat(check_out_date);

    if(!check_in.ok() || !check_out.ok()){
        throw DateException("Invalid Date Format");
    }
    auto &rooms = hotel.getRooms();
    std::vector<Room *> available_rooms;

    for (auto &room : rooms)
    {
        if (room->getRoomCategory()->getRoomName() == room_names &&
            availability_index.isFree(room->getRoomNumber(), check_in, check_out))
        {

            available_rooms.push_back(room.get());
        }
    }

    if (available_rooms.size() == 0)
    {
        std::cout << "Type of the Room Not Available For the mentinoed Dates" << std::endl;
        return;
    }

    std::cout << "The available rooms are:" << std::endl;

    for (auto room : available_rooms)
    {
        std::cout << room->getRoomNumber() << " " << std::endl;
    }
    std::cout << "Enter the Room Number to Reserve a Booking:" << std::endl;
    int room_number;
    std::cin >> room_number;
    reserveRoom(room_number, check_in, check_out);
}

/*

The ReservRoom() function is used to reseve a room for a paticular user
    it also uses lock_guard for supporting multithreading
*/
void HotelService::reserveRoom(int room_number,
                               std::chrono::year_month_day check_in,
                               std::chrono::year_month_day check_out)
{

    std::string guest_email, guest_password;

    UserDetails *guest_ptr;
    bool exit_flag = false;

    while (!exit_flag)
    {
        std::cout << "1.Exisisting User" << std::endl;
        std::cout << "2.New User" << std::endl;
        std::cout<<"Enter Your Choice:";
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::cout << "Enter your Email:";
            std::cin >> guest_email;
            std::cout << std::endl;
            std::cout << "Enter your Password:";
            std::cin >> guest_password;
            std::cout << std::endl;
            AuthService authservice(hotel);
            guest_ptr = authservice.login(guest_email, guest_password);
            if (guest_ptr == NULL)
            {
                std::cout << "User Not found" << std::endl;
            }
            else
            {
                std::cout << "User found";
                exit_flag = true;
            }
            break;
        }
        case 2:
        {
            std::string guest_name, guest_phone_number, guest_email;
            std::cin.ignore();
            std::cout << "Enter Your Name :";
            getline(std::cin, guest_name);
            std::cout << std::endl;
            std::cout << "Enter Your Phone Number";
            getline(std::cin, guest_phone_number);
            std::cout << std::endl;
            std::cout << "Enter Your Email";
            getline(std::cin, guest_email);
            std::cout << std::endl;

            auto guest = std::make_unique<GuestDetails>(
                guest_name,
                guest_phone_number,
                guest_email);
            guest_ptr = guest.get();
            hotel.adduser(std::move(guest));
            std::cout << "A default guest has been Created with password guest@123"
                      << "you can later change it in Guest Options" << std::endl;
            exit_flag = true;
        }
        }
    }
    std::lock_guard<std::mutex> lock(reservation_mutex);
    if (!availability_index.isFree(room_number, check_in, check_out))
    {
        throw RoomUnavailableException(
            "Room is already booked for the selected dates");
    }
    auto reservation = std::make_unique<Reservation>(check_in, check_out, room_number, guest_ptr->getUserId());
    Reservation *reservation_ptr = reservation.get();
    availability_index.updateAvailability(room_number, check_in, check_out);
    hotel.addReservation(std::move(reservation));

    loggerservice.addLog(std::make_unique<Logger>(guest_ptr->getUserId(), reservation_ptr->getReservationId(),
                                                  LogMessageType::BOOKING));

    std::cout << "Your Rooms has Been Reserved with the booking Id:" << reservation_ptr->getReservationId() << " " << std::endl;
}

/*
    the Cancel Reservation is used to cancel a Reserved Room using the reservation id
*/
void HotelService::cancelReservedRoom()
{

    int reservation_id;
    std::cout << "Enter Your Reservation Id:";
    std::cin >> reservation_id;
    std::cout << std::endl;

    auto &reservations = hotel.getReservations();
    Reservation *reservation = isValidReservationid(reservation_id, reservations);

    if (!reservation)
    {
        throw ReservationNotFoundException(
            "Invalid Reservation ID");
    }

    availability_index.removeAvailability(reservation->getRoomNumber(),
                                          reservation->getCheckIn(),
                                          reservation->getCheckOut());
    reservation->setReservationStatus(ReservationStatus::CANCELLED);

    std::cout << "Reservation Cancelled Successfully" << std::endl;

    loggerservice.addLog(std::make_unique<Logger>(reservation->getUserId(), reservation->getReservationId(),
                                                  LogMessageType::CANCELLATION));
}

/*
    isValidReservationid is used to return whether the givem userid is a valid one or not
*/
Reservation* HotelService::isValidReservationid(int reservation_id, std::vector<std::unique_ptr<Reservation>> &reservations)
{

    for (auto &reservation : reservations)
    {
        if (reservation->getReservationId() == reservation_id)
            return reservation.get();
    }
    return NULL;
}
/*
    findRoomByRoomNumber is used to get the Room object using the roomid
*/
Room* HotelService::findRoomByRoomNumber(int room_number, std::vector<std::unique_ptr<Room>> &rooms)
{

    for (auto &room : rooms)
    {
        if (room->getRoomNumber() == room_number)
            return room.get();
    }
    return NULL;
}

/*
    The setCheckInStatus() is used to handle setting checkin status for a user using the reservation id
*/
void HotelService::setCheckInStatus()
{

    int reservation_id;
    std::cout << "Enter Your Reservation Id:";
    std::cin >> reservation_id;
    std::cout << std::endl;

    auto &reservations = hotel.getReservations();
    auto &rooms = hotel.getRooms();

    Reservation *reservation = isValidReservationid(reservation_id, reservations);
    if (!reservation)
    {
        throw ReservationNotFoundException(
            "Reservation ID not found");
    }

    Room *room = findRoomByRoomNumber(reservation->getRoomNumber(), rooms);

    if (!room)
    {
        throw RoomNotFoundException(
            "Room Cannot be found");
    }

    if (room->getRoomStatus())
    {
        throw RoomOccupiedException(
            "Room is already occupied");
    }

    reservation->setReservationStatus(ReservationStatus::CHECKED_IN);
    loggerservice.addLog(std::make_unique<Logger>(reservation->getUserId(), reservation->getReservationId(),
                                                  LogMessageType::CHECK_IN));

    std::cout<<"Room Has Been CHECKED-IN Successfully"<<std::endl;
}
/*
    The setCheckOutStatus() is used to handle setting
        checkout status for a user using the reservation id and also to update to display the bill
        for a person
*/
double HotelService::setCheckOutStatus()
{

    int reservation_id;
    std::cout << "Enter Your Reservation Id:";
    std::cin >> reservation_id;
    std::cout << std::endl;

    auto &reservations = hotel.getReservations();
    auto &rooms = hotel.getRooms();

    Reservation *reservation = isValidReservationid(reservation_id, reservations);
    if (!reservation)
    {
        throw ReservationNotFoundException(
            "Reservation ID not found");
    }

    Room *room = findRoomByRoomNumber(reservation->getRoomNumber(), rooms);



    std::cout << "Enter the New Billing Statergy" << std::endl;
    std::cout << "1.Seasonal Billing" << std::endl;
    std::cout << "2.Standard Billing" << std::endl;
    std::cout<<"Enter Your Choice:";
    int choice;
    std::cin >> choice;
    std::unique_ptr<BillingStrategy> billStrategy;
    switch (choice)
    {
    case 1:
        billStrategy = std::make_unique<SeasonalBilling>();
        break;
    case 2:
        billStrategy = std::make_unique<StandardBilling>();
        break;
    default:
        throw InvalidBillingStrategyException(
            "Invalid billing strategy selected");
    }
    double bill = billStrategy->calculateBill(
        reservation,
        room->getRoomCategory()->getRoomBaseRate());


    reservation->setReservationStatus(ReservationStatus::CHECKED_OUT);
    room->setRoomStatus(false);

    loggerservice.addLog(std::make_unique<Logger>(reservation->getUserId(), reservation->getReservationId(),
                                                  LogMessageType::BILLING));
    loggerservice.addLog(std::make_unique<Logger>(reservation->getUserId(), reservation->getReservationId(),
                                                  LogMessageType::CHECK_OUT));
    return bill;
}

/*
    addRoom() function is used to create room and add them to the hotel class
*/

void HotelService::addRoom()
{

    int choice;
    std::cout << "1.Standard\n";
    std::cout << "2.Deluxe\n";
    std::cout << "3.Suite";
    std::cout<<"Enter Your Choice:";
    std::cin >> choice;
    RoomNames category_name;

    switch (choice)
    {
    case 1:
        category_name = RoomNames::STANDARD;
        break;
    case 2:
        category_name = RoomNames::DELUXE;
        break;

    case 3:
        category_name = RoomNames::SUITE;
        break;
    default:
        std::cout << "Invalid category\n";
        return;
    }
    std::shared_ptr<RoomCategory> category = room_catlog.getCategory(category_name);
    auto room = std::make_unique<Room>(category);
    int room_number = room->getRoomNumber();
    hotel.addRoom(std::move(room));
    std::cout << "Room Created Successfully with Room Id: " << room_number << std::endl;
}

/*
    deleteRoom() function is used to delete room
*/
void HotelService::deleteRoom()
{

    int room_number;
    std::cout << "Enter Your Room Number:";
    std::cin >> room_number;

    auto &rooms = hotel.getRooms();
    auto &reservations = hotel.getReservations();
    for (auto &reservation : reservations)
    {
        if (reservation->getRoomNumber() == room_number)
        {
            std::cout << "Room Cannot Be Removed Since It has been Booked" << std::endl;
            return;
        }
    }
    for (auto &room : rooms)
    {
        if (room->getRoomNumber() == room_number)
        {
            if (room->getRoomStatus() == true)
            {
                std::cout << "The Given RoomNumber is Being Currently occupied By guest so it cannot be deleted" << std::endl;
                return;
            }
            else
            {
                hotel.removeRoom(room.get());
                std::cout << "Room Successfully Removed" << std::endl;
                return;
            }
        }
    }
    std::cout << "The Paticular Room Cannot be Found Please Enter a Valid room Number" << std::endl;
}

void HotelService::changePassword()
{
    std::string user_email;
    std::string current_password;
    std::string new_password;
    std::string confirm_password;

    std::cout << "Enter Your User email: ";
    std::cin >> user_email;
    std::cout << "Enter Your Current Password: ";
    std::cin >> current_password;
    AuthService authservice(hotel);

    UserDetails* user = authservice.login(user_email, current_password);

    std::cout << "Enter New Password: ";
    std::cin >> new_password;
    std::cout << "Confirm New Password: ";
    std::cin >> confirm_password;

    if (new_password != confirm_password)
    {
        throw UserException(
            "New passwords does not match"
        );
    }

    if (new_password==current_password)
    {
        throw UserException(
            "New password cannot be the same as current password"
        );
    }
    user->setUserPassword(new_password);
    std::cout << "Password changed successfully!\n";
}

/*
    Generate Report is used to generate reports such as total revenue and
*/
void HotelService::generateReport()
{

    StandardBilling billingStrategy;
    auto &reservations = hotel.getReservations();

    int total_reservation = reservations.size();

    int cancelled_reservations = 0, current_reservations = 0, current_check_in = 0, current_check_out = 0;

    for (auto &reservation : reservations)
    {

        if (reservation->getReservationStatus() == ReservationStatus::CANCELLED)
        {
            cancelled_reservations++;
        }
        else if (reservation->getReservationStatus() == ReservationStatus::CHECKED_IN)
        {
            current_check_in++;
        }
        else if (reservation->getReservationStatus() == ReservationStatus::CHECKED_OUT)
        {
            current_check_out++;
        }
        else if (reservation->getReservationStatus() == ReservationStatus::RESERVED)
        {
            current_reservations++;
        }
    }
    std::cout << "REPORT OF ABC HOTEL" << std::endl;
    std::cout << "Total Number of Reservation: " << total_reservation << std::endl;
    std::cout << "Current Active Reservation:" << current_reservations << std::endl;
    std::cout << "Current Active CHECK-IN:" << current_check_in << std::endl;
    std::cout << "Current Active CHECK_OUT:" << current_check_out << std::endl;
    std::cout << "Cancellations:" << cancelled_reservations << std::endl;
    std::cout<<"Total Revenue :"<<billingStrategy.getTotalRevenue()<<std::endl;

}
