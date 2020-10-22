
#ifndef MYCUSTOMER_H
#define MYCUSTOMER_H

#include "interface.h"


// A customer has a full name, a priority rating (a number between 1 and 5), and a list of all orders he has placed.
class MyCustomer : public Customer {
private:
    string id;
    string fullName;
    int customerPriority;
    list<Reservation*> reservations;

public:
    MyCustomer(string uniqueId, string full_name, int priority) {
        id = uniqueId;
        fullName = full_name;
        customerPriority = priority;
    }

    string getID() {
        return id;
    }

    string getFullName() {
        return fullName;
    }

    int getPriority() {
        return customerPriority;
    }

    list<Reservation*> getReservations() {
        return reservations;
    }

    string getCustomerFileFormat();

    // Destructor.
    ~MyCustomer(){

    }

};

#endif // MYCUSTOMER_H