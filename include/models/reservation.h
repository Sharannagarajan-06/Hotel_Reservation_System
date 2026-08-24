//
// Created by asus on 8/24/2026.
//

#ifndef HOTELRESERVATIONSYSTEM_RESERVATION_H
#define HOTELRESERVATIONSYSTEM_RESERVATION_H

#include <chrono>
#include "enums/reservation_status.h"
class Reservation {

private:

    inline static int next_reservation_id=1;
    int reservation_id;
    std::chrono::year_month_day check_in;
    std::chrono::year_month_day check_out;
    ReservationStatus reservation_status;

public:

    Reservation(
    std::chrono::year_month_day check_in,
    std::chrono::year_month_day check_out);

	std::chrono::year_month_day getCheckIn();

	std::chrono::year_month_day getCheckout();

	ReservationStatus getReservationStatus();
    void setReservationStatus(ReservationStatus reservation_status);

    int getReservationId();

};


#endif //HOTELRESERVATIONSYSTEM_RESERVATION_H