#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>

#define fileName "file.txt"

using namespace std;

struct recordType {
    string name; // Ф.И.О. студента
    string address; // адрес проживания
    int semester; // семестр
};

enum LockAction {
    lock,
    unlock
};

ofstream& operator<< (std::ofstream& out, struct recordType& data){
    out << data.name;
    out << '\n';
    out << data.address;
    out << '\n';
    out << to_string(data.semester);
    out << '\n';

    return out;
}

void writeIntoFile(vector<recordType> allRecords) {
    struct recordType record;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, record.name);
  
    cout << "\n\nEnter address: ";
    getline(cin, record.address);

    cout << "\n\nEnter semestr: ";
    cin >> record.semester;

    ofstream fout(fileName, std::ios::app);

    fout << record;

    allRecords.push_back(record);

    fout.close();
}


struct recordType getRecordByNumber(int number) {
    ifstream fin(fileName, ios::in);

    string sem;
    struct recordType rec;

    string buf;
    if(number != 1) 
        for(int i = 0; i < 3*(number - 1); i++) 
            getline(fin, buf);


    getline(fin, rec.name);
    if(!rec.name.size()) return rec;

    getline(fin, rec.address);
    getline(fin, sem);
    rec.semester = atoi(sem.c_str());

    return rec;
}

void getAllRecords(vector<recordType> *allRecords) {
    int nmb = 1;

    while(true) {
        recordType record = getRecordByNumber(nmb++);

        if(record.name.size()) allRecords->push_back(record);
        else break;
    }
}

void saveChangesIntoFile(vector<recordType> all) {
    ofstream fout(fileName);

    for(auto rec: all) {
        fout << rec;
    }

    cout << "\n\nAll good\n\n";

    fout.close();
}

void changeRecord(vector<recordType> all, int number) {
    cout << "Enter new name: ";
    cin >> all[number-1].name;
}

void printRecord(struct recordType record, int number) {
    cout << number << ": " << endl;
    cout << "\tname: " << record.name << endl;
    cout << "\taddress: " << record.address << endl;
    cout << "\tsemestr: " << record.semester << endl;
}

void lockAction(struct flock* locker, int fd, LockAction actionType) {

    if(actionType == lock) {
        locker->l_type = F_WRLCK;

        /* Установка блокировки */
        fcntl(fd, F_SETLKW, locker);
        cout << "---File Locked---" << endl;
    }
    if(actionType == unlock) {
        locker->l_type = F_UNLCK;

        fcntl(fd, F_SETLKW, locker);
        cout << "---File unlocked---" << endl;
    }
}

void lockAction(struct flock* locker, int fd, const std::function<void()>& f) {
    lockAction(locker, fd, lock);
    f();
    lockAction(locker, fd, unlock);
}

int menuChoice(bool isInitial) {
    int cd;

    if(isInitial) {
        cout << "\n\n" << "Select action: "<< endl;
        cout << "1 - Record operations"<< endl;
        cout << "2 - Add record"<< endl;
        cout << "0 - Exit" << endl;

    }
    else {
        cout << "\n\n" << "Select action: "<< endl;
        cout << "1 - Print record"<< endl;
        cout << "2 - Change record name"<< endl;
        cout << "3 - Show all records" << endl;
        cout << "4 - Save changes" << endl;
        cout << "0 - Exit" << endl;
    }

    cin >> cd;
    cout << "\n\n";

    return cd;
}

int main(int argc, char* argv[]) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    char* filename = argv[1];
    int fd = open(filename, O_RDWR);

    struct recordType record;
    int recordNumber;

    vector<recordType> allRecords;

    getAllRecords(&allRecords);

    while(true) {
        int code = menuChoice(true);

        if(code == 1) {
            cout << "\n\tRecord operations\n\n";

            cout << "Enter record number: ";
            cin >> recordNumber;

            int code = menuChoice(false);

            switch (code) {
                case 1: {
                    lockAction(&lock, fd, [&] {
                        record = getRecordByNumber(recordNumber);
                    });
                    printRecord(record, recordNumber);
                }; break;

                case 2: {
                    lockAction(&lock, fd, [&] {
                        changeRecord(allRecords, recordNumber);
                    });
                }; break;

                case 3: {
                    for(int i = 0; i <= allRecords.size() - 1; i++) {
                        printRecord(allRecords[i], i+1);
                    }
                }; break;
                case 4: {
                    lockAction(&lock, fd, [&] {
                        saveChangesIntoFile(allRecords);
                    });
                }; break;

                case 0: break;

                default:
                    break;
            }
        }
        else if(code == 2) {
            cout << "\n\tAdding record\n\n";
            lockAction(&lock, fd, [&] {
                writeIntoFile(allRecords);
            });
        }
        else break;

    }

    close(fd);

    return 0;
}