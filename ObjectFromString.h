
#ifndef OBJECTFROMSTRING_H
#define OBJECTFROMSTRING_H

#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyCustomer.h"
#include "MyReservation.h"


class ObjectFromString {

public:
    // Convert a string type to a Jobs enum type.
    Jobs convertStringToJob(string jobStr);

    // Return a pointer to the employee with the given information.
    MyEmployee* getStringReturnEmployee(vector<string> employeeInfo, Employee* emp);

    // Return a pointer to the plane with the given information.
    MyPlane* getStringReturnPlane(vector<string> planeInfo);

    // Return a pointer to the flight with the given information.
    MyFlight* getStringReturnFlight(vector<string> flightInfo,
        list<Employee*> assignedCrew, int maxFirstClass, int maxSecondClass);

    // Return a pointer to the customer with the given information.
    MyCustomer* getStringReturnCustomer(vector<string> customerInfo);

    // Return a pointer to the reservation with the given information.
    MyReservation* getStringReturnReservation(vector<string>
        reservationInfo, Customer* customer, Flight* flight);
};

#endif // OBJECTFROMSTRING_H