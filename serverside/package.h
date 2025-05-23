#pragma once
#include "tourist.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class package : public tourist {
private:
    string pkg_name;
    int members;

public:
    package() : tourist(), pkg_name(""), members(0) {}

    package(int flight_id, const string& destination, const string& date,
        float price, long long cnic, int age, const string& name,
        const string& pkg_name, int members)
        : tourist(flight_id, destination, "Not Set", date, price, cnic, age, name),
        pkg_name(pkg_name), members(members) {}

    string serialize()  {
        return to_string(tourist_detail.getId()) + "|" +       // CNIC
            tourist_detail.getName() + "|" +                // Name
            to_string(tourist_detail.getAge()) + "|" +      // Age
            pkg_name + "|" +                                // Package name
            to_string(members) + "|" +                      // Members
            destination + "|" +                             // Destination
            to_string(price) + "|" +                        // Price
            date;                                           // Date
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
        tokens.push_back(temp); // push the last part
        return tokens;
    }

    static package deserialize(const string& data) {
        vector<string> tokens = split(data, '|');

        if (tokens.size() != 8) {
            throw runtime_error("Invalid data format for package: expected 8 tokens, got " + to_string(tokens.size()));
        }

        long long cnic = stoll(tokens[0]);
        string name = tokens[1];
        int age = stoi(tokens[2]);
        string pkg_name = tokens[3];
        int members = stoi(tokens[4]);
        string destination = tokens[5];
        float price = stof(tokens[6]);
        string date = tokens[7];

        return package(
            generate_id(),   // flight_id (randomly generated)
            destination,
            date,
            price,
            cnic,
            age,
            name,
            pkg_name,
            members
        );
    }





    static vector<package> loadPackages() {
        ifstream fin("package.txt");
        vector<package> packages;
        string line;
        while (getline(fin, line)) {
            try {
                packages.push_back(deserialize(line));
            }
            catch (...) {
                continue;
            }
        }
        return packages;
    }

    static void savePackages( vector<package>& packages) {
        ofstream fout("package.txt");
        for ( auto& p : packages) {
            fout << p.serialize() << "\n";
        }
    }

    static string processRequest(const string& rawreq) {
       
        size_t pos = rawreq.find("|");
        if (pos == string::npos) return "Invalid format";


        string cmd = rawreq.substr(0,pos);

        string payload = rawreq.substr(pos + 1);
        
   

        string command = cmd;
       

        if (command == "ADD") {
            return handleAdd(payload);
        }
        else if (command == "VIEW") {
            return handleView();
        }
        else if (command == "DELETE") {
            return handleDelete(payload);
        }
        else if (command == "FIND") {
            return handleFind(payload);
        }
        else if (command == "UPDATE") {
            return handleUpdate(payload);
        }
        else {
            return "Unknown command: " + command;
        }
    }

    static string handleAdd(const string& payload) {
        try {
            package p = deserialize(payload);
            auto packages = loadPackages();
            packages.push_back(p);
            savePackages(packages);
            return "Package added successfully.";
        }
        catch (const exception& e) {
            return string("ADD failed: ") + e.what();
        }
    }

    static string handleView() {
        auto packages = loadPackages();
        if (packages.empty()) return "No packages found.";

        stringstream ss;
        for ( auto& p : packages) {
            ss << p.serialize() << "\n";
        }
        return ss.str();
    }

    static string handleDelete(const string& payload) {
        auto packages = loadPackages();
        long long cnic = stoll(payload);
        auto it = remove_if(packages.begin(), packages.end(),
            [cnic]( package& p) {
                return p.tourist_detail.getId() == cnic;
            });
        if (it == packages.end()) return "No package found with this CNIC.";

        packages.erase(it, packages.end());
        savePackages(packages);
        return "Package deleted.";
    }

    static string handleFind( string& payload) {
        auto packages = loadPackages();
        long long cnic = stoll(payload);
        for (auto& p : packages) {
            if (p.tourist_detail.getId() == cnic)
                return p.serialize();
        }
        return "Package not found.";
    }

    static string handleUpdate(const string& data) {
        package updated = deserialize(data);  // data: "cnic|name|age|pkg_name|members|dest|price|date"
        bool found = false;

        auto packages = loadPackages();
        for (auto& p : packages) {
            if (p.tourist_detail.getId() == updated.tourist_detail.getId()) {
                p = updated;
                found = true;
                break;
            }
        }

        if (!found) return "Package not found.";
        savePackages(packages);
        return "Package updated.";
    }


};
