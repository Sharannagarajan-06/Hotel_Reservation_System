# HOTEL RESERVATION MANAGEMENT SYSTEM
The Hotel Reservation System is a C++ based application for managing hotel rooms and reservations.

The system supports:

* Guest and Admin users
* User authentication
* Room management
* Room categories
* Room availability checking
* Date-range based reservations
* Reservation cancellation
* Check-in and check-out
* Billing calculation
* Concurrent booking handling
* Unit testing using Google Test
* Generating Report
* Log 

The system also checks for overlapping reservations so that the same room cannot be double booked.

---

## FOLDER STRUCTURE

```
    
└── HotelReservationSystem/
    ├── include/
    │   ├── services/
    │   │   ├── auth_service.h
    │   │   ├── hotel_service.h
    │   │   └── logger_service.h
    │   ├── models/
    │   │   ├── admin_details.h
    │   │   ├── availabilityindex.h
    │   │   ├── billing_strategy.h
    │   │   ├── guest_details.h
    │   │   ├── hotel.h
    │   │   ├── logger.h
    │   │   ├── reservation.h
    │   │   ├── rooms.h
    │   │   ├── room_category.h
    │   │   ├── room_catlog.h
    │   │   ├── seasonal_billing.h
    │   │   ├── standard_billing.h
    │   │   └── user_details.h
    │   ├── exceptions/
    │   │   ├── billing_exception.h
    │   │   ├── date_exception.h
    │   │   ├── hotel_exception.h
    │   │   ├── reservation_exception.h
    │   │   ├── room_exception.h
    │   │   └── user_exception.h
    │   └── enums/
    │       ├── .gitkeep
    │       ├── log_message_type.h
    │       ├── reservation_status.h
    │       ├── room_name.h
    │       └── user_roles.h
    ├── src/
    │   ├── services/
    │   │   ├── auth_service.cpp
    │   │   ├── hotel_service.cpp
    │   │   └── logger_service.cpp
    │   └── models/
    │       ├── admin_details.cpp
    │       ├── availabilityindex.cpp
    │       ├── billing_strategy.cpp
    │       ├── guest_details.cpp
    │       ├── hotel.cpp
    │       ├── logger.cpp
    │       ├── reservation.cpp
    │       ├── rooms.cpp
    │       ├── room_category.cpp
    │       ├── room_catlog.cpp
    │       ├── seasonal_billing.cpp
    │       ├── standard_billing.cpp
    │       └── user_details.cpp
    ├── media/
    │   ├── image1.png
    │   ├── image2.png
    │   ├── image3.png
    │   ├── image4.png
    │   ├── image5.png
    │   ├── image6.png
    │   ├── image7.png
    │   ├── image8.png
    │   └── image9.png
    ├── tests/
    │   ├── auth_service_test.cpp
    │   ├── availability_index_test.cpp
    │   ├── billing_test.cpp
    │   ├── concurreny_test.cpp
    │   ├── hotel_reservation_system.cpp
    │   ├── hotel_service_test.cpp
    │   ├── reservation_test.cpp
    │   ├── room_tests.cpp
    │   ├── user_tests.cpp
    │   └── CMakeLists.txt
    ├── .gitignore
    ├── CMakeLists.txt
    ├── hotel_reservation_system.cpp
    ├── README.md
    └── Report.md
```
The above is the folder structure of the project
* ```include/``` – Contains all header files used in the project
* ```src/``` – Contains the implementation (.cpp) files.
* ```media/``` – Contains images used for the project documentation 
* ```tests/``` – Contains the Google Test test cases for different components of the system.
* ```CMakeLists.txt``` – Main CMake configuration used to build the project.
* ```hotel_reservation_system.cpp``` – Main entry point of the application.
* ```README.md``` – Project documentation and instructions.
* ```Report.md``` – Detailed project report containing testing results, observations, performance insights, and challenges.
---

## TOOLS & TECHNOLOGIES

|Category|Tool / Technology|
|--------|------------|
|Programming Language|C++20|
|Build System|CMake|
|Version Control|Git|
|Testing Framework|Google Test (GTest)|
---
## BUILD & RUN INSTRUCTIONS

### 1. Create the build directory

```
mkdir build
cd build
```
### 2. Configure the project using CMake
```
cmake ..
```
### 3. Build the project
```
cmake --build .
```
### 4.Run the application

```
./hotel_reservation_system.exe
```
## RUNNING TESTS
After building the project, run the test executable from the ```build``` directory uisng

```
    build/tests/HotelTests.exe 
```
