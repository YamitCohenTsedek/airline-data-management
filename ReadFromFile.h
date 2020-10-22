
#ifndef READFROMFILE_H
#define READFROMFILE_H

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "interface.h"
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
#define PLANE_MODELS_COUNTERS "PlaneModelsCounters.txt"
#define EMPLOYEES_TO_FLIGHTS_FILE "EmployeesToFlightsFile.txt"
#define DELIMITER ";"

using namespace std;


class ReadFromFile {

private:
    vector<string> splitByDelimiter(string line);

public:
    vector<vector<string>> loadEmployeesFromFile();

    vector<vector<string>> loadPlanesFromFile();

    vector<vector<string>> loadFlightsFromFile();

    vector<vector<string>> loadCustomersFromFile();

    vector<vector<string>> loadReservationsFromFile();

    vector<vector<string>> loadEmployeesToFlights();
};

#endif // READFROMFILE_H