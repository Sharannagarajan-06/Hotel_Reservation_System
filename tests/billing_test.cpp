#include <gtest/gtest.h>
#include <chrono>
#include <memory>

#include "models/reservation.h"
#include "models/standard_billing.h"
#include "models/seasonal_billing.h"

class BillingTest : public ::testing::Test
{
protected:
    std::chrono::year_month_day date(
        int year,
        unsigned month,
        unsigned day)
    {
        return std::chrono::year_month_day{
            std::chrono::year{year},
            std::chrono::month{month},
            std::chrono::day{day}};
    }

    std::unique_ptr<Reservation> createReservation(
        unsigned checkInDay,
        unsigned checkOutDay)
    {
        return std::make_unique<Reservation>(
            date(2026, 9, checkInDay),
            date(2026, 9, checkOutDay),
            101,
            1);
    }
};

TEST_F(BillingTest, StandardBillingDoesNotModifyReservation)
{

    auto reservation = createReservation(1, 5);

    auto originalStatus =
        reservation->getReservationStatus();

    StandardBilling billing;

    billing.calculateBill(
        reservation.get(),
        1000);

    EXPECT_EQ(
        reservation->getReservationStatus(),
        originalStatus);
}

TEST_F(BillingTest, SeasonalBillingCalculatesBill)
{

    auto reservation = createReservation(1, 5);

    SeasonalBilling billing;

    double result = billing.calculateBill(
        reservation.get(),
        1000);

    EXPECT_GT(result, 0);
}

TEST_F(BillingTest, SeasonalBillingIsHigherThanStandard)
{

    auto reservation = createReservation(1, 5);

    StandardBilling standardBilling;
    SeasonalBilling seasonalBilling;

    double standardBill =
        standardBilling.calculateBill(
            reservation.get(),
            1000);

    double seasonalBill =
        seasonalBilling.calculateBill(
            reservation.get(),
            1000);

    EXPECT_GT(
        seasonalBill,
        standardBill);
}

TEST_F(BillingTest, SeasonalBillingCalculatesMultipleDayBill)
{

    auto reservation = createReservation(1, 10);

    SeasonalBilling billing;

    double result = billing.calculateBill(
        reservation.get(),
        1000);

    EXPECT_GT(result, 0);
}

TEST_F(BillingTest, SeasonalBillingDoesNotModifyReservation)
{

    auto reservation = createReservation(1, 5);

    auto originalStatus =
        reservation->getReservationStatus();

    SeasonalBilling billing;

    billing.calculateBill(
        reservation.get(),
        1000);

    EXPECT_EQ(
        reservation->getReservationStatus(),
        originalStatus);
}

TEST_F(BillingTest, StandardBillingCalculatesOneDayBill)
{

    auto reservation = createReservation(1, 2);

    StandardBilling billing;

    double result = billing.calculateBill(
        reservation.get(),
        1000);

    EXPECT_DOUBLE_EQ(result, 1280);
}

TEST_F(BillingTest, StandardBillingCalculatesMultipleDayBill)
{

    auto reservation = createReservation(1, 5);

    StandardBilling billing;

    double result = billing.calculateBill(
        reservation.get(),
        1000);

    EXPECT_DOUBLE_EQ(result, 5120);
}

TEST_F(BillingTest, DifferentRoomRatesProduceDifferentBills)
{

    auto reservation = createReservation(1, 5);

    StandardBilling billing;

    double standardRate = billing.calculateBill(
        reservation.get(),
        1000);

    double deluxeRate = billing.calculateBill(
        reservation.get(),
        2000);

    EXPECT_DOUBLE_EQ(standardRate, 5120);
    EXPECT_DOUBLE_EQ(deluxeRate, 10240);
}
