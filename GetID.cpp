
#include "GetID.h"
#include "ReadFromFile.h"
#include "WriteInFile.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// Assumption: the length of the ID will not be bigger than 20.
#define MAX_ID_LENGTH 20

using namespace std;

string GetID::getNextID(string fileName) {
    WriteInFile writer = WriteInFile();
    fstream file(fileName);
    string currentID;
    string newIDStr;
    long newID;
    // If the file is not open, it means that it is the first ID.
    if (!file.is_open()) {
        newIDStr = "1";
        // Add padding of spaces to prevent overwriting.
        for (int i = 1; i< MAX_ID_LENGTH; i++) {
            newIDStr += " ";
        }
        file.open(fileName, ios::app);
        // Write the ID in the first line.
        file << newIDStr << "\n";
        return "1";
    }
    string line;
    // Get the first line of the file.
    getline(file, line);
    currentID = line;
    // Remove the spaces from the first line.
    currentID.erase(std::remove(currentID.begin(), currentID.end(), ' '), currentID.end());
    // Convert the string of the ID to int and increase its value by 1.
    newID = stoi(currentID) + 1;
    // Convert the new ID to string and add at the end of it padding of spaces.
    newIDStr = to_string(newID);
    for (int i = newIDStr.length(); i< MAX_ID_LENGTH; i++){
        newIDStr+= " ";
    }
    // Write the new ID in the first line of the file.
    writer.writeIDInFile(newIDStr, fileName);
    // Remove the spaces from the string of the new ID.
    newIDStr.erase(std::remove(newIDStr.begin(), newIDStr.end(), ' '), newIDStr.end());
    return newIDStr;
}