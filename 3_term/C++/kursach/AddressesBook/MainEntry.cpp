
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Constants.h";
#include "Persons.h";
#include "Addresses.h";
#include "Exception.h";

AllBooks AddressesBox;
AllPersons PersonsBox;
AllFriends FriendsBox;

bool thinkMenu() {
    int sel;

    cout << "\n\n\t[ Menu ]\n\n";
    cout 
        << "1. Print records (" << AddressesBox.records.size() << ")" << endl
        << "2. Add new record" << endl
        << "3. Edit record" << endl
        << "4. Delete record" << endl
        << "5. Find record" << endl << endl;

    cout
        << "6. Check persons (" << PersonsBox.persons.size() << ")" << endl
        << "7. Add new person" << endl
        << "8. Check friend of person" << endl
        << "9. Check address of person" << endl << endl;

    cout 
        << "10. Save and exit" << endl << endl;

    cout << "\n\n" << "-> ";
    cin >> sel;
    cin.ignore();
    cout << endl;

    switch (sel) {
        case 1: AddressesBox.writeRecords(); break;
        case 2: AddressesBox.addRecord(); break;
        case 3: AddressesBox.editRecord(); break;
        case 4: AddressesBox.deleteRecord(); break;
        case 5: AddressesBox.findRecord(); break;

        case 6: PersonsBox.writeRecords(); break;
        case 7: PersonsBox.addPerson(); break;
        case 8: FriendsBox.checkFriendsOfPerson(&PersonsBox); break;
        case 9: PersonsBox.checkAddressOfPerson(&AddressesBox); break;

        case 10: return false; break;
        default: break;
    }

    return true;
}

int main() {
    try {
        AddressesBox.loadFromFile();
        PersonsBox.loadPersonsFromFile();
        FriendsBox.loadFriendsFromFile();

        while (thinkMenu()) {};

        if (!AddressesBox.saveToFile() || !PersonsBox.saveToFile())
            throw new ExceptionClass(SaveFileError);
    }
    catch (ExceptionClass* exc) {
        cout << endl << exc->exception_message << endl;

        return 1;
    }

    return 0;
}