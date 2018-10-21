// Including header files
#pragma once
#include"Admin.h"
#include"Requester.h"

// Declaring extern global variables
extern map<string, string> pairs;
extern vector<map<string, string>> pairs_vector;
extern bool user_exists;
extern vector<int> available_options;

/**********************************************************/
// Name: create_account
// Description: To fetch login details from user. If input details
//				are valid then create payload and send POST request to
//				server for creating new account.
/**********************************************************/
void Admin::create_account() {
	// Clearing screen
	system("cls");

	// Fetch and validate account creation details from user 
	if (login_details()) {

		// Creating payload json object 
		auto body = json::value::array();
		body[0] = json::value::string(to_utf16string(name));
		body[1] = json::value::string(to_utf16string(to_string(age)));
		body[2] = json::value::string(to_utf16string(username));
		body[3] = json::value::string(to_utf16string(password));
		body[4] = json::value::string(to_utf16string(emailid));
		body[5] = json::value::string(L"A");

		// Sending request to the server for account creation
		string uri = "http://localhost:80/createAccount/";
		Requester obj(uri);
		obj.make_request(methods::POST, body);

		cout << "\n\t\t\tAccount Created!\n\t\t\t";
		system("pause");
	}
	else {
		cout << "\n\t\t\tAccount creation failed!\n\t\t\t";
		system("pause");
	}
}

/**********************************************************/
// Name: sign_in
// Description: To take username and password from user as input.
//				Validate username, password and account type.
/**********************************************************/
bool Admin::sign_in() {
	
	// Clearing screen
	system("cls");

	// Local variable declarations
	string tmpUsername, tmpPasswd, str;

	cout << "\n\n\n\n\n\t\t\t****************************";
	cout << "\n\t\t\tLOGIN DETAILS:";

	// Fetch and validate username
	while (1) {
		cout << "\n\n\t\t\tEnter username: ";
		getline(cin, str);
		if (!validate_username(str)) {
			cout << "\n\t\t\t Please enter only alphabetic input without spaces.";
			continue;
		}
		tmpUsername = str;
		break;
	}

	// Fetch and validate password
	while (1) {
		cout << "\n\t\t\tPassword should only contain alphabets or digits (A-Z,a-z,0-9).";
		str = fetch_password("\n\t\t\tEnter Password  : ");
		if (!validate_password(str)) {
			cout << "\n\t\t\t Please enter a valid password.";
			continue;
		}
		tmpPasswd = str;
		break;
	}
	
	// Make a GET request to server to fetch user details
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/userDetails/" + tmpUsername;
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);

	// Check if user exists in database
	if (user_exists) {

		// Check if password and account type matches the user input
		if (pairs.at("password") == tmpPasswd && pairs.at("utype") == "A") {
			cout << "\n\t\t\tLogin Successful!\n\t\t\t";
			system("pause");
			return 1;
		}
		else {
			cout << "\n\t\t\tLogin Unsuccessful!\n\t\t\t";
			system("pause");
			return 0;
		}
	}
	else {
		user_exists = 1;
		cout << "\n\t\t\tUsername doesn't exist. Please enter correct username.\n\t\t\t";
		system("pause");
		return 0;
	}
}

/**********************************************************/
// Name: show_options
// Description: Displays options for creating new flight, 
//				displaying exsitng flight, deleting existing flight
/**********************************************************/
void Admin::show_options() {

	// Local variable decarations
	bool contFlag = 0;
	int choice;
	string str;

	// do-while loop to display options until back button is pressed
	do {

		// Clearing screen 
		system("cls");

		// Displaying options to the user
		cout << "\n\n\n\n\n\t\t\t****************************";
		cout << "\n\t\t\tADMINISTRATOR OPTIONS:";
		cout << "\n\n\t\t\t1. Create New Flight";
		cout << "\n\t\t\t2. Display All Flights";
		cout << "\n\t\t\t3. Delete Existing Flight";
		cout << "\n\t\t\t4. Back";
		cout << "\n\t\t\t****************************";
		cout << "\n\n\t\t\t Enter your choice: ";

		// Fetch and validate user input
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
			continue;
		}
		choice = stoi(str);

		// switch-case structure to handle various options
		switch (choice) {
		case 1: {
			// Function call to create a new flight
			create_flight();
			break;
		}
		case 2: {

			// Clearing screen
			system("cls");

			cout << "\n*********************";
			cout << "\n ALL FLIGHT DETAILS:";
			cout << "\n*********************";

			// Function call to display existing flights
			display_all_flights();
			system("pause");
			break;
		}
		case 3: {

			// Clearing screen
			system("cls");

			cout << "\n*********************";
			cout << "\n DELETE EXISTING FLIGHT:";
			cout << "\n*********************";

			// Function call to delete existing flight
			delete_flight();
			break;
		}
		case 4: {
			// Go back to previous menu
			contFlag = 1;
			break;
		}
		default: {
			// Error message for invalid user input
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
		}
		}
	} while (contFlag == 0);
}

