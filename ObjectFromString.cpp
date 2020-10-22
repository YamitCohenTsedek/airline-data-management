
#include "ObjectFromString.h"

// Convert a string type to a Jobs enum type.
Jobs ObjectFromString::convertStringToJob(string jobStr) {
    if (jobStr == "MANAGER") {
        return MANAGER;
    }
    else if (jobStr == "NAVIGATOR") {
        return NAVIGATOR;
    }
    else if (jobStr == "FLIGHT_ATTENDANT") {
        return FLIGHT_ATTENDANT;
    }
    else if (jobStr == "PILOT") {
        return PILOT;
    }
    else if (jobStr == "OTHER") {
        return OTHER;
    }
}

// Return a pointer to the employee with the given information.
MyEmployee* ObjectFromString::getStringReturnEmployee(vector<string> employeeInfo,
        Employee* emp) {
    string employeeID = employeeInfo.at(0);
    int strSeniority = stoi(employeeInfo.at(1));
    int strBirthYear = stoi(employeeInfo.at(2));
    Jobs title = convertStringToJob(employeeInfo.at(3));
    string employerID = employeeInfo.at(4);
    return new MyEmployee(employeeID, strSeniority,
        strBirthYear, title, employerID, emp);
}

// Return a pointer to the plane with the given information.
MyPlane* ObjectFromString::getStringReturnPlane(vector<string> planeInfo) {
    string planeID = planeInfo.at(0);
    int model_number = stoi(planeInfo.at(1));
    map<Jobs,int> crewMap;
    crewMap[MANAGER] = stoi(planeInfo.at(2));
    crewMap[NAVIGATOR] = stoi(planeInfo.at(3));
    crewMap[FLIGHT_ATTENDANT] = stoi(planeInfo.at(4));
    crewMap[PILOT] = stoi(planeInfo.at(5));
    crewMap[OTHER] = stoi(planeInfo.at(6));
    map<Classes,int> max_passengers;
    max_passengers[FIRST_CLASS] = stoi(planeInfo.at(7));
    max_passengers[SECOND_CLASS] = stoi(planeInfo.at(8));
    return new MyPlane(planeID, model_number, crewMap, max_passengers);
}

// Return a pointer to the flight with the given information.
MyFlight* ObjectFromString::getStringReturnFlight(vector<string> flightInfo,
        list<Employee*> assignedCrew, int maxFirstClass, int maxSecondClass) {
    string flightID = flightInfo.at(0);
    int model = stoi(flightInfo.at(1));
    Date date(flightInfo.at(2));
    string source = flightInfo.at(3);
    string destination = flightInfo.at(4);
    list<Reservation*> reservations;
    return new MyFlight(flightID, model, date, source, destination,
        reservations, assignedCrew, maxFirstClass, maxSecondClass);
}

// Return a pointer to the customer with the given information.
MyCustomer* ObjectFromString::getStringReturnCustomer(vector<string> customerInfo) {
    string customerID = customerInfo.at(0);
    string customerFullName = customerInfo.at(1);
    int customer_priority = stoi(customerInfo.at(2));
    return new MyCustomer(customerID, customerFullName, customer_priority);
}

// Return a pointer to the reservation with the given information.
MyReservation* ObjectFromString::getStringReturnReservation(vector<string>
        reservationInfo, Customer* customer, Flight* flight) {
    string reservationID = reservationInfo.at(0);
    string customer_ID = reservationInfo.at(1);
    string flight_ID = reservationInfo.at(2);
    Classes cls;
    if (reservationInfo.at(3) == "FIRST_CLASS") {
        cls = FIRST_CLASS;
    } else {
        cls = SECOND_CLASS;
    }
    int maxBaggage = stoi(reservationInfo.at(4));
    return new MyReservation(reservationID, customer_ID, customer,
        flight_ID, flight, cls, maxBaggage);
}