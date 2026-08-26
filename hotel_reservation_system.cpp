#include <iostream>
#include <chrono>
#include "models/room_category.h"
#include "models/rooms.h"
#include "enums/room_name.h"
#include "models/guest_details.h"
#include "models/hotel.h"
#include "models/reservation.h"
#include "services/hotel_service.h"
#include "services/auth_service.h"
#include "models/admin_details.h"
#include "services/logger_service.h"
#include "exceptions/hotel_exception.h"
#include "exceptions/user_exception.h"
#include "exceptions/room_exception.h"
#include "exceptions/reservation_exception.h"
#include "exceptions/billing_exception.h"
#include "exceptions/date_exception.h"

void guestMenu(Hotel &hotel, LoggerService &loggerservice)
{

    bool exit_flag = false;
    HotelService hotelservice(hotel, loggerservice);
    while (!exit_flag)
    {
        try
        {
            std::cout << "1.Reserve Room " << std::endl;
            std::cout << "2.Cancel Reserved Room" << std::endl;
            std::cout << "3.Change Password" << std::endl;
            std::cout << "4.Exit" << std::endl;
            std::cout << "Enter You Choice";

            int choice;
            std::cin >> choice;

            switch (choice)
            {

            case 1:
                try
                {
                    hotelservice.searchRooms();
                }
                catch (const RoomUnavailableException &e)
                {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 2:
                try
                {
                    hotelservice.cancelReservedRoom();
                }
                catch (const ReservationNotFoundException &e)
                {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 3:
                try
                {
                    hotelservice.changePassword();
                }
                catch (const ReservationNotFoundException &e)
                {
                    std::cerr << e.what() << std::endl;
                }

            case 4:

                exit_flag = true;
                break;
            default:
                std::cout << "Enter the Valid Intput" << std::endl;
                break;
            }
        }
        catch (const HotelException &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

bool verifyAdmin(Hotel &hotel)
{

    try
    {
        std::string admin_email, admin_password;
        std::cout << "Login Using Your Admin Account" << std::endl;
        std::cout << "Enter the Email:";
        std::cin >> admin_email;

        std::cout << "Enter the Password:";
        std::cin >> admin_password;

        AuthService authservice(hotel);
        UserDetails *user = authservice.login(admin_email, admin_password);

        if (!user)
        {
            throw AuthenticationException(
                "Invalid email or password");
        }

        if (!authservice.isAdmin(user))
        {
            throw UnauthorizedException(
                "User does not have admin privileges");
        }
    }
    catch (const AuthenticationException &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}
void adminMenu(Hotel &hotel, LoggerService &loggerservice)
{
    bool exit_flag = false;
    HotelService hotelservice(hotel, loggerservice);

    while (!exit_flag)
    {
        try
        {
            // system("cls");
            std::cout << "1.Add a Room" << std::endl;
            std::cout << "2.Delete a Room" << std::endl;
            std::cout << "3.Reserve Room for a Guest" << std::endl;
            std::cout << "4.Handle Check-in for Guest" << std::endl;
            std::cout << "5.Handle Check-out for Guest" << std::endl;
            std::cout << "6.Generate Report" << std::endl;
            std::cout << "7.See Log Messages" << std::endl;
            std::cout << "8.Exit" << std::endl;
            std::cout << "Enter Your Choice:";
            int choice;
            std::cin >> choice;

            switch (choice)
            {

            case 1:
                hotelservice.addRoom();
                break;
            case 2:
                try
                {
                    hotelservice.deleteRoom();
                }
                catch (const RoomNotFoundException &e)
                {
                    std::cerr << e.what() << std::endl;
                }

                break;
            case 3:
                try
                {
                    hotelservice.searchRooms();
                }
                catch (const InvalidDateException &e)
                {
                    std::cerr << "Invalid date format: " << e.what() << std::endl;
                }
                catch (const DateException &e)
                {
                    std::cerr << "Invalid date: " << e.what() << std::endl;
                }
                catch (const RoomUnavailableException &e)
                {
                    std::cerr << "Room unavailable: " << e.what() << std::endl;
                }
                break;
            case 4:
                try
                {
                    hotelservice.setCheckInStatus();
                }
                catch (const RoomNotFoundException &e)
                {
                    std::cerr << e.what() << std::endl;
                }

                break;
            case 5:
                try
                {
                    hotelservice.setCheckOutStatus();
                }
                catch (const RoomNotFoundException &e)
                {
                    std::cerr << e.what() << std::endl;
                }

                break;
            case 6:
                hotelservice.generateReport();
                break;
            case 7:

                loggerservice.printLogs();

                break;
            case 8:
                exit_flag = true;
                break;
            default:
                std::cout << "Enter the Valid output" << std::endl;
                break;
            }
        }
        catch (const HotelException &e)
        {

            std::cerr << e.what() << std::endl;
        }
    }
}
void showMainMenu(Hotel &hotel, LoggerService &loggerservice)
{

    bool exit_flag = false;
    while (!exit_flag)
    {

        std::cout << "Welcome to ABC Hotel" << std::endl;
        std::cout << "1.Admin Options" << std::endl;
        std::cout << "2.Customer Options" << std::endl;
        std::cout << "3.Exit" << std::endl;
        std::cout << "Enter Your Choice:";

        int choice;
        std::cin >> choice;
        std::cout << std::endl;
        switch (choice)
        {

        case 1:
        {
            try
            {
                if (verifyAdmin(hotel))
                {
                    adminMenu(hotel, loggerservice);
                }
                else
                {
                    std::cout << "Login failed" << std::endl;
                }
            }
            catch (const AuthenticationException &e)
            {
                std::cerr << e.what() << std::endl;
            }

            break;
        }
        case 2:
            try
            {
                guestMenu(hotel, loggerservice);
            }
            catch (const HotelException &e)
            {
                std::cerr << e.what() << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << "System Error: "
                          << e.what()
                          << std::endl;
            }
            break;
        case 3:
            exit_flag = true;
            break;
        default:
            std::cout << "Enter the Valid output" << std::endl;
            break;
        }
    }
}
int main()
{
    try
    {
        Hotel hotel;
        LoggerService loggerservice;
        auto admin = std::make_unique<AdminDetails>("Sharan",
                                                    "9345480377",
                                                    "admin@gmail.com",
                                                    "123");
        hotel.adduser(std::move(admin));
        showMainMenu(hotel, loggerservice);
    }
    catch (const HotelException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "System Error: "
                  << e.what()
                  << std::endl;
    }

    return 0;
}