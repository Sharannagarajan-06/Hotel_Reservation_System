#ifndef HOTELRESERVATIONSYSTEM_STANDARD_BILLING_H
#define HOTELRESERVATIONSYSTEM_STANDARD_BILLING_H

#include "models/billing_strategy.h"

class StandardBilling : public BillingStrategy {
public:
    double calculateBill(
        Reservation* reservation,
        double base_rate
    ) override;
};

#endif