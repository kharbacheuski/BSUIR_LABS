#include <iostream>
#include <vector>
using namespace std;

static int ID;

class Employee {
	private:
		int id;
		string name;
		double solary;

	public:
		Employee(string _name, double _solary) {
			ID = 0;
			id = ID++; name = _name; solary = _solary;
		};

		void CheckSolary() {
			cout << "My solary is " << solary << endl;
		}

		~Employee() {}

		friend void CheckInfo(Employee& empl);
		friend class Accountant;
};
void CheckInfo(Employee& empl) {
	cout << "Name: " << empl.name << endl;
	cout << "Id: " << empl.id << endl;
	cout << "Solary: " << empl.solary << endl;
}

class Accountant {
	public:
		Accountant() {}

		double setSolary(Employee& employee, double newSolary) {
			employee.solary = newSolary;
			return newSolary;
		}

		~Accountant() {}
};

int main() {
	string name;
	double solry;
	cout << "Enter name of employee: " << endl;
	cin >> name;
	cout << "Enter solry for employee: " << endl;
	cin >> solry;
	cout << endl;

	Employee One = Employee(name, solry);

	cout << "Enter name of employee: " << endl;
	cin >> name;
	cout << "Enter solry for employee: " << endl;
	cin >> solry;
	cout << endl;

	Employee Two = Employee(name, solry);
	Accountant Buh;

	int id;
	double solary;

	cout << "Enter ID of employee: " << endl;
	cin >> id;
	cout << "Enter new solary for this employee: " << endl;
	cin >> solary;

	One.CheckSolary();
	Buh.setSolary(One, solary);
	One.CheckSolary();
	CheckInfo(One);

	cout << "Enter ID of employee: " << endl;
	cin >> id;

	cout << "Enter new solary for this employee: " << endl;
	cin >> solary;
	cout << endl << endl;

	Two.CheckSolary();
	Buh.setSolary(Two, solary);
	Two.CheckSolary();
	CheckInfo(Two);

	return 0;
}