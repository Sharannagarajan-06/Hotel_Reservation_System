#include "models/seasonal_billing.h"
#include "models/reservation.h"
#include <iostream>
#include <chrono>

double SeasonalBilling::calculateBill(
    Reservation *reservation,
    double base_rate)
{
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
        2 * (total_rate + service_charge + tax);

    std::cout << "Total Room Rate:" << total_rate << std::endl;
    std::cout << "Service charges:" << service_charge << std::endl;
    std::cout << "Tax" << tax << std::endl;
    std::cout << "Total" << final_rate << std::endl;
    addRevenue(final_rate);
    return final_rate;
}