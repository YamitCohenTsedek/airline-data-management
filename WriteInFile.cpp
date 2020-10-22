
#include "WriteInFile.h"
#include "interface.h"
#include "MyEmployee.h"
#include "MyCustomer.h"
#include <fstream>

using namespace std;

// Write the specified ID in the specified file.
void WriteInFile::writeIDInFile(string id, string fileName) {
    fstream myFile;
    myFile.open(fileName);
    myFile << id << "\n";
}

// Write the information about the specified employee in a file.
void WriteInFile::writeInEmployeeFile(MyEmployee* employee) {
    ofstream myFile(EMPLOYEE_FILE, std::ios::app);
    /* 
     * The format of EmployeeFile:
     * id;seniority;birthYear;title;employerID;
     */
    if (myFile.is_open()) {
        myFile << employee->getEmployeeFileFormat();
    }
    myFile.close();
}

// Write the information about the specified customer in a file.
void WriteInFile::writeInCustomerFile(MyCustomer* customer) {
    ofstream myFile(CUSTOMER_FILE, std::ios::app);
    if (myFile.is_open()) {
        myFile << customer->getCustomerFileFormat();
    }
    myFile.close();
}

// Write the information about the specified flight in a file.
void WriteInFile::writeInFlightFile(MyFlight* flight) {
    ofstream myFile(FLIGHT_FILE, std::ios::app);
    if (myFile.is_open()) {
        myFile << flight->getFlightFileFormat();
    }
    myFile.close();
}

// Write the information about the specified plane in a file.
void WriteInFile::writeInPlaneFile(MyPlane* plane) {
    ofstream myFile(PLANE_FILE, std::ios::app);
    if (myFile.is_open()) {
        myFile << plane->getPlaneFileFormat();
    }
    myFile.close();
}

// Write the information about the specified reservation in a file.
void WriteInFile::writeInReservationFile (MyReservation* reservation) {
    ofstream myFile(RESERVATION_FILE, std::ios::app);
    if (myFile.is_open()) {
        myFile << reservation->getReservationFileFormat();
    }
    myFile.close();
}

// Write the information about the specified employee and his flights in a file.
void WriteInFile::writeInEmployeesToFlightsFile (string employeeID, string date, string flightID) {
    ofstream myFile(EMPLOYEES_TO_FLIGHTS_FILE, std::ios::app);
    myFile << employeeID << DELIMITER << date <<
           DELIMITER << flightID << DELIMITER << "\n";
}