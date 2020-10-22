
#ifndef MYIMPLEMENTATION_H
#define MYIMPLEMENTATION_H

#include "interface.h"
#include "GetID.h"
#include <iostream>
#include <vector>
#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyCustomer.h"
#include "MyReservation.h"
#include "WriteInFile.h"
#define DELIMITER ";"

using namespace std;

class MyImplementation: public Airline_Data_Managment {

private:

    // An object to create a unique ID for each object of a specific class.
    GetID idFactory = GetID();

    // Vectors for saving the new objects that are created during running the program.
    vector<MyEmployee*> newEmployees;
    vector<MyPlane*> newPlanes;
    vector<MyFlight*> newFlights;
    vector<MyCustomer*> newCustomers;
    vector<MyReservation*> newReservations;


    /* The existing objects that were created in the previous runs of the program and were loaded from the files. */
     
    vector<MyEmployee*> loadedEmployees;
    vector<MyPlane*> loadedPlanes;
    vector<MyFlight*> loadedFlights;
    vector<MyCustomer*> loadedCustomers;
    vector<MyReservation*> loadedReservations;

    
     /* Boolean members which indicate whether the objects were loaded from the files or not. */
     
    bool employeesWereLoaded = false;
    bool planesWereLoaded = false;
    bool flightsWereLoaded = false;
    bool customersWereLoaded = false;
    bool reservationsWereLoaded = false;
    bool employeesToFlightsWereLoaded = false;

    /*
     * The following methods load the information about the objects that were created at the previous runs of
     * the program from the files and save them in the corresponding vector.
     */

    void loadEmployeesFromFile();
    void loadPlanesFromFile();
    void loadFlightsFromFile();
    void loadCustomersFromFile();
    void loadReservationsFromFile();
    void loadEmployeesToFlightsFromFile();

    // A map that maps between a plane model to its quantity.
    map<int,int> planeModelsCounters;

    /*
     * Vectors of pairs - a date string and a plane model, in order to know when a specific plane model is needed.
     * loadedDatesToModels is intended for information loaded from the files,
     * newDatesToModels is intended for the new information created while running the program.
     */

    vector<pair<string, int>> loadedDatesToModels;
    vector<pair<string, int>> newDatesToModels;

    
     // Add the specific plane model to the map of the plane models counters.
    void addModelToModelsCounters (int modelNumber);

    // Check whether there are enough planes from the specified model for the new flight.
    bool isModelHasEnoughPlanes(string date, int model_number);

    // Find an assigned crew to a flight.
    list<Employee*> findAssignedCrew(int model_number, Date flightDate);

    // Find what is the needed crew to the plane.
    map<Jobs, int> findCrewNeeded(int model_number);

    // Helper method - find the required employees for a specific job.
    list<Employee*> requiredEmployees(Jobs job, int numOfEmployeesNeeded, Date flightDate);

    // Add a flight to the employees who work on it.
    void addFlightToEmployees(list<Employee*> assignedCrew, string date, string uniqueId);

    // Add a reservation to its flight.
    void addReservationToFlight(MyReservation* reservation, string flightId);

    
     // Find the maximal number of places the specified class of the specified model plane. 
    int findNumOfPlacesInClass(Classes cls, int model_number);

    
    // Check whether there are enough places in the specified class of the specified flight.
    bool areThereEnoughPlacesInClass(string flightId, Classes cls);

    
    // Add the existing employees that were loaded from a file to the existing flights that were loaded from a file.
    void addExistingEmployeesToExistingFlights();

    /* Methods for finding the required object by its ID number. */

    Employee* findEmployee(string ID);
    Plane* findPlane(string ID);
    Flight* findFlight(string ID);
    Customer* findCustomer(string ID);
    Reservation* findReservation(string ID);

    /* Methods for copying the new information added during the current running to the files. */

    void copyNewEmployeesToFile(WriteInFile writer);
    void copyNewCustomersToFile(WriteInFile writer);
    void copyNewPlanesToFile(WriteInFile writer);
    void copyNewFlightsToFile(WriteInFile writer);
    void copyNewReservationsToFile(WriteInFile writer);

public:
    Employee* addEmployee(int seniority, int birth_year, string employer_id, Jobs title);
    Employee* getEmployee(string id);
    Plane* addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers);
    Plane* getPlane(string id);
    Flight* addFlight(int model_number, Date date, string source, string destination);
    Flight* getFlight(string id);
    Customer* addCustomer(string full_name, int priority);
    Customer* getCustomer(string id);
    Reservation* addResevation(string customerId, string flightId, Classes cls, int max_baggage);
    Reservation* getReservation(string id);

    // Call exit function at the end of the running.
    void exit();

    // Destructor.
    ~MyImplementation();

};

#endif // MYIMPLEMENTATION_H