#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>
#include<vector>

using namespace std;

class detail {
private:
    long long int id;
    int age;
    string name;

public:
    detail();
    detail(int, int, string);
    void setId(int);
    long getId();
    int getAge();
    void setName(string);
    string getName();
    string tostring();
    void setAge(int);

};
detail::detail() {
    id = 0;
    age = 0;
    name = " ";
};

detail::detail(int _id, int _age, string _name) : id(_id), age(_age), name(_name) {}
void detail::setId(int _id) {
    id = _id;
}

long detail::getId() {
    return id;
}

int detail::getAge() {
    return age;
}
void detail::setName(string _name) {
    name = _name;
}
string detail::getName() {
    return name;
}
string detail::tostring() {
    return to_string(id) + " " + to_string(age) + " " + name;
}

void detail::setAge(int _age) {
    age = _age;
}

