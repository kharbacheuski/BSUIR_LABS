#pragma once

#include <iostream>
#include <fstream>
#include <string>

// File paths
#define AddressesFNAME "addresses.json"
#define PersonsFNAME "persons.json"
#define FriendsFNAME "friend-friend.json"

// Exception message constants
#define OpenFileError "Cannot open file. Check file path..."
#define SaveFileError "Cannot save file :("

// Phone Validation
#define WrongNumberLength "Wrong number length!"
#define WrongCountryCode "Wrong country code. Code must be +375"
#define WrongOperatorCode "Wrong operator code. Valid operators code: 29, 25, 33, 44"
#define WrongSymbols "Number contains not valid symbols"

const std::string ValidCountryCode = "+375";
const std::string validCodes[] = { "29", "25", "33", "44" };


enum PersonType {
    legal = 1,
    phisical = 0
};