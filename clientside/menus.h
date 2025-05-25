
#pragma once
#include "detail.h"
#include <iostream>
#include <string>


using namespace std;

class guide {

  

public:
 
  

    static string showSubMenu() {
        int subChoice;
        while (true) {
            cout << "\n--------------------------------------------------\n";
            cout << "Press 1 to add an Entry.\n";
            cout << "Press 2 to view all data.\n";
            cout << "Press 3 to find specific Entry.\n";
            cout << "Press 4 to update.\n";
            cout << "Press 5 to delete.\n";
            cout << "Press 6 to go back\n";
            cout << "Choose: ";
            cin >> subChoice;

            if (subChoice == 6) break;

            switch (subChoice) {
            case 1:
                return guide::addEntry();
                break;
            case 2:
               
                return guide::viewAll();
                break;
            case 3:
                return guide::findEntry();
                break;
            case 4:
                return guide::updateEntry();
               
                break;
            case 5:
                return guide::deleteEntry();
              
                break;
            default:
                cout << "invalid option\n";
            }
        }
    }

    static string addEntry() {
        int id, age;
        string name, experience, language;
        float rating;

        cout << "Enter cnic:\n";
        cin >> id;
        cout << "Enter age:\n";
        cin >> age;
        cin.ignore();
        cout << "Enter Name:\n";
        getline(cin, name);
        cout << "Enter Experience:\n";
        getline(cin, experience);
        cout << "Enter Language:\n";
        getline(cin, language);
        cout << "Enter rating:\n";
        cin >> rating;
        cin.ignore();

        return "guide|ADD|" + to_string(id) + "|" + to_string(age) + "|" + name + "|" + experience + "|" + language + "|" + to_string(rating);
    }

    static string updateEntry() {
        int id, age;
        string name, experience, language;
        float rating;

        cout << "Enter cnic of guide to update:\n";
        cin >> id;
        cout << "Enter new age:\n";
        cin >> age;
        cin.ignore();
        cout << "Enter new Name:\n";
        getline(cin, name);
        cout << "Enter new Experience:\n";
        getline(cin, experience);
        cout << "Enter new Language:\n";
        getline(cin, language);
        cout << "Enter new rating:\n";
        cin >> rating;
        cin.ignore();

        return "guide|UPDATE|" + to_string(id) + "|" + to_string(age) + "|" + name + "|" + experience + "|" + language + "|" + to_string(rating);
    }

    static string deleteEntry() {
        int id;
        cout << "Enter cnic of guide to delete:\n";
        cin >> id;
        cin.ignore();

        return "guide|DELETE|" + to_string(id);
    }

    static string findEntry() {
        int id;
        cout << "Enter cnic of guide to find:\n";
        cin >> id;
        cin.ignore();

        return "guide|FIND|" + to_string(id);
    }

    static string viewAll() {
        return "guide|VIEW|";
    }
};



class package {
public:
    static string showSubMenu() {
        int subChoice;
        while (true) {
            cout << "\n--------------------------------------------------\n";
            cout << "Press 1 to add an Entry.\n";
            cout << "Press 2 to view all data.\n";
            cout << "Press 3 to find specific Entry.\n";
            cout << "Press 4 to update.\n";
            cout << "Press 5 to delete.\n";
            cout << "Press 6 to go back\n";
            cout << "Choose: ";
            cin >> subChoice;

            if (subChoice == 6) break;

            switch (subChoice) {
            case 1: return addEntry();
            case 2: return viewAll();
            case 3: return findEntry();
            case 4: return updateEntry();
            case 5: return deleteEntry();
            default:
                cout << "Invalid option, try again.\n";
            }
        }
        return "";
    }

