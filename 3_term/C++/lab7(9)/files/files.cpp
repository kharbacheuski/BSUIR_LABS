#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdio.h>

#define FNAME "Tourists.txt"
#define FNAMEbin "TouristsBinary.bin"

#define FILE_OPEN_ERROR "Error open file"
#define STRING_LENGTH 20

using namespace std;

bool binaryFlag = 0;
bool isBinaryFile = 0;

class Tourist {
public:
	string name;
	string whereFrom;
	string daysOfVacances;

	Tourist() {}
	Tourist(string _nm, string _country, string _countDays) {
		name = _nm;
		whereFrom = _country;
		daysOfVacances = _countDays;
	}
	~Tourist() {}

	void showInfo() {
		cout << "My name is " << name << endl;
		cout << "I'm from " << whereFrom;
	}
};

class AllTourists {
	public:
		vector<Tourist> tour;

		AllTourists() {}

		void addRecord() {
			Tourist r;

			cout << "\n\n\t\t[ Добавление новой записи ]\n\n";

			cout << "Введите имя туриста: ";
			cin >> r.name;

			cout << "Введите откуда турист: ";
			cin >> r.whereFrom;

			cout << "Введите кол-во дней отпуска: " << endl;
			cin >> r.daysOfVacances;

			tour.push_back(r);
			cout << "Новая запись с порядковым номером "
				<< tour.size() << " добавлена!" << endl << endl;
			cin.get();

			if (binaryFlag) {
				try {
					ofstream fout(isBinaryFile ? FNAMEbin : FNAME, ios::binary | ios::app);

					if (fout.bad() || !fout.is_open()) {
						fout.close();
						throw FILE_OPEN_ERROR;
					}

					fout.write(r.name.c_str(), r.name.size());
					fout.write("\n", 1);
					fout.write(r.whereFrom.c_str(), r.whereFrom.size());
					fout.write("\n", 1);
					fout.write(r.daysOfVacances.c_str(), r.daysOfVacances.size());
					fout.write("\n", 1);

					fout.close();
				}
				catch (string e) {
					cout << e;
				}
			}

			!binaryFlag && this->saveToFile();
		}

		void deleteRecord() {
			cout << "\n\n\t\t[ Удаление записи ]\n\n";

			char ans = 'n';
			int id = this->findRecord();

			if (id == -1)
			{
				cout << "Удаление не удалось!" << endl;
				return;
			}

			cout << endl;
			cout << "Вы уверены? (y/n)? " << endl << endl;
			cin >> ans;

			if (ans == 'y' || ans == 'Y')
			{
				tour.erase(tour.begin() + id);
				cout << "Запись с порядковым номером "
					<< id + 1 << " удалена!" << endl
					<< "Учтите, что все порядковые номера других записей сдвинулись!" << endl << endl;
				cin.get();

				binaryFlag?this->saveToFileBinary():this->saveToFile();
			}
		}

		int findRecord() {
			int sel;

			cout << "Вам нужно найти запись:" << endl
				<< "1. По порядковому номеру" << endl
				<< "2. По имени" << endl
				<< "\n\n > ";

			cin >> sel;
			cout << endl;

			if (sel == 2) {
				string val;
				
				bool isFind = false;

				while (!isFind) {
					cout << "Введите значение для поиска: ";
					cin.clear();
					rewind(stdin);
					getline(cin, val);

					for (int i = 0; i < tour.size(); i++) {
						if (tour[i].name == val) {
							isFind = true;
							this->readRecordFromFile(i);
							return i;
						}
					}
					!isFind && cout << endl << "Турист не найден. Попробуйте еще раз." << endl << endl;
				}

				cout << endl;
			}

			int number;
			bool fail = false;

			cout << "Введите порядковый номер записи: ";
			cin >> number;

			if (number < 1 || number > tour.size()) {
				this->notFound();
				return -1;
			}
			else this->readRecordFromFile(number - 1);

			return number - 1;
		}

		void readRecordFromFile(int index = -1) {

			if (index == -1) {
				cout << "Всего " << tour.size() << " записей:" << endl << endl;

				for (int i = 0; i < tour.size(); i++) {
					cout << i+1 << ". "
						<< tour[i].name << "  "
						<< tour[i].whereFrom << "  "
						<< tour[i].daysOfVacances << endl;
				}
			}
			else {
				cout << index + 1 << ". "
					<< tour[index].name << "  "
					<< tour[index].whereFrom << "  "
					<< tour[index].daysOfVacances << endl;
			}
		}

