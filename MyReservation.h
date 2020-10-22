
#ifndef MYRESERVATION_H
#define MYRESERVATION_H


#include "interface.h"

// A reservation has a customer, a flight ID, a class in which the customer is interested, and the max baggage of the customer.
class MyReservation : public Reservation {
private:
    string id;
    string customer_ID;
    Customer* reservationCustomer;
    string flight_ID;
    Flight* reservationFlight;
    Classes currentClass;
    int maxBaggage;

public:
    MyReservation(string uniqueId, string customerId,  Customer* customer,
            string flightId, Flight* flight, Classes cls, int max_baggage) {
        id = uniqueId;
        customer_ID = customerId;
        Customer* reservationCustomer = customer;
        flight_ID = flightId;
        reservationFlight = flight;
        currentClass = cls;
        maxBaggage = max_baggage;
    }

    string getID() {
        return id;
    }

    Customer* getCustomer() {
        return reservationCustomer;
    }

    Flight* getFlight() {
        return reservationFlight;
    }

    Classes getClass() {
        return currentClass;
    }

    int getMaxBaggage() {
        return maxBaggage;
    }

    string getReservationFileFormat();

    ~MyReservation(){
    }
};

#endif // MYRESERVATION_H