#include <iostream>
using namespace std;

class Workman {
public:
    string profession;

    Workman(){}

    Workman(string _prof) {
        profession = _prof;
    }

    ~Workman(){}

    void GetProfession() {
        cout << "My profession is " << this->profession << endl;
    }
};

class Programmer : public virtual Workman {
protected:
    string language;
public:
    Programmer(string _prof, string _lang) : Workman(_prof) {
        language = _lang;
        profession = _prof;
    }
    ~Programmer(){}

    void GetLanguage() {
        cout << "My programming language is " << this->language << endl;
    }
};

class Frontend : public Programmer {
protected:
    string framework;
public:
    Frontend(string _prof, string _lang, string _frame) : Programmer(_prof, _lang) {
        framework = _frame;
    }
    ~Frontend() {}

    void GetFramework() {
        cout << "My framework is " << this->framework << endl;
    }
};

class Designer : public virtual Workman {
protected:
    string department;
public:
    Designer(string _prof, string _dep): Workman(_prof) {
        profession = _prof;
        department = _dep;
    }
    ~Designer() {}

    void GetDepartment() {
        cout << "My department is " << this->department << endl;
    }
};

class WebDesigner : public Designer {
protected:
    int stage;
public:
    WebDesigner(int _stage, string _prof, string _dep) : Designer(_prof, _dep) {
        stage = _stage;
    }
    ~WebDesigner() {}

    void GetStage() {
        cout << "My stage " << this->stage << endl;
    }
};


class SiteDeveloper : public Frontend, public WebDesigner {
protected:
    string companyName;
public:
    SiteDeveloper(string _cmpName, string _prof, string _frame, int _stage, string _dep, string _lang) 
    :Frontend(_prof, _lang, _frame), WebDesigner(_stage, _prof, _dep) {
        companyName = _cmpName;
    }
   

    ~SiteDeveloper() {}

    void GetInfo() {
        cout << "Hello, I am " << this->profession << endl;
        cout << "My company's name is " << this->companyName << endl;
        cout << "I write in " << this->language << " (" << this->framework << " framework)" << endl;
        cout << "I've been writing code for " << this->stage << " years now" << endl;
        cout << "You can find me in <" << this->department << "> department" << endl;
    }
};

int main() {
    
    SiteDeveloper Paul("SOFT-FX", "frontend developer", "React", 15, "info communication", "JavaScript");

    Paul.GetInfo();

    return 0;
}


