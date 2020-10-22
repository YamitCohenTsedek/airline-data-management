
#include "MyEmployee.h"
#include <string.h>
#include "interface.h"
#include "ReadFromFile.h"
#include "ObjectFromString.h"

// Convert a Jobs enum type to a string type.
string MyEmployee::convertJobToString(Jobs title) {
    switch(title) {
        case MANAGER:
            return "MANAGER";
        case NAVIGATOR:
            return "NAVIGATOR";
        case FLIGHT_ATTENDANT:
            return "FLIGHT_ATTENDANT";
        case PILOT:
            return "PILOT";
        case OTHER:
            return "OTHER";
        default:
            throw std::invalid_argument("The specified job is not valid.");
    }
}

/*
 * The format of EmployeeFile:
 * string employeeID;int seniority;int BirthYear;Jobs title;string employerID;
 */
string MyEmployee::getEmployeeFileFormat () {
    string employeeFileFormat;
    string employeeID = id;
    string strSeniority = to_string(seniority);
    string strBirthYear = to_string(birthYear);
    string strTitle = convertJobToString(title);
    string employerID = getEmployerID();
    employeeFileFormat = employeeID + ";" + strSeniority + ";" + strBirthYear + ";"
        + strTitle + ";" +  employerID + ";\n";
    return employeeFileFormat;
}

// Return true if the employee is available at the specified date, otherwise - return false.
bool MyEmployee::isAvailable(Date flightDate) {
    if (datesToFlights.empty()) {
        return true;
    }
    // If the date doesn't exist in the map keys, the employee is available.
    if (datesToFlights.find(flightDate)!= datesToFlights.end()) {
        return true;
    } else {
        return false;
    }
}

// Update the status of an employee to be not available at the specified date.
void MyEmployee::notAvailableAt(Date flightDate, string flightID) {
    datesToFlights[flightDate] = flightID;
}

// Return true if the employee works in the specified flight, otherwise - return false.
bool MyEmployee::worksInFlight(string flightID) {
    for (map<Date,string>::iterator it = datesToFlights.begin();
         it != datesToFlights.end(); it++) {
        if ((*it).second == flightID) {
            return true;
        }
    }
    return false;
}