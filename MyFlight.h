
#ifndef MYFLIGHT_H
#define MYFLIGHT_H

#include "interface.h"
#include "MyEmployee.h"


 // A flight has a plane model, a date, a source, a destination, a list of reservations, and a list of the assigned crew. 
class MyFlight: public Flight {
private:
    string id;
    int modelNumber;
    Date date;
    string source;
    string destination;
    list<Reservation*> reservations;
    list<Employee*> assignedCrew;
    int placesInFirstClass;
    int placesInSecondClass;

public:
    MyFlight(string uniqueId, int model_number, Date flightDate,
        string flightSource, string flightDestination, 
        list<Reservation*> reservations, list<Employee*> crew,
        int maxFirstClass, int maxSecondClass): date(flightDate) {
        id = uniqueId;
        modelNumber = model_number;
        date = Date(flightDate);
        source = flightSource;
        destination = flightDestination;
        assignedCrew = crew;
        placesInFirstClass = maxFirstClass;
        placesInSecondClass = maxSecondClass;
    }

    string getID() {
        return id;
    }


    int getModelNumber() {
        return modelNumber;
    }

    void addReservation (Reservation* reservation) {
        reservations.push_back(reservation);
        decreaseNumberOfPlacesInClass(reservation->getClass());
    }

    list<Reservation*> getReservations() {
        return reservations;
    }

    list<Employee*> getAssignedCrew() {
        return assignedCrew;
    }

    Date getDate() {
        return date;
    }

    string getSource() {
        return source;
    }

    string getDestination() {
        return destination;
    }

    void setAssignedCrew(list <Employee*> crew) {
        assignedCrew = crew;
    }

    // Decrease the number of the free places in the specified class.
    void decreaseNumberOfPlacesInClass(Classes cls) {
        if (cls == FIRST_CLASS) {
            placesInFirstClass--;
        } else {
            placesInSecondClass--;
        }
    };

    // Return the number of free places in the specified class.
    int getNumOfPlacesInClass(Classes cls) {
        if (cls == FIRST_CLASS) {
            return placesInFirstClass;
        } else {
            return placesInSecondClass;
        }
    }

    string getFlightFileFormat();

    // Destructor.
    ~MyFlight(){

    }
};

#endif // MYFLIGHT_H