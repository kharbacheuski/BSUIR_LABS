#pragma once

#include "Constants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Exception.h"

using json = nlohmann::json;
using namespace std;

class Address {
public:
    string street;
    string homePhoneNumber;
    string note;
    int idOfPerson;
    int id;

    Address() {};
    ~Address() {};

    json ToJsonObject() {
        json obj;

        obj["street"] = street;
        obj["homePhoneNumber"] = homePhoneNumber;
        obj["note"] = note;
        obj["idOfPerson"] = idOfPerson;
        obj["id"] = id;

        return obj;
    }

    void checkAddress() {
        cout
            << left << setw(45) << street << "\t"
            << setw(10) << homePhoneNumber << "\t\t"
            << setw(30) << note << endl;
    }
};

class AllBooks {
public:
    vector<Address*> records;

    bool loadFromFile() {
        try {
            ifstream f(AddressesFNAME);

            if (!f.is_open() || f.bad()) {
                throw new ExceptionClass(OpenFileError);
            }

            json j = json::array();
            j = json::parse(f);

            records.clear();

            for (int i = 0; i < j.size(); i++) {
                Address* t = new Address();

                t->street = j[i]["street"].get<string>();
                t->homePhoneNumber = j[i]["homePhoneNumber"].get<string>();
                t->note = j[i]["note"].get<string>();
                t->idOfPerson = j[i]["idOfPerson"].get<int>();
                t->id = j[i]["id"].get<int>();
                

                records.push_back(t);
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
            ofstream f(AddressesFNAME);

            if (f.bad() || !f.is_open()) {
                throw new ExceptionClass(OpenFileError);

                f.close();

                return false;
            }

            json j = json::array();

            for (auto l : records)
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

    void writeRecord(Address* item) {
        item->checkAddress();
    }

    void notFound() {
        cout << endl << "Record not found..." << endl;
    }

    int findRecord()
    {
        int sel;

        cout << "Find record by:" << endl
            << "1. Number" << endl
            << "2. Name" << endl
            << "\n\n > ";

        cin >> sel;
        cout << endl;

        if (sel == 2)
        {
            string val;
            cout << "Write value for search: ";
            cin.ignore();
            getline(cin, val);

            for (int i = 0; i < records.size(); i++)
                if (records[i]->street.find(val) != records[i]->street.npos ||
                    records[i]->note.find(val) != records[i]->note.npos ||
                    records[i]->homePhoneNumber == val)
                    writeRecord(records[i]);

            cout << endl;
        }

        int number = 0;
        bool fail = false;

        cout << "Enter number of record: ";
        cin >> number;
        cin.ignore();

        if (number < 1 || number > records.size()) {
            notFound();
            return -1;
        }
        else writeRecord(records[number - 1]);

        return 1;
    }

    void writeRecords() {
        cout << "All " << records.size() << " records:" << endl;

        for (int i = 0; i < records.size(); i++) {
            cout << i + 1 << ". ";
            writeRecord(records[i]);
        }
            
        cin.get();
    }

    void addRecord()
    {
        Address r;
        cout << "\n\n\t\t[ Added new record ]\n\n";

        cout << "Write home phone number: ";
        getline(cin, r.homePhoneNumber);
        cout << "Write address: ";
        getline(cin, r.street);
        cout << "Write note to a record: ";
        getline(cin, r.note);
        cout << endl;

        cout << "Write id of owner: ";
        getline(cin, r.note);
        cin >> r.idOfPerson;
        cout << endl;

        r.id = (records.size() + 1);

        records.push_back(&r);
        cout << "New record number "
            << records.size() << " are added!" << endl;
        cin.get();
    }

    void editRecord()
    {
        cout << "\n\n\t\t[ Editing record ]\n\n";

        int id = findRecord();
        if (id == -1) {
            addRecord();
            return;
        }
        string temp = "";
        int ids;

        cout << "Write 'enter' if you wont edit record!\n\n";

        cout << "Write home phone number: ";
        getline(cin, temp);
        if (temp.size() > 0)
            records[id]->homePhoneNumber = temp;
        cout << "Add new name of record: ";
        getline(cin, temp);
        if (temp.size() > 0)
            records[id]->street = temp;
        cout << "Added new note to record: " << endl;
        getline(cin, temp);
        if (temp.size() > 0)
            records[id]->note = temp;

        cout << "Record edited!" << endl;
        cin.get();
    }

    void deleteRecord()
    {
        cout << "\n\n\t\t[ Editing record ]\n\n";

        char ans = 'n';
        int id = findRecord();
        if (id == -1)
        {
            cout << "Delete error!" << endl;
            return;
        }

        cout << endl;
        writeRecord(records[id]);
        cout << endl;
        cout << "Sure? (y/n)? ";
        cin.get(ans);

        if (ans == 'y' || ans == 'Y')
        {
            records.erase(records.begin() + id);
            cout << "Record number "
                << id + 1 << " are deleted!" << endl;
            cin.ignore();
            cin.get();
        }
    }
};