    static string addEntry() {
        long long cnic;
        int age, members;
        string name, pkg_name, date, dest;
        float price = 0;

        cout << "Enter CNIC: ";
        cin >> cnic;
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Number of Members: ";
        cin >> members;

        int option;
        cout << "\nSelect a Package:\n";
        cout << "1. UMRAH PACKAGE (10 days, $3000/person)\n";
        cout << "2. Dubai City Tour (5 days, $2000/person)\n";
        cout << "3. Cairo Historical Tour (5 days, $2800/person)\n";
        cout << "4. Barcelona City Tour (3 days, $1500/person)\n";
        cout << "Enter choice: ";
        cin >> option;

        switch (option) {
        case 1:
            pkg_name = "UMRAH PACKAGE";
            price = members * 3000;
            date = "27-May-2024";
            dest = "Saudia Arabia";
            break;
        case 2:
            pkg_name = "Dubai City Tour";
            price = members * 2000;
            date = "20-April-2024";
            dest = "Dubai";
            break;
        case 3:
            pkg_name = "Cairo Historical Tour";
            price = members * 2800;
            date = "12-August-2024";
            dest = "Cairo";
            break;
        case 4:
            pkg_name = "Barcelona City Tour";
            price = members * 1500;
            date = "08-May-2024";
            dest = "Barcelona";
            break;
        default:
            cout << "Invalid option selected.\n";
            return "";
        }

       
        return "package|ADD|" + to_string(cnic) + "|" + name + "|" + to_string(age) + "|" +
            pkg_name + "|" + to_string(members) + "|" + dest + "|" + to_string(price) + "|" + date;
    }

    static string updateEntry() {
        long long cnic;
        int age, members;
        string name, pkg_name, date, dest;
        float price = 0;

        cout << "Enter CNIC of package to update: ";
        cin >> cnic;
        cout << "Enter new Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter new Name: ";
        getline(cin, name);
        cout << "Enter new Number of Members: ";
        cin >> members;

        int option;
        cout << "\nSelect a new Package:\n";
        cout << "1. UMRAH PACKAGE (10 days, $3000/person)\n";
        cout << "2. Dubai City Tour (5 days, $2000/person)\n";
        cout << "3. Cairo Historical Tour (5 days, $2800/person)\n";
        cout << "4. Barcelona City Tour (3 days, $1500/person)\n";
        cout << "Enter choice: ";
        cin >> option;

        switch (option) {
        case 1:
            pkg_name = "UMRAH PACKAGE";
            price = members * 3000;
            date = "27-May-2024";
            dest = "Saudia Arabia";
            break;
        case 2:
            pkg_name = "Dubai City Tour";
            price = members * 2000;
            date = "20-April-2024";
            dest = "Dubai";
            break;
        case 3:
            pkg_name = "Cairo Historical Tour";
            price = members * 2800;
            date = "12-August-2024";
            dest = "Cairo";
            break;
        case 4:
            pkg_name = "Barcelona City Tour";
            price = members * 1500;
            date = "08-May-2024";
            dest = "Barcelona";
            break;
        default:
            cout << "Invalid option selected.\n";
            return "";
        }
       

        return "package|UPDATE|" + to_string(cnic) + "|" + name + "|" + to_string(age) + "|" +
            pkg_name + "|" + to_string(members) + "|" + dest + "|" + to_string(price) + "|" + date;
    }


    static string deleteEntry() {
        long long id;
        cout << "Enter CNIC of package to delete: ";
        cin >> id;
        return "package|DELETE|" + to_string(id);
    }

    static string findEntry() {
        long long id;
        cout << "Enter CNIC of package to find: ";
        cin >> id;
        return "package|FIND|" + to_string(id);
    }

    static string viewAll() {
        return "package|VIEW|";
    }
};




