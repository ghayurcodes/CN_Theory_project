#pragma once
#include <string>
using namespace std;

class accommodation {
private:
    int numRooms;
    int numPeople;
    string description;

public:
    accommodation() : numRooms(0), numPeople(0), description("") {}
    accommodation(int rooms, int people, const string& desc)
        : numRooms(rooms), numPeople(people), description(desc) {}

    int getNumRooms() const { return numRooms; }
    int getNumPeople() const { return numPeople; }
    string getDescription() const { return description; }

    void setNumRooms(int rooms) { numRooms = rooms; }
    void setNumPeople(int people) { numPeople = people; }
    void setDescription(const string& desc) { description = desc; }
};
