// Including header files
#pragma once
#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace utility::conversions;

#include <iostream>
#include<windows.h>
#include<map>
using namespace std;

// Global Functions

string slice(string str);					// Method for removing first and last character from string

void display_json(							// Method for displaying json object 
	json::value const & jvalue,
	utility::string_t const & prefix);

void stringtomap(string);					// Method for converting string to map

void jsontopairvector(json::value jvalue);	// Method for converting json to vector containing map element

bool validate_int(string);					// Method to validate integer input
bool validate_alphastring(string);			// Method to validate alphabetic input with spaces
bool validate_email(string);				// Method to validate email input
bool validate_password(string);				// Method to validate password input
bool validate_username(string);				// Method to validate username input
string convert_airport_name(string);		// Method to covert airport name for sending requests to server
