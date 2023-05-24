#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
void arrayReversAndPrint(T* array, int count)
{
    int len = count;
    T temp;
    for (int i = 0; i < len / 2; i++)
    {
        temp = array[i];
        array[i] = array[len - i - 1];
        array[len - i - 1] = temp;
    }  
    cout << "Answer: ";
    for (int i = 0; i < len; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}


int main() {
    int cel[] = { 1, 0, 0, 2 };
    double d[] = { 1.13, 7.5, 9.89, 12.70 };
    char ch[] = { 'o', 'l', 'l', 'e', 'h'};
    string str[] = { "Alabama", "Home", "Sweet"};

    int userAnswer;
    int cycleExitFlag = 1;
    while (cycleExitFlag) {
        cout << endl << "Enter type of array: (int - 1, double - 2, char - 3, string - 4, exit - 0)" << endl;
        cin >> userAnswer;

        switch (userAnswer) {
            case 1: arrayReversAndPrint(cel, sizeof(cel) / sizeof(*cel)); break;
            case 2: arrayReversAndPrint(d, sizeof(d) / sizeof(*d));; break;
            case 3: arrayReversAndPrint(ch, sizeof(ch) / sizeof(*ch)); break;
            case 4: arrayReversAndPrint(str, sizeof(str) / sizeof(*str)); break;
            case 0: cycleExitFlag = 0; break;

            default: cout << "Enter valid number from list!" << endl; break;
        }
    }

    return 0;
}


