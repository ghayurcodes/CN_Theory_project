#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "detail.h"


using namespace std;

class guide {
private:
    detail guide_detail;  
    string experience;
    string language;
    float rating;

public:
    guide() : guide_detail(), experience(""), language(""), rating(0.0f) {}

    guide(int _id, int _age, const string& _name, const string& _experience, const string& _language, float _rating)
        : guide_detail(_id, _age, _name), experience(_experience), language(_language), rating(_rating) {}

    int getID()  { return guide_detail.getId(); }

    string serialize()  {
        return to_string(guide_detail.getId()) + "|" +
            to_string(guide_detail.getAge()) + "|" +
            guide_detail.getName() + "|" +
            experience + "|" +
            language + "|" +
            to_string(rating);
    }


    static guide deserialize(const string& data) {
        stringstream ss(data);
        string token;
        int id, age;
        string name, experience, language;
        float rating;

        getline(ss, token, '|'); id = stoi(token);
        getline(ss, token, '|'); age = stoi(token);
        getline(ss, name, '|');
        getline(ss, experience, '|');
        getline(ss, language, '|');
        getline(ss, token, '|'); rating = stof(token);

        return guide(id, age, name, experience, language, rating);
    }

    static vector<guide> loadGuides() {
        ifstream fin("guides.txt");
        vector<guide> guides;
        string line;
        while (getline(fin, line)) {
            guides.push_back(deserialize(line));
        }
        return guides;
    }

    static void saveGuides(vector<guide> guides) {
        ofstream fout("guides.txt");
        for ( auto g : guides) {
            fout << g.serialize() << endl;
        }
    }

    static string processRequest(const string& request) {
        vector<guide> guides = loadGuides();
        size_t pos = request.find("|");
        if (pos == string::npos) return "Invalid request format.";
        string cmd = request.substr(0, pos);
        string data = request.substr(pos + 1);

        if (cmd == "ADD") {
            guides.push_back(deserialize(data));
            saveGuides(guides);
            return "Guide added successfully.";
        }
        else if (cmd == "VIEW") {
            if (guides.empty()) return "No guides found.";
            string res;
            for ( auto g : guides) {
                res += g.serialize() + "\n";
            }
            return res;
        }
        else if (cmd == "DELETE") {
            int id = stoi(data);
            auto it = remove_if(guides.begin(), guides.end(), [id]( guide& g) {
                return g.getID() == id;
                });
            if (it == guides.end()) return "Guide not found.";
            guides.erase(it, guides.end());
            saveGuides(guides);
            return "Guide deleted.";
        }
        else if (cmd == "UPDATE") {
            guide updated = deserialize(data);
            bool found = false;
            for (auto& g : guides) {
                if (g.getID() == updated.getID()) {
                    g = updated;
                    found = true;
                    break;
                }
            }
            if (!found) return "Guide not found.";
            saveGuides(guides);
            return "Guide updated.";
        }
        else if (cmd == "FIND") {
            int id = stoi(data);
            for (auto g : guides) {
                if (g.getID() == id) return g.serialize();
            }
            return "Guide not found.";
        }

        return "Unknown command.";
    }
};
