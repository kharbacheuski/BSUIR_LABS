// перегрузка операторов: «Дробные числа».
#include <iostream>
using namespace std;

class SquareNumber {
    private:
        double nmb;

    public:
        SquareNumber(double num) {
            nmb = pow(num, 2);
        }  
    friend ostream& operator << (std::ostream& out, SquareNumber num);
};

class DoubleNumber {
    private:
        double number;

    public:
        DoubleNumber(double num) {
            number = num;
        }

        DoubleNumber& operator = (DoubleNumber nextNum) { // overdrive "=" operator (num is object of DoubleNumber class)
            number = nextNum.number;
            return *this;
        }

        void operator ++ (int) {    // overdrive increment operator
            number++; 
        } 

        DoubleNumber& operator - (DoubleNumber nextNum) {       // overdrive "-" operator 
            number = number - nextNum.number;
            return *this;
        }

        bool operator > (DoubleNumber& rightNum) {     // overdrive ">" operator 
            return number > rightNum.number;
        }

        void operator () (double num) {
            number = num;
        }

        friend void operator -- (DoubleNumber& num, int);
        friend DoubleNumber operator + (DoubleNumber leftNum, DoubleNumber rightNum);
        friend ostream& operator << (std::ostream& out, DoubleNumber num);

        int ToInt() {
            return int(number);
        }

        SquareNumber ToSquare() {
            return SquareNumber(number);
        }

        friend class SquareNumber;
};

void operator -- (DoubleNumber& num, int) { 
    num.number--; 
}

DoubleNumber operator + (DoubleNumber leftNum, DoubleNumber rightNum) {       // overdrive "-" operator 
    return DoubleNumber(leftNum.number +rightNum.number);
}

ostream& operator << (std::ostream& out, DoubleNumber num) {
    return out << num.number;
}

ostream& operator << (std::ostream& out, SquareNumber num) {
    return out << num.nmb;
}

string BoolToString(bool par) {
    return par ? "True" : "False";
}

int main()
{
    DoubleNumber one(19.12);
    DoubleNumber two(7.978);

    cout << "One = " << one << endl;
    cout << "Two = " << two << endl << endl;

    int p = two.ToInt();
    cout << "Two to int = " << p << endl;

    one++;
    cout << "One increment = " << one << endl;

    cout << "One + Two = " << one + two << endl;

    two--;
    cout << "Two decrement = " << two << endl;

    bool isTrue = one > two;
    cout << "Is One bigger than Two? " << BoolToString(isTrue) << endl;

    SquareNumber pow = one.ToSquare();
    cout << "Square one = " << pow << endl;

    return 0;
}