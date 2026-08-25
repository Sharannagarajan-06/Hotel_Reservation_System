#include "models/standard_billing.h"
#include "models/reservation.h"

#include <chrono>

double StandardBilling::calculateBill(
    Reservation* reservation,
    double base_rate
) {
    auto check_in =
        std::chrono::sys_days{reservation->getCheckIn()};

    auto check_out =
        std::chrono::sys_days{reservation->getCheckOut()};

    int total_days =
        (check_out - check_in).count();

    double total_rate =
        total_days * base_rate;

    double service_charge =
        total_rate * 0.10;

    double tax =
        total_rate * 0.18;

    double final_rate =
        total_rate + service_charge + tax;

    return final_rate;
}