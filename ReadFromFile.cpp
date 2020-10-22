
#include "ReadFromFile.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <istream>
#include <vector>

using namespace std;

vector<string> ReadFromFile::splitByDelimiter(string line) {
    size_t current = 0;
    size_t previous = 0;
    vector<string> results;
    current = line.find(DELIMITER);
    while (current != std::string::npos) {
        results.push_back(line.substr(previous, current - previous));
        previous = current + 1;
        current = line.find(DELIMITER, previous);
    }
    results.push_back(line.substr(previous, current - previous));
    return results;
}

vector<vector<string>> ReadFromFile::loadEmployeesFromFile() {
    fstream myFile(EMPLOYEE_FILE);
    string line;
    vector<vector<string>> employees;
    bool firstLine = true;
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            employees.push_back(splitByDelimiter(line));
        }
        myFile.close();
        return employees;
    }
}

vector<vector<string>> ReadFromFile::loadPlanesFromFile() {
    fstream myFile(PLANE_FILE);
    string line;
    vector<vector<string>> planes;
    string currentID;
    bool firstLine = true;
    if (myFile.is_open()) {
        while(getline(myFile, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            planes.push_back(splitByDelimiter(line));
        }
        myFile.close();
        return planes;
    }
}

vector<vector<string>> ReadFromFile::loadFlightsFromFile() {
    fstream myFile(FLIGHT_FILE);
    string line;
    vector<vector<string>> flights;
    bool firstLine = true;
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            flights.push_back(splitByDelimiter(line));
        }
        myFile.close();
        return flights;
    }
}

vector<vector<string>> ReadFromFile::loadCustomersFromFile() {
    fstream myFile(CUSTOMER_FILE);
    string line;
    vector<vector<string>> customers;
    bool firstLine = true;
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            customers.push_back(splitByDelimiter(line));
        }
        myFile.close();
        return customers;
    }
}

vector<vector<string>> ReadFromFile::loadReservationsFromFile() {
    fstream myFile(RESERVATION_FILE);
    string line;
    vector<vector<string>> reservations;
    bool firstLine = true;
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            reservations.push_back(splitByDelimiter(line));
        }
        myFile.close();
        return reservations;
    }
}

vector<vector<string>> ReadFromFile::loadEmployeesToFlights() {
    vector<vector<string>> results;
    string line;
    fstream myFile(EMPLOYEES_TO_FLIGHTS_FILE);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            results.push_back(splitByDelimiter(line));
        }
        myFile.close();
        return results;
    } else {
        return results;
    }
}