		int readRecordFromFileReverse() {
			for (int i = tour.size()-1; i >= 0; i--) {
				cout << i + 1 << ". "
					<< tour[i].name << "  "
					<< tour[i].whereFrom << "  "
					<< tour[i].daysOfVacances << endl;
			}

			return 1;
		}

		void notFound() {
			cout << endl << "Записи с данным порядковым номером не существует" << endl;
		}

		bool saveToFile() {
			try {
				ofstream fout(FNAME);

				if (fout.bad() || !fout.is_open())
				{
					throw FILE_OPEN_ERROR;
					fout.close();
				}

				for (int i = 0; i < tour.size(); i++)
				{
					fout << tour[i].name << endl
						<< tour[i].whereFrom << endl
						<< tour[i].daysOfVacances << endl;
				}

				fout.close();
				return true;
			}
			catch (string e) {
				cout << e;
				return false;
			}
		}

		bool saveToFileBinary() {
			try {
				ofstream fout(isBinaryFile ? FNAMEbin : FNAME, ios::binary | ios::trunc); // open and clear file
				fout.close();

				fout.open(isBinaryFile ? FNAMEbin : FNAME, ios::binary | ios::app);

				if (fout.bad() || !fout.is_open()) {
					fout.close();

					throw FILE_OPEN_ERROR;
				}

				for (int i = 0; i < tour.size(); i++)
				{
					fout.write(tour[i].name.c_str(), tour[i].name.size());
					fout.write("\n", 1);
					fout.write(tour[i].whereFrom.c_str(), tour[i].whereFrom.size());
					fout.write("\n", 1);
					fout.write(tour[i].daysOfVacances.c_str(), tour[i].daysOfVacances.size());
					fout.write("\n", 1);
				}

				fout.close();
				return true;
			}
			catch (string e) {
				cout << e;
				return false;
			}
		}


		bool loadFromFile() {
			try {
				ifstream fin(isBinaryFile ? FNAMEbin : FNAME);

				if (fin.bad() || !fin.is_open()) {
					fin.close();

					throw FILE_OPEN_ERROR;
				}

				tour.clear();

				while (!fin.eof()) {
					Tourist t;
					if (!getline(fin, t.name) ||
						!getline(fin, t.whereFrom) ||
						!getline(fin, t.daysOfVacances))
						break;

					tour.push_back(t);
				}

				fin.close();
				return true;
			}
			catch (string e) {
				cout << e;
				return false;
			}
		}

		bool loadFromFileBinary() {
			ifstream fin;
			Tourist st;

			fin.open(isBinaryFile ? FNAMEbin : FNAME, ios::binary);

			while (getline(fin, st.name, isBinaryFile?'\n':'\r')) {
				if (fin.eof())
					break;

				!isBinaryFile && fin.get();
				getline(fin, st.whereFrom, isBinaryFile ? '\n' : '\r');

				!isBinaryFile && fin.get();
				getline(fin, st.daysOfVacances, isBinaryFile ? '\n' : '\r');

				!isBinaryFile && fin.get();

				tour.push_back(st);
			}
			fin.close();
			return true;
		}
};

AllTourists Box;


bool menu() {
	int sel;

	cout << "\n\n\t\t[ Главное меню ]\n\n";

	cout 
		<< "1. Посмотреть список записей (" << Box.tour.size() << ")" << endl
		<< "2. Добавить новую запись" << endl
		<< "3. Удалить запись" << endl
		<< "4. Найти запись" << endl
		<< "5. Реверсивный вывод" << endl
		<< "6. Выход" << endl << endl;


	cin.clear();
	rewind(stdin);
	cout << endl << " > ";
	cin >> sel;
	

	switch (sel) {
		case 1: Box.readRecordFromFile(); break;
		case 2: Box.addRecord(); break;
		case 3: Box.deleteRecord(); break;
		case 4: Box.findRecord(); break;
		case 5: Box.readRecordFromFileReverse(); break;
		case 6: return false; break;
		default: break;
	}

	return true;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char f;
	cout << "Работаем в бинарном режиме? (y/n): ";
	cin >> f;

	binaryFlag = bool(f == 'y' || f == 'Y');

	cout << "Работаем c бинарным файлом? (y/n): ";
	cin >> f;

	if (bool(f == 'y' || f == 'Y')) {
		isBinaryFile = true;

		if (!binaryFlag) {
			cout << endl << 
			"С бинарным файлом нельзя работать в небинарном режиме. Устанавливаю бинарный режим." 
			<< endl;

			binaryFlag = true;
		}
	}

	binaryFlag?Box.loadFromFileBinary():Box.loadFromFile();

	while (menu()) {};


	return 0;
}