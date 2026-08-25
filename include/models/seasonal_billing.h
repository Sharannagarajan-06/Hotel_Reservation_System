#ifndef HOTELRESERVATIONSYSTEM_SEASONAL_BILLING_H
#define HOTELRESERVATIONSYSTEM_SEASONAL_BILLING_H

#include "models/billing_strategy.h"

class SeasonalBilling : public BillingStrategy {
public:
    double calculateBill(
        Reservation* reservation,
        double base_rate
    ) override;
};

#endif