
#ifndef WRITEINFILE_H
#define WRITEINFILE_H

#include <iostream>
#include <fstream>
#include "interface.h"
#include "GetID.h"
#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyCustomer.h"
#include "MyReservation.h"

#define EMPLOYEE_FILE "EmployeeFile.txt"
#define CUSTOMER_FILE "CustomerFile.txt"
#define FLIGHT_FILE "FlightFile.txt"
#define PLANE_FILE "PlaneFile.txt"
#define RESERVATION_FILE "ReservationFile.txt"
#define EMPLOYEES_TO_FLIGHTS_FILE "EmployeesToFlightsFile.txt"
#define DELIMITER ";"


class WriteInFile {

public:
    // Write the specified ID in the specified file.
    void writeIDInFile(string id, string fileName);

    // Write the information about the specified employee in a file.
    void writeInEmployeeFile(MyEmployee* employee);

    // Write the information about the specified plane in a file.
    void writeInPlaneFile(MyPlane* plane);

    // Write the information about the specified flight in a file.
    void writeInFlightFile(MyFlight* flight);

    // Write the information about the specified customer in a file.
    void writeInCustomerFile(MyCustomer* customer);

    // Write the information about the specified reservation in a file.
    void writeInReservationFile(MyReservation* reservation);

    // Write the information about the specified employee and his flights in a file.
    void writeInEmployeesToFlightsFile(string EmployeeID, string date, string flightID);
};

#endif // WRITEINFILE_H