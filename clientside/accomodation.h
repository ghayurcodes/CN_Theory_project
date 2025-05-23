#pragma once
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class accomodation{
private:
    int no_ppl;
    int rooms;
    string special_detail;

public:
    // Constructors
    accomodation();
    accomodation(int ,int, string);

    // Getters
    int getNoPeople();
    int getRooms();
    string getDetail();

    // Setters
    void setNoPeople(int);
    void setRooms(int);
    void setDetail(string);
    string tostring();

    
};

accomodation::accomodation() : no_ppl(0), rooms(0), special_detail(""){}

accomodation::accomodation(int ppl,int room,string _detail)
    : no_ppl(ppl), rooms(room), special_detail(_detail) {}

int accomodation::getNoPeople() {
    return no_ppl;
}

int accomodation::getRooms() {
    return rooms;
}

string accomodation::getDetail() {
    return special_detail;
}

void accomodation::setNoPeople(int people) {
    no_ppl = people;
}

void accomodation::setRooms(int roomCount) {
    rooms = roomCount;
}

void accomodation::setDetail(string _detail) {
    special_detail = _detail;
}

string accomodation::tostring(){
    return to_string(no_ppl)+" "+to_string(rooms)+" "+special_detail;
}
