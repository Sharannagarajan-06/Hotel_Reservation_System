#ifndef HOTELRESERVATIONSYSTEM_BILLING_STRATEGY_H
#define HOTELRESERVATIONSYSTEM_BILLING_STRATEGY_H

class Reservation;

class BillingStrategy {
public:
    virtual ~BillingStrategy() = default;

    virtual double calculateBill(
        Reservation* reservation,
        double base_rate
    ) = 0;
};

#endif