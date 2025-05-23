#pragma once
#include "detail.h"

using namespace std;

class tour {
protected:
    string destination;
    string departure;
    string date;
    float price;
    detail tour_detail;
    long long int cnic;
    int guide_id;
    static int total_tours;
public:
    tour();
    tour(string, string, string, float, int, int, string);
    tour(string, string, string, float,long,bool,bool ,int, int, string);

    void setDestination(string);
    string getDestination();
    void setDeparture(string _departure);
    string getDeparture();
    void setDate(string _date);
    string getDate();
    float getPrice();
    long long int getCnic(){return cnic;}
    void setPrice(float _price);
    static int get_total();
    static void set_total(int);
    detail getDetail();
    
    static int generate_id();
    virtual void menu()=0;
    
  
};
int tour::total_tours=0;

tour::tour() : destination(" "), departure(" "), date(" "), price(0), tour_detail() {}

tour::tour(string _destination, string _departure, string _date, float _price, int _id, int _age, string _name)
    : destination(_destination), departure(_departure), date(_date), price(_price), tour_detail(_id, _age, _name) {}

tour::tour(string _destination, string _departure, string _date, float _price,long _cnic,bool inter,bool food, int _id, int _age, string _name)
    : destination(_destination), departure(_departure), date(_date), price(_price),cnic(_cnic), tour_detail(_id, _age, _name) {}


void tour::setDestination(string _destination) {
    destination = _destination;
}

string tour::getDestination() {
    return destination;
}

void tour::setDeparture(string _departure) {
    departure = _departure;
}

string tour::getDeparture() {
    return departure;
}

void tour::setDate(string _date) {
    date = _date;
}

string tour::getDate() {
    return date;
}

void tour::setPrice(float _price) {
    price = _price;
}

int tour::get_total(){
    return total_tours;
}

void tour::set_total(int x){
    total_tours=x;
}

float tour::getPrice() {
    return price;
}

detail tour::getDetail() {
    return tour_detail;
}

int tour::generate_id(){
    srand(time(0));
    int temp=rand()%(200-100)+100;
    return temp;
}



