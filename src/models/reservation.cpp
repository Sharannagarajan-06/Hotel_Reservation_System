//
// Created by asus on 8/24/2026.
//

#include <chrono>
#include "models/reservation.h"
#include "enums/reservation_status.h"

Reservation::Reservation(
    std::chrono::year_month_day check_in,
    std::chrono::year_month_day check_out,
    int room_number,int guest_id){
        this->reservation_id=Reservation::next_reservation_id++;
        this->check_in=check_in;
        this->check_out=check_out;
        this->reservation_status=ReservationStatus::RESERVED;
        this->room_number=room_number;
        this->guest_id=guest_id;
    }

        std::chrono::year_month_day Reservation::getCheckIn(){
            return this->check_in;
        }

        std::chrono::year_month_day Reservation::getCheckout(){
            return this->check_out;
        }

        ReservationStatus Reservation::getReservationStatus(){
            return this->reservation_status;
        }

        void Reservation::setReservationStatus(ReservationStatus reservation_status){
            this->reservation_status=reservation_status;
        }

        int Reservation::getReservationId(){
            return this->reservation_id;
        }

