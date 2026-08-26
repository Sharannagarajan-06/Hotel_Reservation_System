#ifndef HOTELRESERVATIONSYSTEM_SEASONAL_BILLING_H
#define HOTELRESERVATIONSYSTEM_SEASONAL_BILLING_H

#include "models/billing_strategy.h"


/*
    The SeasonalBilling is a dervied class of the BillingStrategy
        which implements the one virtual method of the BillingStrategy class
*/
class SeasonalBilling : public BillingStrategy {
public:
    double calculateBill(
        Reservation* reservation,
        double base_rate
    ) override;
};

#endif