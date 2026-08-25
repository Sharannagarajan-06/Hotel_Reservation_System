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
void guestMenu(Hotel& hotel,LoggerService& loggerservice){

    bool exit_flag = false;
    HotelService hotelservice(hotel,loggerservice);
    while(!exit_flag){

        system("cls");
        std::cout<<"1.Reserve Room "<<std::endl;
        std::cout<<"2.Cancel Reserved Room"<<std::endl;
        std::cout<<"3.Exit"<<std::endl;

        int choice;
        std::cin>>choice;

         switch(choice){

            case 1:
                hotelservice.searchRooms();
                break;
            case 2:
                hotelservice.cancelReservedRoom();
             case 3:
                exit_flag=true;
                break;
            default:
                std::cout<<"Enter the Valid output"<<std::endl;
                 break;
         }
    }
}

bool verifyAdmin(Hotel& hotel){

    std::string admin_email,admin_password;

    std::cout<<"Enter the Email:";
    std::cin>>admin_email;

    std::cout<<"Enter the Password:";
    std::cin>>admin_password;


    AuthService authservice(hotel) ;
    UserDetails* user= authservice.login(admin_email,admin_password);


    if(user!=NULL && authservice.isAdmin(user)) return true;
    return false;

}
void adminMenu(Hotel& hotel,LoggerService& loggerservice){
    bool exit_flag = false;
    HotelService hotelservice(hotel,loggerservice);

     while(!exit_flag){

        //system("cls");
        std::cout<<"1.Add a Room"<<std::endl;
        std::cout<<"2.Delete a Room"<<std::endl;
        std::cout<<"3.Reserve Room for a Guest"<<std::endl;
        std::cout<<"4.Handle Check-in for Guest"<<std::endl;
        std::cout<<"5.Handle Check-out for Guest"<<std::endl;
        std::cout<<"6.Generate Report"<<std::endl;
        std::cout<<"7.See Log Messages"<<std::endl;
        std::cout<<"8.Exit"<<std::endl;

        int choice;
        std::cin>>choice;

         switch(choice){

            case 1:
                hotelservice.addRoom();
                break;
            case 2:
                hotelservice.deleteRoom();
                break;
            case 3:
                hotelservice.searchRooms();
                break;
             case 4:
                hotelservice.setCheckInStatus();
                break;
            case 5:
                hotelservice.setCheckOutStatus();
                break;
            case 6:
                 hotelservice.generateReport();
                break;
            case 7:
                loggerservice.printLogs();
                break;
            case 8:
                  exit_flag=true;
                break;
            default:
                std::cout<<"Enter the Valid output"<<std::endl;
                 break;
         }
    }
}
void showMainMenu(Hotel& hotel,LoggerService& loggerservice){

    bool exit_flag = false;
    while(!exit_flag){
        system("cls");
        std::cout<<"Welcome to ABC Hotel"<<std::endl;
        std::cout<<"1.Admin Options"<<std::endl;
        std::cout<<"2.Customer Options"<<std::endl;
        std::cout<<"3.Exit"<<std::endl;
        std::cout<<"Eneter Your Choice:";
        std::cout<<std::endl;
        int choice;
        std::cin>>choice;

         switch(choice){

            case 1:
                if(verifyAdmin(hotel)){
                    adminMenu(hotel,loggerservice);
                }
                else{
                    std::cout<<"Login failed";
                }
                break;
            case 2:
                guestMenu(hotel,loggerservice);
                break;
            case 3:
                exit_flag=true;
                break;
            default:
                std::cout<<"Enter the Valid output"<<std::endl;
                 break;
         }

    }
}
int main(){

   Hotel hotel;
    LoggerService loggerservice;
    auto admin= std::make_unique<AdminDetails>("Sharan",
    "9345480377",
    "admin@gmail.com",
     "123");
    hotel.adduser(std::move(admin));
   showMainMenu(hotel,loggerservice);


}