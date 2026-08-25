#ifndef HOTELRESERVATIONSYSTEM_BILLING_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_BILLING_EXCEPTION_H

#include "exceptions/hotel_exception.h"

class BillingException:public HotelException {
public:
    explicit BillingException(const std::string& message)
        : HotelException(message) {
    }

    ~BillingException()override= default;
};


class InvalidBillingStrategyException: public BillingException {


public:
    explicit InvalidBillingStrategyException
    (const std::string& message): BillingException(message) {
    }

    ~InvalidBillingStrategyException() override = default;
};

#endif