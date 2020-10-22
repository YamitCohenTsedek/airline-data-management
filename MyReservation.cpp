
#include "MyReservation.h"

/*
 * The format of ReservationFile:
 * string reservationID;string customerID;
 * string flightID;Classes class;int max_baggage;
 */
string MyReservation::getReservationFileFormat () {
    string reservationFileFormat;
    string reservationID = id;
    string customerID = customer_ID;
    string flightID = flight_ID;
    string current_class;
    if (currentClass == FIRST_CLASS) {
        current_class = "FIRST_CLASS";
    } else {
        current_class = "SECOND_CLASS";
    }
    string max_baggage = to_string(maxBaggage);
    reservationFileFormat = reservationID + ";" + customerID + ";" + flightID + ";" + current_class + ";"
        + max_baggage + ";\n";
    return reservationFileFormat;
}