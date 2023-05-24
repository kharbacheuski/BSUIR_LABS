#pragma once
#include <iostream>
#include <string>
#include "Constants.h"

using namespace std;

bool numberValidation(string number) {

	if (number.length() != 13) {
		cout << endl << WrongNumberLength << endl;

		return false;
	}

	string countryCode = "0000";

	for(int i = 0; i < 4; i++)
		countryCode[i] = number[i];

	if (countryCode != ValidCountryCode) {
		cout << endl << WrongCountryCode << endl;
		return false;
	}

	string operatorCode = "00";
	operatorCode[0] = number[4];
	operatorCode[1] = number[5];

	bool validOperatorCodeFlag = false;

	for (int n = 0; n < validCodes->size(); n++) {
		if (operatorCode == validCodes[n]){
			validOperatorCodeFlag = true;
			break;
		}
	}

	if (!validOperatorCodeFlag) {
		cout << endl << WrongOperatorCode << endl;
		return false;
	}

	for (int n = 6; n < number.length(); n++) {
		if (number[n] > '9' || number[n] < '0') {
			cout << endl << WrongSymbols << endl;
			return false;
		}
	}

	return true;
}
