#ifndef HOTELRESERVATIONSYSTEM_BILLING_STRATEGY_H
#define HOTELRESERVATIONSYSTEM_BILLING_STRATEGY_H

#include "models/reservation.h"
/*
BillingStrategy is a class that is used to act as a interface and
    produce easy coupling to provide various types of billing to inherit and use it .It has a virtual function called calculateBill()
*/
class BillingStrategy {

    inline static double total_revenue=0;
public:
    virtual ~BillingStrategy() = default;

    virtual double calculateBill(
        Reservation* reservation,
        double base_rate
    ) = 0;

    double getTotalRevenue();
    void addRevenue(double bill);
};

#endif