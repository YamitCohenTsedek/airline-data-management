
#ifndef GETID_H
#define GETID_H

#include <iostream>
#include <string.h>

using namespace std;

// Class GetID is in charge of creating a unique ID for each object of a specific class.
class GetID {
public:
    string getNextID(string fileName);
};

#endif // GETID_H