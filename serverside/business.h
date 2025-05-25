#pragma once
#include "tourist.h"
#include "accomodation.h" 
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

class business : public tourist {
private:
    string companyName, jobTitle, meetingPurpose;
    bool needsTransport;
    accommodation accom;  

public:
    business()
        : companyName(""), jobTitle(""), meetingPurpose(""), needsTransport(false),
        accom() 
    {}

    business(const string& comp, const string& job, const string& purpose,
        bool transport, int rooms, int people, const string& accomDesc,
        const string& dest, float price, int id, int age, const string& name)
        : companyName(comp), jobTitle(job), meetingPurpose(purpose), needsTransport(transport),
        accom(rooms, people, accomDesc)  
    {
        this->destination = dest;
        this->price = price;
        this->tourist_detail.setId(id);
        this->tourist_detail.setAge(age);
        this->tourist_detail.setName(name);
    }

    

    string serialize() {
        stringstream ss;
        ss << companyName << "|" << jobTitle << "|" << meetingPurpose << "|"
            << (needsTransport ? "1" : "0") << "|"
            << accom.getNumRooms() << "|" << accom.getNumPeople() << "|"
            << accom.getDescription() << "|" << destination << "|"
            << price << "|" << tourist_detail.getId() << "|"
            << tourist_detail.getAge() << "|" << tourist_detail.getName();
        return ss.str();
    }

    static vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        string temp;
        for (char ch : str) {
            if (ch == delimiter) {
                tokens.push_back(temp);
                temp.clear();
            }
            else {
                temp += ch;
            }
        }
        tokens.push_back(temp); // Push last segment
        return tokens;
    }

    static business deserialize(const string& data) {
        vector<string> tokens = split(data, '|');
        

        if (tokens.size() != 12) {  
            throw runtime_error("Invalid data length for business tourist. Got " + to_string(tokens.size()));
        }

       /*for (int i : {4, 5, 8, 9, 10}) {
            if (tokens[i].empty()) {
                throw runtime_error("Empty numeric token at index " + to_string(i));
            }
        }
       */ 

        int rooms = stoi(tokens[4]);
        int people = stoi(tokens[5]);
        float price = stof(tokens[8]);
        int id = stoi(tokens[9]);
        int age = stoi(tokens[10]);
        string name = tokens[11];

        return business(
            tokens[0],          // companyName
            tokens[1],          // jobTitle
            tokens[2],          // meetingPurpose
            tokens[3] == "1",   // needsTransport
            rooms,
            people,
            tokens[6],          // accomDesc
            tokens[7],          // destination
            price,
            id,
            age,
            name
        );
    }

    static vector<business> loadBusinesses(const string& filename = "business.txt") {
        ifstream fin(filename);
        vector<business> vec;
        string line;
        while (getline(fin, line)) {
            try {
                vec.push_back(deserialize(line));
            }
            catch (const exception& ex) {
                cerr << "Deserialize error: " << ex.what() << endl;
            }
        }
        return vec;
    }

    static void saveBusinesses(vector<business>& vec, const string& filename = "business.txt") {
        ofstream fout(filename);
        for (auto& b : vec)
            fout << b.serialize() << endl;
    }

    static string processRequest(const string& request) {
        vector<business> businesses = loadBusinesses();
        size_t delim = request.find("|");
        if (delim == string::npos) return "Invalid format.";
        string cmd = request.substr(0, delim);
        string rest = request.substr(delim + 1);

        if (cmd == "ADD") {
            try {
                business b = deserialize(rest);
                for (auto& item : businesses) {
                    if (item.tourist_detail.getId() == b.tourist_detail.getId())
                        return "Business with this CNIC already exists.";
                }
                businesses.push_back(b);
                saveBusinesses(businesses);
                return "Business added successfully.";
            }
            catch (const exception& ex) {
                return string("Error adding business: ") + ex.what();
            }
        }
        else if (cmd == "VIEW") {
            if (businesses.empty()) return "No entries found.";
            stringstream ss;
            for (auto& b : businesses)
                ss << b.serialize() << "\n";
            return ss.str();
        }
        else if (cmd == "DELETE") {
            try {
                int id = stoi(rest);
                auto it = remove_if(businesses.begin(), businesses.end(),
                    [id](business& b) { return b.tourist_detail.getId() == id; });
                if (it == businesses.end()) return "ID not found.";
                businesses.erase(it, businesses.end());
                saveBusinesses(businesses);
                return "Deleted successfully.";
            }
            catch (const exception& ex) {
                return string("Error deleting: ") + ex.what();
            }
        }
        else if (cmd == "FIND") {
            try {
                int id = stoi(rest);
                for (auto& b : businesses) {
                    if (b.tourist_detail.getId() == id)
                        return b.serialize();
                }
                return "Business tourist not found.";
            }
            catch (const exception& ex) {
                return string("Error finding business: ") + ex.what();
            }
        }
        else if (cmd == "UPDATE") {
            try {
                business updated = deserialize(rest);
                bool found = false;
                for (auto& b : businesses) {
                    if (b.tourist_detail.getId() == updated.tourist_detail.getId()) {
                        b = updated;
                        found = true;
                        break;
                    }
                }
                if (!found) return "Business not found for update.";
                saveBusinesses(businesses);
                return "Business updated successfully.";
            }
            catch (const exception& ex) {
                return string("Failed to update business: ") + ex.what();
            }
        }

        return "Unknown command.";
    }
};
