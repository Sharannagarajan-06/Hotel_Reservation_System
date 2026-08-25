//
// Created by asus on 8/24/2026.
//

#include "models/availabilityindex.h"

void  AvailabilityIndex::updateAvailability(int roomId,
    std::chrono::year_month_day new_check_in,
    std::chrono::year_month_day new_check_out){

        availability[roomId].insert({new_check_in,new_check_out});

}
void AvailabilityIndex::removeAvailability(int roomId,
    std::chrono::year_month_day new_check_in,
    std::chrono::year_month_day new_check_out){

    availability[roomId].erase({new_check_in,new_check_out});

}
bool AvailabilityIndex::isFree(int roomId,
    std::chrono::year_month_day new_check_in,
    std::chrono::year_month_day new_check_out){

        for(auto date_range : availability[roomId]){
            auto existing_check_in = date_range.first;
            auto existing_check_out = date_range.second;

            if(new_check_in < existing_check_out && new_check_out > existing_check_in) return false;
       }
    return true;
}