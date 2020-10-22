
#include "MyImplementation.h"
#include "GetID.h"
#include <string.h>
#include "ReadFromFile.h"
#include "ObjectFromString.h"
#include <stdexcept>
using namespace std;

// Add a new employee.
Employee* MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    // Create a unique ID for the current employee.
    string uniqueId = idFactory.getNextID(EMPLOYEE_FILE);
    Employee* employee = new MyEmployee(uniqueId, seniority, birth_year, title, employer_id, findEmployee(employer_id));
    newEmployees.push_back((MyEmployee*)employee);
    return employee;
}

// Find the specified employee by his ID number.
Employee* MyImplementation::findEmployee(string ID) {
    // If the data of the existing employees wasn't loaded from the file yet, load it.
    if (!employeesWereLoaded) {
        employeesWereLoaded = true;
        loadEmployeesFromFile();
    }
    // Search the employee among the existing employees.
    for (vector<MyEmployee*>:: iterator it = newEmployees.begin();
         it != newEmployees.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    // Search the employee among the new employees.
    for (vector<MyEmployee*>:: iterator it = loadedEmployees.begin();
         it != loadedEmployees.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    // If the employee doesn't exist, return NULL.
    return NULL;
}

// Return a pointer to the employee with the specified ID number.
Employee* MyImplementation::getEmployee(string id) {
    Employee* employee = findEmployee(id);
    return employee;
}

// Find a specific plane by its ID number.
Plane* MyImplementation::findPlane(string ID) {
    // If the data of the existing planes wasn't loaded from the file yet, load it.
    if (!planesWereLoaded) {
        planesWereLoaded = true;
        loadPlanesFromFile();
    }
    // Search the plane among the existing planes.
    for (vector<MyPlane*>:: iterator it = loadedPlanes.begin();
         it != loadedPlanes.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    // Search the plane among the new planes.
    for (vector<MyPlane*>:: iterator it = newPlanes.begin();
         it != newPlanes.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    // If the plane doesn't exist, return NULL.
    return NULL;
}

// Add a new plane.
Plane* MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    // Create a unique ID for the current plane.
    string uniqueId = idFactory.getNextID(PLANE_FILE);
    MyPlane* plane = new MyPlane(uniqueId, model_number, crew_needed, max_passangers);
    // Add the plane model to the map of the plane models counters.
    addModelToModelsCounters(model_number);
    newPlanes.push_back(plane);
    return plane;
}

// Return a pointer to the plane with the specified ID number.
Plane* MyImplementation::getPlane(string id) {
    Plane* plane = findPlane(id);
    return plane;
}

// Find the crew that is needed for the specified plane model.
map<Jobs, int> MyImplementation::findCrewNeeded(int model_number) {
    // Search the plane among the existing planes.
    for (vector<MyPlane*>::iterator it = loadedPlanes.begin();
         it != loadedPlanes.end(); ++it) {
        if ((*it)->getModelNumber() == model_number) {
            return (*it)->getCrewNeeded();
        }
    }
    // Search the plane among the new planes.
    for (vector<MyPlane*>::iterator it = newPlanes.begin();
         it != newPlanes.end(); ++it) {
        if ((*it)->getModelNumber() == model_number) {
            return (*it)->getCrewNeeded();
        }
    }
}

// Helper method - find the required employees for the specified job.
list<Employee*> MyImplementation::requiredEmployees(Jobs job, int numOfEmployeesNeeded, Date flightDate) {
    list<Employee*> neededEmployees;
    // Search the employee among the existing employees.
    for (vector<MyEmployee*>::iterator it = loadedEmployees.begin();
         it != loadedEmployees.end(); it++) {
        // If the employee works in the fit job and is available - assign him.
        if (job == (*it)->getTitle() && (*it)->isAvailable(flightDate)) {
            numOfEmployeesNeeded--;
            neededEmployees.push_back((*it));
            // If enough employees were found - return them.
            if (numOfEmployeesNeeded == 0) {
                return neededEmployees;
            }
        }
    }
    // Search the employee among the new employees.
    for (vector<MyEmployee*>::iterator it = newEmployees.begin();
         it != newEmployees.end(); it++) {
        if (job == (*it)->getTitle() && (*it)->isAvailable(flightDate)) {
            numOfEmployeesNeeded--;
            neededEmployees.push_back((*it));
        }
        if (numOfEmployeesNeeded == 0) {
            return neededEmployees;
        }
    }
    // If there are not enough employees, throw an exception.
    throw std::invalid_argument("There is no available crew.");
}

// Find an assigned crew to a flight.
list<Employee*> MyImplementation::findAssignedCrew(int model_number, Date flightDate) {
    // Load the required data from the files.
    if (!employeesWereLoaded) {
        employeesWereLoaded = true;
        loadEmployeesFromFile();
    }
    if (!planesWereLoaded) {
        planesWereLoaded = true;
        loadPlanesFromFile();
    }
    if (!flightsWereLoaded) {
        flightsWereLoaded = true;
        loadFlightsFromFile();
    }
    // Find the crew that is needed for this plane model.
    map<Jobs, int> crewNeeded = findCrewNeeded(model_number);
    list<Employee*> currentEmployees;
    list<Employee*> allEmployees;
    // Find available employees for each job and add them to assigned crew.
    for (map<Jobs, int>::iterator it = crewNeeded.begin();
         it != crewNeeded.end(); ++it) {
        // If employees are not required for this job, continue.
        if ((*it).second == 0) {
            continue;
        }
        currentEmployees = requiredEmployees((*it).first, (*it).second, flightDate);
        allEmployees.merge(currentEmployees);
    }
    return allEmployees;
}

// Add a flight to the employees who work on it.
void MyImplementation::addFlightToEmployees(list<Employee*> assignedCrew, string date, string uniqueId) {
    WriteInFile writer = WriteInFile();
    // Iterate over the employees of the assigned crew.
    for (list<Employee*>:: iterator it = assignedCrew.begin();
         it != assignedCrew.end(); ++it) {
        // Add the flight to the relevant existing employees.
        for (vector<MyEmployee*>:: iterator iter = loadedEmployees.begin();
             iter != loadedEmployees.end(); ++iter) {
            if ((*it)->getID() == (*iter)->getID()) {
                (*iter)->notAvailableAt(Date(date), uniqueId);
                writer.writeInEmployeesToFlightsFile((*it)->getID(), date, uniqueId);
            }
        }
        // Add the flight to the relevant new employees.
        for (vector<MyEmployee*>:: iterator iter = newEmployees.begin();
             iter != newEmployees.end(); ++iter) {
            if ((*it)->getID() == (*iter)->getID()) {
                (*iter)->notAvailableAt(Date(date), uniqueId);
            }
        }
    }
}

// Find the maximal number of places in the specified model plane in the specified class. 
int MyImplementation:: findNumOfPlacesInClass(Classes cls, int model_number) {
   for (vector<MyPlane*>:: iterator it = loadedPlanes.begin();
       it != loadedPlanes.end(); ++it) {
       if ((*it)->getModelNumber() == model_number) {
          if (cls == FIRST_CLASS) {
              return ((*it)->getMaxFirstClass());
          }
          else {
              return ((*it)->getMaxEconomyClass());
          }
       }
   }
    for (vector<MyPlane*>:: iterator it = newPlanes.begin();
         it != newPlanes.end(); ++it) {
        if ((*it)->getModelNumber() == model_number) {
            if (cls == FIRST_CLASS) {
                return ((*it)->getMaxFirstClass());
            }
            else {
                return ((*it)->getMaxEconomyClass());
            }
        }
    }
}

// Add a new flight
Flight* MyImplementation::addFlight(int model_number, Date date, string source, string destination) {
    // Load the data of the flights from a file if it wasn't loaded yet.
    if (!flightsWereLoaded) {
        flightsWereLoaded = true;
        loadFlightsFromFile();
    }
    // Check whether there are enough planes from the specified model for the new flight.
    if (!isModelHasEnoughPlanes(date.getDate(), model_number)) {
        throw std::invalid_argument("There are not enough planes from the specified plane model.");
    }
    // At first the reservations list of the flight is empty.
    list<Reservation*> reservations;
    // Find a crew for the flight.
    list<Employee*> assignedCrew = findAssignedCrew(model_number, date);
    // Create a unique ID for the flight.
    string uniqueId = idFactory.getNextID(FLIGHT_FILE);
    // Find the maximal number of places in the specified model plane in the specified class. 
    int maxFirstClass = findNumOfPlacesInClass(FIRST_CLASS, model_number);
    int maxSecondClass = findNumOfPlacesInClass(SECOND_CLASS, model_number);
    MyFlight* flight = new MyFlight(uniqueId, model_number, date, source,
        destination, reservations, assignedCrew, maxFirstClass, maxSecondClass);
    // Add the flight to the employees who work on it.
    addFlightToEmployees(assignedCrew, date.getDate(), uniqueId);
    newFlights.push_back(flight);
    return flight;
}

// Find a specific flight by its ID number.
Flight* MyImplementation::findFlight(string ID) {
    for (vector<MyFlight*>:: iterator it = newFlights.begin();
         it != newFlights.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    for (vector<MyFlight*>:: iterator it = loadedFlights.begin();
         it != loadedFlights.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    // If the plane doesn't exist, return NULL.
    return NULL;
}

// Return a pointer to the flight with the specified ID number.
Flight* MyImplementation::getFlight(string id) {
    if (!employeesWereLoaded) {
        employeesWereLoaded = true;
        loadEmployeesFromFile();
    }
    if (!flightsWereLoaded) {
        flightsWereLoaded = true;
        loadFlightsFromFile();
    }
    Flight* flight = findFlight(id);
    return flight;
}

// Add a new employee.
Customer* MyImplementation::addCustomer(string full_name, int priority) {
    // If the priority is not valid, throw an exception.
    if (priority < 0 || priority > 5) {
        throw std::invalid_argument("There specified priority is not valid.");
    }
    // Create a unique ID for the current customer.
    string uniqueId = idFactory.getNextID(CUSTOMER_FILE);
    MyCustomer* customer = new MyCustomer(uniqueId, full_name, priority);
    newCustomers.push_back(customer);
    return customer;
}

// Find the customer with the specified ID number.
Customer* MyImplementation::findCustomer(string ID) {
    for (vector<MyCustomer*>:: iterator it = newCustomers.begin();
         it != newCustomers.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    for (vector<MyCustomer*>:: iterator it = loadedCustomers.begin();
         it != loadedCustomers.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    // If the customer doesn't exist, return NULL.
    return NULL;
}

// Return a pointer to the customer with the specified ID number.
Customer* MyImplementation::getCustomer(string id) {
    if (!customersWereLoaded) {
        customersWereLoaded = true;
        loadCustomersFromFile();
    }
    Customer* customer = findCustomer(id);
    return customer;
}

// Add a reservation to its flight.
void MyImplementation::addReservationToFlight(MyReservation* reservation, string flightId) {
    for (vector<MyFlight*>:: iterator it = newFlights.begin(); it != newFlights.end(); ++it) {
        if ((*it)->getID() == flightId) {
            (*it)->addReservation(reservation);
            break;
        }
    }
    for (vector<MyFlight*>:: iterator it = loadedFlights.begin();
         it != loadedFlights.end(); ++it) {
        if ((*it)->getID() == flightId) {
            (*it)->addReservation(reservation);
            break;
        }
    }
}

// Check whether there are enough places in the specified class of the specified flight.
bool MyImplementation::areThereEnoughPlacesInClass(string flightId, Classes cls) {
    for (vector<MyFlight*>::iterator it = loadedFlights.begin();
        it != loadedFlights.end(); ++it) {
        if ((*it)->getID() == flightId) {
            if ((*it)->getNumOfPlacesInClass(cls) > 0) {
                return true;
            } else {
                return false;
            }
        }
    }
    for (vector<MyFlight*>::iterator it = newFlights.begin();
         it != newFlights.end(); ++it) {
        if ((*it)->getID() == flightId){
            if ((*it)->getNumOfPlacesInClass(cls) > 0) {
                return true;
            } else {
                return false;
            }
        }
    }
}

// Add a new reservation.
Reservation* MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    // Create a unique ID for the current reservation.
    string uniqueId = idFactory.getNextID(RESERVATION_FILE);
    MyFlight* flight = (MyFlight*)getFlight(flightId);
    // If the flight doesn't exist, throw an exception.
    if (flight == NULL) {
        throw std::invalid_argument("There is no such flight.");
    }
    // If the customer doesn't exist, throw an exception.
    MyCustomer* customer = (MyCustomer*)getCustomer(customerId);
    if (customer == NULL) {
        throw std::invalid_argument("There is no such customer.");
    }
    // If there are not enough places in the specified class of the specified flight, throw an exception.
    if (!areThereEnoughPlacesInClass(flightId, cls)) {
        throw std::invalid_argument("There are not enough places in this class.");
    }
    MyReservation* reservation = new MyReservation(uniqueId, customerId,
        customer, flightId, flight, cls, max_baggage);
    // Add the reservation to its flight.
    addReservationToFlight(reservation, flightId);
    newReservations.push_back(reservation);
    return reservation;
}

// Find the reservation with the specified ID number.
Reservation* MyImplementation::findReservation(string ID) {
    for (vector<MyReservation*>:: iterator it = newReservations.begin();
         it != newReservations.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    for (vector<MyReservation*>:: iterator it = loadedReservations.begin();
         it != loadedReservations.end(); ++it) {
        if((*it)->getID() == ID) {
            return *it;
        }
    }
    // If the reservation doesn't exist, return NULL.
    return NULL;
}

// Return a pointer to the reservation with the specified ID number.
Reservation* MyImplementation::getReservation(string id) {
    if (!reservationsWereLoaded) {
        reservationsWereLoaded = true;
        loadReservationsFromFile();
    }
    Reservation* reservation = findReservation(id);
    return reservation;
}

// Load the data of the existing employees from a file.
void MyImplementation::loadEmployeesFromFile() {
    ReadFromFile reader = ReadFromFile();
    vector<vector<string>> results = reader.loadEmployeesFromFile();
    // ObjectFromString is an object that gets information as strings and creates objects.
    ObjectFromString ofs = ObjectFromString();
    Employee* emp = NULL;
    string currentEmployerID;
    for (vector<vector<string>>:: iterator it = results.begin();
         it != results.end(); ++it) {
        // The ID of the employer.
        currentEmployerID = (*it).at(4);
        if (currentEmployerID != "") {
            emp = getEmployee(currentEmployerID);
        }
        loadedEmployees.push_back(ofs.getStringReturnEmployee((*it), emp));
    }
}

// Add the specific plane model to the map of the plane models counters.
void MyImplementation::addModelToModelsCounters(int modelNumber) {
    map<int,int> ::iterator iter;
    iter = planeModelsCounters.find(modelNumber);
    // If the key exists in the map - increase the counter by 1.
    if (iter != planeModelsCounters.end()) {
        planeModelsCounters[modelNumber] = planeModelsCounters[modelNumber] + 1;
    // Else - the key doesn't exist in the map, map it to the value 1.
    } else {
        planeModelsCounters[modelNumber] = 1;
    }
};

// Load the data of the existing planes from a file.
void MyImplementation::loadPlanesFromFile() {
    ReadFromFile reader = ReadFromFile();
    vector<vector<string>> results = reader.loadPlanesFromFile();
    // ObjectFromString is an object that gets information as strings and creates objects.
    ObjectFromString ofs =  ObjectFromString();
    for (vector<vector<string>>:: iterator it = results.begin();
        it != results.end(); ++it) {
        MyPlane* plane = ofs.getStringReturnPlane((*it));
        int modelNumber = plane->getModelNumber();
        addModelToModelsCounters(modelNumber);
        loadedPlanes.push_back(plane);
    }
}

// Add the existing employees that were loaded from a file to the existing flights that were loaded from a file.
void MyImplementation::addExistingEmployeesToExistingFlights() {
    for (vector<MyFlight*>:: iterator it = loadedFlights.begin();
         it != loadedFlights.end(); ++it) {
        list<Employee*> assignedCrew;
        string flightID = (*it)->getID();
        for (vector<MyEmployee*>:: iterator iter = loadedEmployees.begin();
             iter != loadedEmployees.end(); ++iter) {
            if ((*iter)->worksInFlight(flightID)) {
                assignedCrew.push_back((Employee*)(*iter));
            }
        }
        (*it)->setAssignedCrew(assignedCrew);
    }
}

// Load the data of the existing flights from a file.
void MyImplementation::loadFlightsFromFile() {
    // Load the required data from files.
    if (!planesWereLoaded) {
        planesWereLoaded = true;
        loadPlanesFromFile();
    }
    if (!employeesWereLoaded) {
        employeesWereLoaded = true;
        loadEmployeesFromFile();
    }
    if (!reservationsWereLoaded) {
        reservationsWereLoaded = true;
        loadReservationsFromFile();
    }
    if (!employeesToFlightsWereLoaded) {
        employeesToFlightsWereLoaded = true;
        loadEmployeesToFlightsFromFile();
    }
    ReadFromFile reader = ReadFromFile();
    vector<vector<string>> results = reader.loadFlightsFromFile();
    // ObjectFromString is an object that gets information as strings and creates objects.
    ObjectFromString ofs =  ObjectFromString();
    for (vector<vector<string>>:: iterator it = results.begin();
         it != results.end(); ++it) {
        int model_number = stoi((*it).at(1));
        Date date((*it).at(2));
        // Add a pair of a flight date and a plane model to loadedDatesToModels.
        loadedDatesToModels.push_back(make_pair(date.getDate(), model_number));
        list<Employee*> assignedCrew;
        int maxFirstClass = findNumOfPlacesInClass(FIRST_CLASS, model_number);
        int maxSecondClass = findNumOfPlacesInClass(SECOND_CLASS, model_number);
        MyFlight* flight =
        ofs.getStringReturnFlight((*it), assignedCrew, maxFirstClass, maxSecondClass);
        loadedFlights.push_back(flight);
    }
    addExistingEmployeesToExistingFlights();
}

// Load the data of the existing customers from a file.
void MyImplementation::loadCustomersFromFile() {
    ReadFromFile reader = ReadFromFile();
    vector<vector<string>> results = reader.loadCustomersFromFile();
    // ObjectFromString is an object that gets information as strings and creates objects.
    ObjectFromString ofs =  ObjectFromString();
    for (vector<vector<string>>:: iterator it = results.begin();
         it != results.end(); ++it) {
        loadedCustomers.push_back(ofs.getStringReturnCustomer((*it)));
    }
}

// Load the data of the existing reservations from a file.
void MyImplementation::loadReservationsFromFile() {
    ReadFromFile reader = ReadFromFile();
    vector<vector<string>> results = reader.loadReservationsFromFile();
    // ObjectFromString is an object that gets information as strings and creates objects.
    ObjectFromString ofs = ObjectFromString();
    Customer* customer;
    Flight* flight;
    for (vector<vector<string>>:: iterator it = results.begin();
        it != results.end(); ++it) {
        string customerID = (*it).at(0);
        customer = getCustomer(customerID);
        string flightID = (*it).at(2);
        flight = getFlight(flightID);
        Reservation* reservation =
            ofs.getStringReturnReservation((*it), customer, flight);
        for (vector<MyFlight*>:: iterator iter = loadedFlights.begin();
            iter != loadedFlights.end(); ++iter) {
            if ((*iter) == flight) {
                // Add the reservation to the corresponding flight.
                ((MyFlight*)flight)->addReservation(reservation);
            }
        }
        loadedReservations.push_back((MyReservation*)reservation);
    }
}

// Load from a file the data that fits employees to their flights.
void MyImplementation::loadEmployeesToFlightsFromFile() {
    ReadFromFile reader = ReadFromFile();
    vector<vector<string>> employeesToFlights = reader.loadEmployeesToFlights();
    for (vector<vector<string>>:: iterator it = employeesToFlights.begin();
         it != employeesToFlights.end(); ++it) {
        // Add the flight to the corresponding employees that were loaded from a file.
        for (vector<MyEmployee*>:: iterator iter = loadedEmployees.begin();
             iter != loadedEmployees.end(); ++iter) {
            if ((*iter)->getID() == (*it).at(0)) {
                (*iter)->notAvailableAt((*it).at(1), (*it).at(2));
            }
        }
    }
}

// Check whether there are enough planes from the specified model for the new flight.
bool MyImplementation::isModelHasEnoughPlanes(string date, int model_number) {
    // Load the required data from the files.
    if (!planesWereLoaded) {
        planesWereLoaded = true;
        loadPlanesFromFile();
    }
    if (!employeesToFlightsWereLoaded) {
        employeesToFlightsWereLoaded = true;
        loadEmployeesToFlightsFromFile();
    }
    // The quantity of the planes from this model.
    int modelsQuantity = planeModelsCounters.find(model_number)->second;
    // If the model's quantity is 0, there are not enough planes from this model - return false.
    if (modelsQuantity == 0) {
        return false;
    }
    /*
     * Subtract the number of flights requiring this plane model at the specified date from the quantity
     * of this plane model in order to know whether there are enough planes or not.
     */
    for (vector<pair<string, int>>::iterator it = loadedDatesToModels.begin();
         it != loadedDatesToModels.end(); ++it) {
        if ((*it).first == date && (*it).second == model_number) {
            modelsQuantity--;
            if (modelsQuantity == 0) {
                return false;
            }
        }
    }
    for (vector<pair<string, int>>::iterator it = newDatesToModels.begin();
         it != newDatesToModels.end(); ++it) {
        if ((*it).first == date && (*it).second == model_number) {
            modelsQuantity--;
            if (modelsQuantity == 0) {
                return false;
            }
        }
    }
    // Return true since there are enough plane models.
    return true;
}

/* Helper functions for copying the new data created during the running to the files when exiting the program. */

void MyImplementation::copyNewEmployeesToFile(WriteInFile writer) {
    for (vector<MyEmployee*>:: iterator it = newEmployees.begin();
         it != newEmployees.end(); ++it) {
        writer.writeInEmployeeFile(*it);
    }
}

void MyImplementation::copyNewPlanesToFile(WriteInFile writer) {
    for (vector<MyPlane*>:: iterator it = newPlanes.begin();
         it != newPlanes.end(); ++it) {
        writer.writeInPlaneFile(*it);
    }
}

void MyImplementation::copyNewFlightsToFile(WriteInFile writer) {
    for (vector<MyFlight*>:: iterator it = newFlights.begin();
         it != newFlights.end(); ++it) {
        writer.writeInFlightFile(*it);
    }
}

void MyImplementation::copyNewCustomersToFile(WriteInFile writer) {
    for (vector<MyCustomer*>:: iterator it = newCustomers.begin();
         it != newCustomers.end(); ++it) {
        writer.writeInCustomerFile(*it);
    }
}

void MyImplementation::copyNewReservationsToFile(WriteInFile writer) {
    for (vector<MyReservation*>:: iterator it = newReservations.begin();
         it != newReservations.end(); ++it) {
        writer.writeInReservationFile(*it);
    }
}

// This method should be called at the end of the running.
void MyImplementation::exit() {
    // Copy the new data created during the running to the files when exiting the program.
    WriteInFile writer = WriteInFile();
    copyNewEmployeesToFile(writer);
    copyNewPlanesToFile(writer);
    copyNewFlightsToFile(writer);
    copyNewCustomersToFile(writer);
    copyNewReservationsToFile(writer);
}


// Free all the memory allocated in MyImplementation. 
MyImplementation:: ~MyImplementation() {
    for (vector<MyEmployee*>:: iterator it = newEmployees.begin();
         it != newEmployees.end(); ++it) {
        delete (*it);
    }

    for (vector<MyEmployee*>:: iterator it = loadedEmployees.begin();
         it != loadedEmployees.end(); ++it) {
        delete (*it);
    }


    for (vector<MyPlane*>:: iterator it = newPlanes.begin();
         it != newPlanes.end(); ++it) {
        delete (*it);
    }

    for (vector<MyPlane*>:: iterator it = loadedPlanes.begin();
         it != loadedPlanes.end(); ++it) {
        delete (*it);
    }

    for (vector<MyFlight*>:: iterator it = newFlights.begin();
         it != newFlights.end(); ++it) {
        delete (*it);
    }

    for (vector<MyFlight*>:: iterator it = loadedFlights.begin();
         it != loadedFlights.end(); ++it) {
        delete (*it);
    }

    for (vector<MyCustomer*>:: iterator it = newCustomers.begin();
         it != newCustomers.end(); ++it) {
        delete (*it);
    }

    for (vector<MyCustomer*>:: iterator it = loadedCustomers.begin();
         it != loadedCustomers.end(); ++it) {
        delete (*it);
    }

    for (vector<MyReservation*>:: iterator it =  newReservations.begin();
         it != newReservations.end(); ++it) {
        delete (*it);
    }

    for (vector<MyReservation*>:: iterator it =  loadedReservations.begin();
         it != loadedReservations.end(); ++it) {
        delete (*it);
    }
}