#pragma once
#include <string>
#include <iostream>

using namespace std;

class ExceptionClass {
public:
	string exception_message;

	ExceptionClass() {}

	ExceptionClass(string _exm) {
		exception_message = _exm;
	}
	~ExceptionClass() {}
};