#pragma once
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Exception.h"
#include "Addresses.h"
#include "functions.h"

using json = nlohmann::json;
using namespace std;

class Person {
public:
    string name;
    string phoneNumber;
    PersonType type;
    int id;

    Person() {};
    ~Person() {};

    virtual void checkInfo() = 0;

    virtual json ToJsonObject() = 0;
};

class PhysicalPerson : public Person {
public:
    PersonType type = PersonType::phisical;

    PhysicalPerson() {};
    ~PhysicalPerson() {};

    void checkInfo() override {
        cout 
            << "Name: " << left << setw(15) << this->name << "\t" 
            << "Phone numbers: " << right << setw(10) << this->phoneNumber << endl;

    }

    json ToJsonObject() override {
        json obj;

        obj["type"] = type;
        obj["name"] = name;
        obj["phoneNumber"] = phoneNumber;
        obj["id"] = id;

        return obj;
    }
};

class LegalPerson : public PhysicalPerson {
public:
    string nameOfCompany;
    PersonType type = PersonType::legal;

    LegalPerson() {};
    ~LegalPerson() {};

    void checkInfo() override {
        cout
            << "Name: " << left << setw(15) << this->name << "\t"
            << "Phone numbers: " << setw(10) << this->phoneNumber << "\t\t" 
            << "Company: " << this->nameOfCompany << endl;
    }

    json ToJsonObject() override {
        json obj;

        obj["type"] = type;
        obj["name"] = name;
        obj["phoneNumber"] = phoneNumber;
        obj["nameOfCompany"] = nameOfCompany;
        obj["id"] = id;

        return obj;
    }
};

class AllPersons {
public:
    vector<Person*> persons;
    
    void writeRecord(Person* p) {
        p->checkInfo();
    }

    void writeRecords() {
        cout << "All " << persons.size() << " records:" << "\n\n";

        for (int i = 0; i < persons.size(); i++) {
            cout << i + 1 << ". ";
            writeRecord(persons[i]);
        }
        cout << endl;

        cin.get();
    }

    void addPerson() {
        bool isJ = false;
        char yesOrNo;

        cout << "Added new Legal person?(y/n): ";
        cin >> yesOrNo;
        (yesOrNo == 'y' || yesOrNo == 'Y') ? isJ = true : isJ = false;

        cout << "\n\n\t\t[ Added new record ]\n\n";

        if (isJ) {
            LegalPerson* p = new LegalPerson();

            cout << "Write name of person: ";
            rewind(stdin);
            getline(cin, p->name);

            cout << "Write name of his company: ";
            rewind(stdin);
            getline(cin, p->nameOfCompany);

            do {
                cout << "Write phone number: ";
                rewind(stdin);
                getline(cin, p->phoneNumber);

            } while (!numberValidation(p->phoneNumber));
            
            p->id = (persons.size() + 1);

            persons.push_back(p);
        }
        else {
            PhysicalPerson* p = new PhysicalPerson();

            cout << "Write name of person: ";
            rewind(stdin);
            getline(cin, p->name);

            do {
                cout << "Write phone number: ";
                rewind(stdin);
                getline(cin, p->phoneNumber);

            } while (!numberValidation(p->phoneNumber));

            p->id = (persons.size() + 1);

            persons.push_back(p);
        }

        cout << "New record number "
            << persons.size() << " are added!" << endl;
        cin.get();

        this->saveToFile();

    }

    bool loadPersonsFromFile() {
        try {
            ifstream f(PersonsFNAME);

            if (!f.is_open() || f.bad()) {
                throw new ExceptionClass(OpenFileError);
            }

            json j = json::array();
            j = json::parse(f);

            persons.clear();

            for (int i = 0; i < j.size(); i++) {
                int type = j[i]["type"].get<int>();

                if (type == PersonType::legal) {
                    LegalPerson* l = new LegalPerson();

                    l->type = legal;
                    l->name = j[i]["name"].get<string>();
                    l->phoneNumber = j[i]["phoneNumber"].get<string>();
                    l->nameOfCompany = j[i]["nameOfCompany"].get<string>();
                    l->id = j[i]["id"].get<int>();

                    persons.push_back(l);

                }
                else if (type == PersonType::phisical) {
                    PhysicalPerson* p = new PhysicalPerson();

                    p->type = phisical;
                    p->name = j[i]["name"].get<string>();
                    p->phoneNumber = j[i]["phoneNumber"].get<string>();
                    p->id = j[i]["id"].get<int>();

                    persons.push_back(p);
                }
            }

            return true;
        }
        catch (ExceptionClass* exc) {
            cout << endl << exc->exception_message << endl;

            return false;
        }
    }

    bool saveToFile() {
        try {
            ofstream f(PersonsFNAME);

            if (f.bad() || !f.is_open()) {
                throw new ExceptionClass(OpenFileError);

                f.close();
                return false;
            }

            json j = json::array();

            for (auto l : persons)
                j.push_back(l->ToJsonObject());

            f << j;
            f.close();

            return true;
        }
        catch (ExceptionClass* exc) {
            cout << endl << exc->exception_message << endl;

            return false;
        }
    }

    void checkAddressOfPerson(AllBooks* addrs) {
        string name;

        cout << "Write name of person. After that you can see his address" << endl;

        cin >> name;
        cin.ignore();
        cout << endl;

        int id;

        for (int m = 0; m < persons.size(); m++) {
            if (persons[m]->name == name) {
                id = persons[m]->id;
                break;
            }
        }

        for (int m = 0; m < addrs->records.size(); m++) {
            if (addrs->records[m]->idOfPerson == id) {
                addrs->records[m]->checkAddress();
                break;
            }
        }
    }


    friend class AllFriends;
};

class Friend {
public:
    int idOfPerson;
    int idOfHisFriend;

    Friend() {}
    ~Friend() {}

    json ToJsonObject() {
        json obj;

        obj["idOfPerson"] = idOfPerson;
        obj["idOfHisFriend"] = idOfHisFriend;

        return obj;
    }
};

class AllFriends {
public:
    vector<Friend*> friends;

    bool loadFriendsFromFile() {
        try {
            ifstream f(FriendsFNAME);

            if (!f.is_open() || f.bad()) {
                throw new ExceptionClass(OpenFileError);
            }

            json j = json::array();
            j = json::parse(f);

            friends.clear();

            for (int i = 0; i < j.size(); i++) {
                Friend* l = new Friend();

                l->idOfPerson = j[i]["idOfPerson"].get<int>();
                l->idOfHisFriend = j[i]["idOfHisFriend"].get<int>();

                friends.push_back(l);
            }

            return true;
        }
        catch (ExceptionClass* exc) {
            cout << endl << exc->exception_message << endl;

            return false;
        }
    }

    void checkFriendsOfPerson(AllPersons* list) {
        string name;

        cout << "\n\n\t[ Friends Menu ]\n\n";

        cout << "Write name of person. After that you can see his friends" << endl;

        cin >> name;
        cin.ignore();
        cout << endl;

        int id;
        int friendId = -1;

        for (int m = 0; m < list->persons.size(); m++) {
            if (list->persons[m]->name == name) {
                id = list->persons[m]->id;
                break;
            }
        }

        for (int i = 0; i < friends.size(); i++) {
            if (id == friends[i]->idOfPerson) {
                friendId = friends[i]->idOfHisFriend;

                for (int j = 0; j < list->persons.size(); j++) {
                    if (list->persons[j]->id == friendId) {
                        list->persons[j]->checkInfo();
                    }
                }
                break;
            }
        }
        if (friendId == -1) {
            cout << endl << name << " doesn't have any friend..." << endl;
        }
    }
};