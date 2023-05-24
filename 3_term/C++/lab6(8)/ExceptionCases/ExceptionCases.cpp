#include <iostream>;
#include <vector>;
using namespace std;

template <typename T>
class Stack {
    public:
        inline static T stackArray[20] = {0.0};

        T* begin = stackArray;
        T* end = stackArray;

        Stack() {}

        void printStack() {
            try {
                if (end == begin)
                    throw true;

                for (int i = 0; i < 20; i++) {
                    cout << stackArray[i] << " ";
                }
                cout << endl << endl;
            }
            catch (...) {
                CustomException::stackIsEmpty();
            }

        }

        void push(T _pushingElem) {
            try {
                if (*end > 19) 
                    throw true;

                *(end++) = _pushingElem;
            }
            catch (...) {
                CustomException::stackIsFull();
            }        
        }

        T pop() {
            try {
                if (end == begin) 
                    throw true;

                T a = *(end--);
                return a;
            }
            catch (...) {
                CustomException::stackIsEmpty();
            }
        }

        void checkTopElement() {
            try {
                if (end == begin)
                    throw true;

                cout << "Top element: " << *(end - 1);
                cout << endl << endl;
            }
            catch (...) {
                CustomException::stackIsEmpty();
            }
        }

        friend class CustomException;
};

class CustomException {
public: 
    static void stackIsEmpty() {
        cout << "Error! Stack is empty" << endl;
        terminate();
    }
    static void stackIsFull() {
        cout << "Error! Stack is full" << endl;
        terminate();
    }
};

int main() {
    Stack<double> Stc;

    Stc.push(12.56);
    Stc.printStack();
    Stc.push(7);
    Stc.push(746);
    Stc.push(1.25);
    Stc.push(0);
    Stc.pop();
    Stc.checkTopElement();
    Stc.printStack();

    return 0;
}