/**********************************************************/
// Name: create_flight
// Description: To create new flight in database. Fetches various
//				parameters from user and makes a POST call to the server
/**********************************************************/
void Admin::create_flight() {
	
	// Local variable declarations
	string str, fltID, depAirport;
	auto body=json::value::array();

	// Clearing screen
	system("cls");

	cout << "\n\n\n\n\n\t\t\t****************************";
	cout << "\n\t\t\tFLIGHT DETAILS:";

	// Fetch and validate flight name
	while (1) {
		cout << "\n\n\t\t\tEnter Flight Name: ";
		getline(cin, str);
		if (!validate_alphastring(str)) {
			cout << "\n\t\t\t Please enter only alphabetic input.";
			continue;
		}
		body[0] = json::value::string(to_utf16string(str));
		break;
	}

	// Fetch and validate departure airport
	while (1) {
		cout << "\n\n\t\t\tEnter Departure Airport: ";
		getline(cin, str);
		if (!validate_alphastring(str)) {
			cout << "\n\t\t\t Please enter only alphabetic input.";
			continue;
		}
		depAirport = str;
		body[1] = json::value::string(to_utf16string(str));
		break;
	}
	
	// Fetch and validate arrival airport
	while (1) {
		cout << "\n\n\t\t\tEnter Arrival Airport: ";
		getline(cin, str);
		if (!validate_alphastring(str)) {
			cout << "\n\t\t\t Please enter only alphabetic input.";
			continue;
		}
		// Validation for arrival and departure airport name to be same
		if (depAirport == str) {
			cout << "\n\t\t\t Arrival Airport cannot be same as Departure airport.";
			continue;
		}
		body[2] = json::value::string(to_utf16string(str));
		break;
	}

	// Fetch and validate departure time hours
	while (1) {
		cout << "\n\n\t\t\tEnter Departure Time (Hours): ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		// Validation for hours between 0 and 23
		if (stoi(str) < 0 || stoi(str) > 23) {
			cout << "\n\t\t\t Please enter hours between 0  to 23.";
			continue;
		}
		body[3] = json::value::string(to_utf16string(str));
		break;
	}

	// Fetch and validate departure time minutes
	while (1) {
		cout << "\n\n\t\t\tEnter Departure Time (Minutes): ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		// Validation for minutes between 0 and 59
		if (stoi(str) < 0 || stoi(str) > 59) {
			cout << "\n\t\t\t Please enter hours between 0  to 59.";
			continue;
		}
		body[4] = json::value::string(to_utf16string(str));
		break;
	}

	// Fetch and validate arrival time hours
	while (1) {
		cout << "\n\n\t\t\tEnter Arrival Time (Hours): ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		// Validation for hours between 0 and 23
		if (stoi(str) < 0 || stoi(str) > 23) {
			cout << "\n\t\t\t Please enter hours between 0  to 23.";
			continue;
		}
		body[5] = json::value::string(to_utf16string(str));
		break;
	}
	
	// Fetch and validate arrival time minutes
	while (1) {
		cout << "\n\n\t\t\tEnter Arrival Time (Minutes): ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		// Validation for minutes between 0 and 59
		if (stoi(str) < 0 || stoi(str) > 59) {
			cout << "\n\t\t\t Please enter hours between 0  to 59.";
			continue;
		}
		body[6] = json::value::string(to_utf16string(str));
		break;
	}

	// Fetch and validate seating capacity economy
	while (1) {
		cout << "\n\n\t\t\tEnter Seating Capacity (Economy): ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		// Validation for minutes between 10 and 525
		if (stoi(str) < 10 || stoi(str) > 525) {
			cout << "\n\t\t\t Please enter seats between 10 to 525.";
			continue;
		}
		body[7] = json::value::string(to_utf16string(str));
		break;
	}

	// Fetch and validate seating capacity first class
	while (1) {
		cout << "\n\n\t\t\tEnter Seating Capacity (Firstclass): ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		// Validation for minutes between 1 and 100
		if (stoi(str) < 1 || stoi(str) > 100) {
			cout << "\n\t\t\t Please enter seats between 1 to 100.";
			continue;
		}
		body[8] = json::value::string(to_utf16string(str));
		break;
	}

	// Fetch and validate economy class price
	while (1) {
		cout << "\n\n\t\t\tEnter Economy Price ($): ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		// Validation for positive amount
		if (stoi(str) < 1) {
			cout << "\n\t\t\t Please enter positive integer.";
			continue;
		}
		body[9] = json::value::string(to_utf16string(str));
		break;
	}

	// Fetch and validate price for firstclass
	while (1) {
		cout << "\n\n\t\t\tEnter Firstclass Price ($): ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\t\t\t Please enter integer number only.";
			continue;
		}
		// Validation for positive amount
		if (stoi(str) < 1) {
			cout << "\n\t\t\t Please enter positive integer.";
			continue;
		}
		body[10] = json::value::string(to_utf16string(str));
		break;
	}

	// Sending post request to server for flight creation
	string uri = "http://localhost:80/createFlight/";
	Requester obj(uri);
	obj.make_request(methods::POST, body);	

	cout << "\n\t\t\tFlight Created!\n\t\t\t";
	system("pause");
}

