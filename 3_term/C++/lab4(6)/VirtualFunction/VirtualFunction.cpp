#include <iostream>
using namespace std;

class Workman { // abstract class
protected:
	string name;

public:
	Workman() {};
	Workman(string _name) {
		name = _name;
	}
	virtual ~Workman() {}

	virtual void print() = 0; // clear virtual function;
};

class Builder : public Workman {
protected: 
	int stage;
public:
	Builder(int _st, string _name) : Workman(_name) {
		stage = _st;
	}
	void print() { 
		cout << "My name is " << name << " Stage - " << stage << " years" << endl;
	}
	~Builder() {}
};

class RoadBuilder : public Builder {
protected:
	int roadKM;
public:
	RoadBuilder(int _km, int _stage, string _name) :  Builder(_stage, _name) {
		roadKM = _km;
	}
	void print() { 
		cout << "I am " << name << "Stage - " << stage <<  ". I builded " << roadKM << " km of roads." << endl; 
	} 
	~RoadBuilder() {}
};

class Teacher : public Workman {
protected:
	string discipline;
public:
	Teacher(string _dis, string _name) : Workman(_name) {
		discipline = _dis;
	}
	void print() { 
		cout << "I am " << name << ". " << discipline << " teacher." << endl;
	} 

	~Teacher() {}
};

int main()
{	
	int countOfElements;
	cout << "Enter count of elements: ";
	cin >> countOfElements;
	Workman **BaseClasses = new Workman*[countOfElements];

	for (int i = 0; i < countOfElements; i++) {
		int classType;
		cout << "Create some class (1, 11 or 2): ";
		cin >> classType;

		switch (classType) {
			case 1: {
				cout << "Class Builder. Enter stage and name: " << endl;
				int stage;
				string name;
				cin >> stage;
				cin >> name;

				BaseClasses[i] = new Builder(stage, name);
			} break;

			case 11: {
				cout << "Class RoadBuilder. Enter km of roads, stage and name: " << endl;
				int km;
				int stage;
				string name;
				cin >> km;
				cin >> stage;
				cin >> name;

				BaseClasses[i] = new RoadBuilder(km, stage, name);
			} break;

			case 2: {
				cout << "Class Teacher. Enter discipline and name: " << endl;
				string discipline;
				string proffession;

				cin >> discipline;
				cin >> proffession;

				BaseClasses[i] = new Teacher(discipline, proffession);
			} break;		  
		}
	}
	for (int j = 0; j < countOfElements; j++) {
		cout << endl << endl;
		(*BaseClasses[j]).print();
	}

	delete[] BaseClasses;

	return 0;
}