class business {
public:
    static string showSubMenu() {
        int subChoice;
        while (true) {
            cout << "\n--------------------------------------------------\n";
            cout << "Business Tourist Menu:\n";
            cout << "1. Add Entry\n";
            cout << "2. View All Entries\n";
            cout << "3. Find Specific Entry\n";
            cout << "4. Update Entry\n";
            cout << "5. Delete Entry\n";
            cout << "6. Go Back\n";
            cout << "Choose: ";
            cin >> subChoice;

            if (subChoice == 6) break;

            switch (subChoice) {
            case 1: return addEntry();
            case 2: return viewAll();
            case 3: return findEntry();
            case 4: return updateEntry();
            case 5: return deleteEntry();
            default: cout << "Invalid option.\n";
            }
        }
        return "";
    }

    static string addEntry() {
        int id, age, rooms, people;
        string name, destination, companyName, jobTitle, meetingPurpose, accomDesc;
        float price;
        char transport;

        cout << "Enter CNIC:\n"; cin >> id;
        cout << "Enter Age:\n"; cin >> age;
        cin.ignore();
        cout << "Enter Name:\n"; getline(cin, name);
        cout << "Enter Company Name:\n"; getline(cin, companyName);
        cout << "Enter Job Title:\n"; getline(cin, jobTitle);
        cout << "Enter Purpose of Meeting:\n"; getline(cin, meetingPurpose);
        cout << "Needs Transport? (y/n):\n"; cin >> transport; cin.ignore();
        cout << "Enter No. of Rooms:\n"; cin >> rooms;
        cout << "Enter No. of People:\n"; cin >> people;
        cin.ignore();
        cout << "Enter Accommodation Description:\n"; getline(cin, accomDesc);
        cout << "Enter Destination:\n"; getline(cin, destination);
        cout << "Enter Price:\n"; cin >> price; cin.ignore();

        return "business|ADD|" + companyName + "|" + jobTitle + "|" + meetingPurpose + "|" +
            (transport == 'y' || transport == 'Y' ? "1" : "0") + "|" +
            to_string(rooms) + "|" + to_string(people) + "|" + accomDesc + "|" +
            destination + "|" + to_string(price) + "|" +
            to_string(id) + "|" + to_string(age) + "|" + name;
    }

    static string updateEntry() {
        int id, age, rooms, people;
        string name, destination, companyName, jobTitle, meetingPurpose, accomDesc;
        float price;
        char transport;

        cout << "Enter CNIC of business tourist to update:\n";
        cin >> id;
        cout << "Enter new Age:\n"; cin >> age; cin.ignore();
        cout << "Enter new Name:\n"; getline(cin, name);
        cout << "Enter new Company Name:\n"; getline(cin, companyName);
        cout << "Enter new Job Title:\n"; getline(cin, jobTitle);
        cout << "Enter new Purpose of Meeting:\n"; getline(cin, meetingPurpose);
        cout << "Needs Transport? (y/n):\n"; cin >> transport; cin.ignore();
        cout << "Enter new No. of Rooms:\n"; cin >> rooms;
        cout << "Enter new No. of People:\n"; cin >> people; cin.ignore();
        cout << "Enter new Accommodation Description:\n"; getline(cin, accomDesc);
        cout << "Enter new Destination:\n"; getline(cin, destination);
        cout << "Enter new Price:\n"; cin >> price; cin.ignore();

        return "business|UPDATE|" + companyName + "|" + jobTitle + "|" + meetingPurpose + "|" +
            (transport == 'y' || transport == 'Y' ? "1" : "0") + "|" +
            to_string(rooms) + "|" + to_string(people) + "|" + accomDesc + "|" +
            destination + "|" + to_string(price) + "|" +
            to_string(id) + "|" + to_string(age) + "|" + name;
    }

    static string deleteEntry() {
        int id;
        cout << "Enter CNIC of business tourist to delete:\n";
        cin >> id;
        cin.ignore();
        return "business|DELETE|" + to_string(id);
    }

    static string findEntry() {
        int id;
        cout << "Enter CNIC of business tourist to find:\n";
        cin >> id;
        cin.ignore();
        return "business|FIND|" + to_string(id);
    }

    static string viewAll() {
        return "business|VIEW|";
    }
};

