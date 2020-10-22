
#ifndef MYEMPLOYEE_H
#define MYEMPLOYEE_H

#include "interface.h"
#include "GetID.h"
#include <string.h>
#include <vector>
#include "MyFlight.h"

/*
 * An employee can be a manager, a navigator, a flight attendant, a pilot or other.
 * Each employee has seniority, a birth year, and a direct employer.
 */
class MyEmployee : public Employee {
private:
    string id;
    int seniority;
    int birthYear;
    string employerId;
    Employee* pToEmployer;
    Jobs title;
    map<Date, string> datesToFlights;

public:
    MyEmployee(string uniqueId, int employeeSeniority, int birth_year,
        Jobs employeeTitle, string employer_id, Employee* employer){
        id = uniqueId;
        seniority = employeeSeniority;
        birthYear = birth_year;
        employerId = employer_id;
        pToEmployer = employer;
        title = employeeTitle;
    }

    string getID() {
        return id;
    }

    int getSeniority() {
        return seniority;
    }

    int getBirthYear() {
        return birthYear;
    }

    Jobs getTitle() {
        return title;
    }

    string getEmployerID() {
        return employerId;
    }

    Employee* getEmployer() {
        if (pToEmployer == NULL) {
            throw std::invalid_argument("There is no employer to the specified employee.");
        }
        return pToEmployer;
    }

    // Convert a Jobs enum type to a string type.
    string convertJobToString(Jobs title);

    // Get the file format of the employee as a string.
    string getEmployeeFileFormat();

    // Return true if the employee is available at the specified date, otherwise - return false.
    bool isAvailable(Date flightDate);

    // Update the status of an employee to be not available at the specified date.
    void notAvailableAt(Date flightDate, string flightID);

    // Return true if the employee works in the specified flight, otherwise - return false.
    bool worksInFlight(string flightID);

    // Destructor.
    ~MyEmployee(){}

};

#endif // MYEMPLOYEE_H