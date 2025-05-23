#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "detail.h"

using namespace std;

class tourist {
protected:
    int flight_id;
    string destination;
    string departure;
    string date;
    float price;
    detail tourist_detail; // Contains CNIC, age, name

public:
    // Constructors
    tourist() : flight_id(0), destination(""), departure(""), date(""), price(0.0f), tourist_detail() {}

    tourist(int _flight_id, const string& _destination, const string& _departure, const string& _date,
        float _price, long long _cnic, int _age, const string& _name)
        : flight_id(_flight_id), destination(_destination), departure(_departure),
        date(_date), price(_price), tourist_detail(_cnic, _age, _name) {
        
    }


    
   
    string serialize() {
        return to_string(flight_id) + "|" +
            to_string(tourist_detail.getId()) + "|" +
            tourist_detail.getName() + "|" +
            to_string(tourist_detail.getAge()) + "|" +
            destination + "|" +
            departure + "|" +
            date + "|" +
            to_string(price)+"|";
    }

    


    static int generate_id() {
        srand(time(0));
        return rand() % (200 - 100) + 100;
    }

   
};
