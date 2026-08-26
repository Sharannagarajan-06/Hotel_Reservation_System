# Test Cases
Evaluated Various test cases under different suitenames and files to verify unit testing
all  the test cases ran were passed successfully
## 1. ConcurrencyTest

* `SameRoomCannotBeDoubleBooked`

![](/media/image1.png)
## 2. BillingTest

* `StandardBillingDoesNotModifyReservation`
* `SeasonalBillingCalculatesBill`
* `SeasonalBillingIsHigherThanStandard`
* `SeasonalBillingCalculatesMultipleDayBill`
* `SeasonalBillingDoesNotModifyReservation`
* `StandardBillingCalculatesOneDayBill`
* `StandardBillingCalculatesMultipleDayBill`
* `DifferentRoomRatesProduceDifferentBills`
  ![](/media/image2.png)
* ![](/media/image3.png)
## 3. AvailabilityTest

* `NewRoomIsAvailable`
* `RoomBecomesUnavailableAfterBooking`
* `SameDatesCannotBeBookedAgain`
* `OverlappingBookingIsRejected`
* `BookingBeforeExistingBookingIsAllowed`
* `BookingAfterExistingBookingIsAllowed`
* `AdjacentBookingIsAllowed`
* `DifferentRoomsCanBeBookedForSameDates`
* `CancelledBookingMakesRoomAvailable`
* `DifferentDateRangesCanUseSameRoom`
  ![](/media/image4.png)
* 
## 4. HotelServiceTest

* `FindsValidReservation`
* `InvalidReservationIdReturnsNull`
* `FindsExistingRoom`
* `InvalidRoomNumberReturnsNull`
* `ReservationInitiallyReserved`
* `ReservationCanBeMarkedCheckedIn`
* `ReservationCanBeCancelled`
* `ReservationCanBeCheckedOut`
* `RoomStatusChangesIndependently`
* `ReservationStoresCorrectRoomAndUser`
  ![](/media/image5.png)
## 5. AuthTest

* `ValidGuestLoginReturnsUser`
* `ValidAdminLoginReturnsUser`
* `InvalidEmailThrowsException`
* `InvalidPasswordThrowsException`
* `InvalidEmailAndPasswordThrowsException`
* `EmptyEmailThrowsException`
* `EmptyPasswordThrowsException`
* `AdminIsRecognizedAsAdmin`
* `GuestIsNotRecognizedAsAdmin`
* `LoginReturnsCorrectUser`
* `DifferentUsersCanLoginIndependently`
* `WrongPasswordDoesNotAuthenticateAdmin`
* `WrongPasswordDoesNotAuthenticateGuest`
  ![](/media/image6.png)
## 6. UserTest

* `GuestCanBeCreated`
* `GuestStoresCorrectName`
* `GuestStoresCorrectPhoneNumber`
* `GuestStoresCorrectEmail`
* `GuestGetsValidUserId`
* `DifferentGuestsHaveDifferentIds`
* `AdminCanBeCreated`
* `AdminStoresCorrectName`
* `AdminStoresCorrectEmail`
* `AdminGetsValidUserId`
* `GuestAndAdminHaveDifferentIds`
* `GuestCanBeStoredUsingBaseClassPointer`
* `AdminCanBeStoredUsingBaseClassPointer`
  ![](/media/image7.png)
## 7. RoomTest

* `RoomCreatedSuccessfully`
* `RoomHasValidRoomNumber`
* `RoomNumbersAreUnique`
* `RoomStoresCorrectCategory`
* `RoomInitiallyAvailable`
* `RoomCanBeMarkedOccupied`
* `RoomCanBeMarkedAvailable`
* `MultipleRoomsCanUseSameCategory`
* `ChangingOneRoomStatusDoesNotChangeAnother`
  ![](/media/image8.png)
## 8. ReservationTest

* `CreateReservationSuccessfully`
* `StoresCorrectRoomNumber`
* `StoresCorrectUserId`
* `StoresCorrectCheckInDate`
* `StoresCorrectCheckOutDate`
* `InitialStatusShouldBeReserved`
* `ReservationShouldHaveValidId`
* `ReservationsShouldHaveUniqueIds`
* `CanCancelReservation`
* `CanCheckInReservation`
* `CanCheckOutReservation`
* `InvalidDateRangeThrowsException`
* `SameCheckInAndCheckOutDateThrowsException`
  ![](/media/image9.png)

## Performance insights 
    
For The Hotel Reservation Management System The availability 
look up time complexity is O( MxN )
    
NOTE:   
* M=Count of the rooms
* N=the Number of Bookings of each indviual rooms 

``` bash
          //map<roomId, set< checkIn , checkOut >>
    std::map<int,std::set<std::pair<std::chrono::year_month_day,std::chrono::year_month_day>>>availability;  
 ```
Inside the availabilty look is kept like this that is map which contains a set  of pair the 
each pair represent the start and end range of the bookings and we iterate over the bookings and then find the free hotel rooms 
    
```bash
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
```
## Challenges faced 

  * The Main Challange for me was finding the right methods attributes for each classes and connecting all the dots and coming to a conclusion 
  * The Second Challange is that Balancing time between ideation and coding i should have needed to spend more time in coding which took me more than that i planned of 
  * Overall i should have planned better and executed it better
  * In the techincal part the problem was on finding the right naming conventions was tough even though i got used to it now
