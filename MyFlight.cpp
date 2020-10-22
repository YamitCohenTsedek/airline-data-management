
#include "MyFlight.h"
#include <string.h>

using namespace std;


 /*
  * The format of FlightFile:
  * string flightID;int modelNumber;Date flightDate;string flightSource;string flightDestination;
  */
string MyFlight::getFlightFileFormat () {

    string flightFileFormat;
    string flightID = id;
    string model = to_string(modelNumber);
    string flightDate = date.getDate();
    string flightSource = source;
    string flightDestination = destination;

    list<Reservation*> reservations;
    list<Employee*> assignedCrew;

    flightFileFormat = flightID + ";" + model + ";" + flightDate + ";"
        + flightSource + ";" + flightDestination + ";\n";
    return flightFileFormat;
}