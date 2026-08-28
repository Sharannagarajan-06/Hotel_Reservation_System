//
// Created by asus on 8/26/2026.
//

#include "models/billing_strategy.h"

double BillingStrategy::getTotalRevenue()
{
    return total_revenue;
}
void BillingStrategy::addRevenue(double bill)
{
    total_revenue += bill;
}