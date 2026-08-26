#ifndef HOTELRESERVATIONSYSTEM_BILLING_EXCEPTION_H
#define HOTELRESERVATIONSYSTEM_BILLING_EXCEPTION_H

#include "exceptions/hotel_exception.h"


/* This is an Billing exception class dervied from the hotel exception it has various exceptions
    related to billing such as InvalidBillingStrategyException it arises when the billing stratergy is chosen wrongly*/


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