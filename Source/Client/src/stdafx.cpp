// Including header files
#pragma once
#include"stdafx.h"


// Declaring global variables
extern map<string, string> pairs;
extern vector<map<string, string>> pairs_vector;

/**********************************************************/
// Name: slice
// Description: Removes first and last charater from string
/**********************************************************/
string slice(string str) {
	return str.substr(1, str.size() - 2);
}

/**********************************************************/
// Name: display_json
// Description: Displays json as string on console
/**********************************************************/
void display_json(
	json::value const & jvalue,
	utility::string_t const & prefix)
{
	wcout << prefix << jvalue.serialize() << endl;
}

/**********************************************************/
// Name: stringtomap
// Description: Converts given string to map
/**********************************************************/
void stringtomap(string str) {
	pairs.clear();
	str = slice(str);
	str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
	//cout << str;
	size_t n = std::count(str.begin(), str.end(), ',');
	size_t found;
	string pair,key,value;
	for (int i = 0; i < n; i++) {
		found = str.find_first_of(",");
		pair = str.substr(0, found);
		str = str.substr(found + 1);
		//cout << pair << endl << endl;

		found = pair.find(":");
		key = pair.substr(0, found);
		value = pair.substr(found + 1);
		//cout << key << endl << endl;
		//cout << value << endl << endl;
		pairs.insert(make_pair(key, value));
	}
	pair=str;
	found = pair.find(":");
	key = pair.substr(0, found);
	value = pair.substr(found + 1);
	//cout << key << endl << endl;
	//cout << value << endl << endl;
	pairs.insert(make_pair(key, value));
}

/**********************************************************/
// Name: jsontopairvector
// Description: Converts json object to vector containing key-value pairs
/**********************************************************/
void jsontopairvector(json::value jvalue) {
	pairs_vector.clear();
	if (jvalue[L"Flights"].is_array()) {
		auto obj = jvalue[L"Flights"].as_array();
		for (int i = 0; i<obj.size(); i++) {
			stringtomap(to_utf8string(obj[i].serialize()));
			pairs_vector.push_back(pairs);
		}
	}
	else 
	{
		auto obj = jvalue[L"Bookings"].as_array();
		for (int i = 0; i<obj.size(); i++) {
			stringtomap(to_utf8string(obj[i].serialize()));
			pairs_vector.push_back(pairs);
		}
	}

}

/**********************************************************/
// Name: validate_int
// Description: Validates if given string is integer
/**********************************************************/
bool validate_int(string str) {
	if (str.empty() || str.size() > 6)
		return 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return 0;
	}
	return 1;
}

/**********************************************************/
// Name: validate_username
// Description: Validates if given string is username
/**********************************************************/
bool validate_username(string str) {
	if (str.empty())
		return 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (!isalpha(str[i]))
			return 0;
	}
	return 1;
}

/**********************************************************/
// Name: validate_alphastring
// Description: Validates if given string contains only alphabets or spaces
/**********************************************************/
bool validate_alphastring(string str) {
	if (str.empty())
		return 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (!isalpha(str[i]) && !isspace(str[i]))
			return 0;
	}
	return 1;
}

/**********************************************************/
// Name: validate_email
// Description: Validates if given string is email
/**********************************************************/
bool validate_email(string str) {
	if (str.empty())
		return 0;

	if (str.find("@") == string::npos || str.find(".") == string::npos)
			return 0;

	if (std::count(str.begin(), str.end(), '@') > 1)
		return 0;

	if (std::count(str.begin(), str.end(), ',') > 0)
		return 0;

	return 1;
}

/**********************************************************/
// Name: validate_password
// Description: Validates if given string is pssword
/**********************************************************/
bool validate_password(string str) {
	if (str.empty())
		return 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (!isalnum(str[i]))
			return 0;
	}
	return 1;
}

/**********************************************************/
// Name: convert_airport_name 
// Description: Replaces spaces with underscore in givens string
/**********************************************************/
string convert_airport_name(string str) {
	string result;
	size_t n = std::count(str.begin(), str.end(), ' ');

	if (n == 0)
		return str;

	size_t found;
	for (int i = 0; i < n; i++) {
		found = str.find(" ");
		result += str.substr(0,found) + "_";
		str = str.substr(found + 1);
	}
	result += str;
	return result;
}
