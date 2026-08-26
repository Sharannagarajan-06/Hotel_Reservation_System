#ifndef HOTELRESERVATIONSYSTEM_STANDARD_BILLING_H
#define HOTELRESERVATIONSYSTEM_STANDARD_BILLING_H

#include "models/billing_strategy.h"

/*
    The StandardBilling is a dervied class of the BillingStrategy 
        which implements the one virtual method of the BillingStrategy class
*/

class StandardBilling : public BillingStrategy {
public:
    double calculateBill(
        Reservation* reservation,
        double base_rate
    ) override;
};

#endif