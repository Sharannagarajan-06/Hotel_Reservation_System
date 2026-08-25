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

void guestMenu(){

    bool exit_flag = false;
    while(!exit_flag){

        system("cls");
        std::cout<<"1.Reserve Room for a Guest"<<std::endl;
        std::cout<<"2.Handle Check-in for Guest"<<std::endl;
        std::cout<<"3.Exit"<<std::endl;

        int choice;
        std::cin>>choice;

         switch(choice){

            case 1:
                //Reserve room
                break;
            case 2:
                //checkin
                break;
             case 3:
                //exit
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
void adminMenu(Hotel& hotel){
    bool exit_flag = false;

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
        HotelService hotelservice(hotel);
         switch(choice){

            case 1:
                hotelservice.addRoom();
                break;
            case 2:
                hotelservice.deleteRoom();
                break;
            case 3:
                //Reserve room
                break;
             case 4:
                //checkin
                break;
            case 5:
                //checkout
                break;
            case 6:
                 //report
                break;
            case 7:
                //log msg
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
void showMainMenu(Hotel& hotel){

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
                    adminMenu(hotel);
                }
                else{
                    std::cout<<"Login failed";
                }
                break;
            case 2:
                guestMenu();
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
    AdminDetails* admin= new AdminDetails("Sharan",
    "9345480377",
    "admin@gmail.com",
     "123");
    hotel.adduser(admin);
   showMainMenu(hotel);


}