
#ifndef MYPLANE_H
#define MYPLANE_H


#include "interface.h"
#include "GetID.h"
#include "MyEmployee.h"

/*
 * A plane has a model number, a list of the number of crew members of any job type required to fly the plane,
 * and the maximal number of passengers in each class.
 */
class MyPlane : public Plane {
private:
    string id;
    int modelNumber;
    map<Jobs, int> crewNeeded;
    int maxFirstClass;
    int maxEconomyClass;

public:
    string getID() {
        return id;
    }

    MyPlane(string uniqueId, int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
        id = uniqueId;
        modelNumber = model_number;
        crewNeeded = crew_needed;
        pair<Jobs, int> x;
        map<Classes, int> ::iterator it = max_passangers.begin();
        it = max_passangers.find(FIRST_CLASS);
        maxFirstClass = ((*it).second);
        it = max_passangers.find(SECOND_CLASS);
        maxEconomyClass = (*it).second;
    }

    int getModelNumber() {
        return modelNumber;
    }

    map<Jobs, int> getCrewNeeded() {
        return crewNeeded;
    }

    int getMaxFirstClass() {
        return maxFirstClass;
    }

    int getMaxEconomyClass() {
        return maxEconomyClass;
    }

    string getPlaneFileFormat();

    ~MyPlane() {}
};


#endif // MYPLANE_H