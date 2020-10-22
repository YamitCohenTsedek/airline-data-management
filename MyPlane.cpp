
#include "MyPlane.h"
#include <string.h>

using namespace std;

/*
 * The format of PlaneFile:
 * string planeID;int model_number;int quantityOfManagersNeeded;
 * int quantityOfNavigatorsNeeded;int quantityOfFlyAttendantNeeded;
 * int quantityOfPilotsNeeded;int quantityOfOthersNeeded;
 * int maxFirstClass;int maxEconomyClass;
 */
string MyPlane::getPlaneFileFormat () {
    string planeFileFormat;
    string planeID = id;
    string model_number = to_string(modelNumber);
    string crew_needed;
    string delimiter = ";";
    for (map<Jobs, int>::iterator it = crewNeeded.begin();
         it!=crewNeeded.end(); ++it) {
        crew_needed+= to_string(it->second)+ delimiter;
    }
    string maxFirst = to_string(maxFirstClass);
    string maxEconomy = to_string(maxEconomyClass);
    planeFileFormat = planeID + ";" + model_number + ";" + crew_needed + maxFirst + ";" + maxEconomy + ";\n";
    return planeFileFormat;
}