/**********************************************************/
// Name: display_all_flights
// Description: To make a GET call to server to fetch all flight
//				details from database and display them on console.
/**********************************************************/
void Admin::display_all_flights() {

	// Clearing out available_options vector
	available_options.clear();

	// Local variable declarations
	string hours;

	// Display formatted output on console
	cout << "\n\n" << left << setw(10) << "Flight Id"<<right<<"|";
	cout << left << setw(12) << "Flight Name" << right << "|";
	cout << left << setw(20) << "Departure Airport" << right << "|";
	cout << left << setw(17) << "Arrival Airport" << right << "|";
	cout << left << setw(16) << "Departure Time" << right << "|";
	cout << left << setw(13) << "Arrival Time" << right << "|";
	cout << left << setw(20) << "No of Seats-Economy" << right << "|";
	cout << left << setw(23) << "No of Seats-Firstclass" << right << "|";
	cout << left << setw(16) << "Economy Price" << right << "|";
	cout << left << setw(11) << "FC Price" << right << "|";

	// Make a GET call to server to fetch all flight details
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/flightDetails/";
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);	

	// Displaying all flight details on console
	cout << endl << endl;
	int num_rows = pairs_vector.size();
	for (int rownum = 0; rownum < num_rows; ++rownum)
	{
			available_options.push_back(stoi(pairs_vector[rownum].at("flightid")));
			cout << left << setw(10) << pairs_vector[rownum].at("flightid") << right << "|";
			cout<< left<<setw(12)<<pairs_vector[rownum].at("flightName")<< right << "|";
			cout << left << setw(20) << pairs_vector[rownum].at("departureAirport") <<right << "|";
			cout << left << setw(17) << pairs_vector[rownum].at("arrivalAirport") << right<<"|";
			hours = pairs_vector[rownum].at("departureTimeHours");
			cout<< left << setw(16)<< hours + ":" + pairs_vector[rownum].at("departureTimeMinutes") <<right << "|";
			hours = pairs_vector[rownum].at("arrivalTimeHours");
			cout << left << setw(13) << hours + ":" + pairs_vector[rownum].at("arrivalTimeMinutes") << right << "|";
			cout << left << setw(20) << pairs_vector[rownum].at("seatingCapacityEconomy") <<right << "|";
			cout << left << setw(23) << pairs_vector[rownum].at("seatingCapacityFirstclass") << right << "|";
			cout << left<<"$"<<left << setw(15) << pairs_vector[rownum].at("priceEconomy") << right << "|";
			cout << left << "$" << left << setw(10) << pairs_vector[rownum].at("priceFirstclass") << right << "|";
				
		cout << endl<<endl;
	}
}

/**********************************************************/
// Name: delete_flight
// Description: Delete user specidied flight from database.
//				Make DEL call to server after fetching input from user.
/**********************************************************/
void Admin::delete_flight() {

	// Local variable decarations
	string str;
	int fltID;

	// Display all flight details on console
	display_all_flights();

	if (!available_options.empty()) {
		// Fetch and validate flight id
		while (1) {
			cout << "\n\n\tEnter the Flight Id: ";
			getline(cin, str);
			if (!validate_int(str)) {
				cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
				system("pause");
				continue;
			}
			// Validation for flight id from available options only
			if (find(available_options.begin(), available_options.end(), stoi(str)) == available_options.end()) {
				cout << "\n\n\t\t\t Please enter the flight id from available options\n\n\t\t\t ";
				system("pause");
				continue;
			}
			fltID = stoi(str);
			break;
		}

		// Make a DEL call to server for flight deletion
		auto nullvalue = json::value::null();
		string uri = "http://localhost:80/deleteFlight/" + to_string(fltID);
		Requester obj(uri);
		obj.make_request(methods::DEL, nullvalue);

		cout << "\n\n\t\t\t Flight deleted.\n\n\t\t\t ";
		system("pause");
	}
	else
	{
		cout << "\n\n\t\t\t No Flight present in database.\n\n\t\t\t ";
		system("pause");
	}
}