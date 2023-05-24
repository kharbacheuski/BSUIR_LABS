#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <functional>

using namespace std;

struct recordType {
    string name; // Ф.И.О. студента
    string address; // адрес проживания
    int semester; // семестр
};