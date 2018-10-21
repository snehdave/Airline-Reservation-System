// Including header files
#pragma once
#include"User.h"
#include"Requester.h"

// Declaring extern global variables
extern bool user_exists;

/**********************************************************/
// Name: login_details
// Description: To fetch and validate various account information
//				from user.
/**********************************************************/
bool User::login_details() {

	// Local variables declaration
	string str;

	// Clearing screen
	system("cls");

	cout << "\n\n\n\n\n\t\t\t****************************";
	cout << "\n\t\t\tLOGIN DETAILS:";

	// Fetch and validate name of user
	while (1) {
		cout << "\n\n\t\t\tEnter your name: ";
		getline(cin, str);
		if (!validate_alphastring(str)) {
			cout << "\n\t\t\t Please enter only alphabetic input.";
			continue;
		}
		name = str;
		break;
	}

	// Fetch and validate age of user
	while (1) {
		cout << "\n\n\t\t\tEnter you age: ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		if (stoi(str) < 1 || stoi(str) > 125) {
			cout << "\n\t\t\t Please enter age between 1 year to 125 years.";
			continue;
		}
		age = stoi(str);
		break;
	}

	// Fetch and validate email id of user
	while (1) {
		cout << "\n\n\t\t\tEnter you email id: ";
		getline(cin, str);
		if (!validate_email(str)) {
			cout << "\n\t\t\t Please enter a valid email id.";
			continue;
		}
		emailid = str;
		break;
	}
	
	// Fetch and validate username
	while (1) {
		cout << "\n\n\t\t\tEnter username: ";
		getline(cin, str);
		if (!validate_username(str)) {
			cout << "\n\t\t\t Please enter only alphabetic input without spaces.";
			continue;
		}

		// Making a GET call to server to check if username already exists
		auto nullvalue = json::value::null();
		string uri = "http://localhost:80/userDetails/" + str;
		Requester obj(uri);
		obj.make_request(methods::GET, nullvalue);

		// Validation for existing username
		if (user_exists){
			cout << "\n\t\t\t Username already exists. Please enter new user name.";
			continue;
		}
		user_exists = 1;
		username = str;
		break;
	}

	// Fetch and validate passowrd
	// Give 3 tries to user for password entry
	for (int i = 0; i < 3; i++) {

		cout << "\n\n\t\t\tPassword should only contain alphabets or digits (A-Z,a-z,0-9).";

		// Fetch password
		string tmpPasswd = fetch_password("\n\n\t\t\tEnter Password  : ");

		// Validate password
		if (!validate_password(tmpPasswd)) {
			cout << "\n\n\t\t\t Please enter a valid password.";
			continue;
		}

		// Fetch confirmation password
		string tmpConfPasswd = fetch_password("\n\n\t\t\tConfirm Password  : ");

		// Check if both password matches
		if (tmpPasswd == tmpConfPasswd) {
			password = tmpConfPasswd;
			return 1;
		}
		else
		{
			cout << "\n\n\t\t\tPasswords donot match!";
		}
	}
	return 0;
}

/**********************************************************/
// Name: fetch_password
// Description: To fetch password from console. Hides password 
//				with * on console.
/**********************************************************/
string User::fetch_password(string str) {

	// Local variable declarations
	cout << str;
	string pass;
	int i = 0;
	char a;

	// Loop to fetch password
	for (i = 0;;)
	{
		a = _getch();
		if (a == '\b' && i > 0) //if user typed backspace
							  
		{
			cout << "\b \b";
			pass.pop_back();
			i--;
		}
		else if (a == '\r') //if enter is pressed
		{
			break;
		}
		else if(isalnum(a)) {
			pass += a;
			cout << "*";
			i++;
		}
	}
	return pass;
}