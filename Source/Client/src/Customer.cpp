// Including header files
#pragma once
#include"Customer.h"
#include"Requester.h"

// Declaring extern global variables
extern map<string, string> pairs;
extern vector<map<string, string>> pairs_vector;
extern vector<int> available_options;
extern bool all_occupied;
extern bool user_exists;

/**********************************************************/
// Name: create_account
// Description: To fetch login details from user. If input details
//				are valid then create payload and send POST request to
//				server for creating new account.
/**********************************************************/
void Customer::create_account() {

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
		body[5] = json::value::string(L"C");

		// Sending request to the server for account creation
		auto nullvalue = json::value::null();
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
bool Customer::sign_in() {

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
		if (pairs.at("password") == tmpPasswd && pairs.at("utype") == "C") {
			userId = stoi(pairs.at("userid"));
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
	else
	{
		user_exists = 1;
		cout << "\n\t\t\tUsername doesn't exist. Please enter correct username.\n\t\t\t";
		system("pause");
		return 0;
	}
}

/**********************************************************/
// Name: show_options
// Description: Displays options for booking a new flight, 
//				view existing bookings
/**********************************************************/
void Customer::show_options() {

	// Local variables declaration
	bool contFlag = 0;
	int choice;
	string str;

	// do-while loop to display options until back button is pressed
	do {

		// Clearing screen 
		system("cls");

		// Displaying options to the user
		cout << "\n\n\n\n\n\t\t\t****************************";
		cout << "\n\t\t\tCUSTOMER OPTIONS:";
		cout << "\n\t\t\t1. Book a New Flight";
		cout << "\n\t\t\t2. View Existing Bookings";
		cout << "\n\t\t\t3. Back";
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
			// Function call to book a new ticket
			book_ticket();
			break;
		}
		case 2: {
			// Function call to view existing bookings
			view_bookings();
			break;
		}
		case 3: {
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
// Name: book_ticket
// Description: Display options to book a new ticket by searhing
//				all flights or searching flights by to and from destinations
/**********************************************************/
void Customer::book_ticket()
{

	// Local variable declarations
	bool contFlag = 0;
	int choice;
	string str;

	// do-while loop to display options until back button is pressed
	do {

		// Clearing screen 
		system("cls");

		// Displaying options to the user
		cout << "\n\n\n\n\n\t\t\t****************************";
		cout << "\n\t\t\tBOOK A NEW TICKET OPTIONS:";
		cout << "\n\t\t\t1. Search By All Flights";
		cout << "\n\t\t\t2. Search By To and From Destination";
		cout << "\n\t\t\t3. Back";
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
			// Function call to book ticket by searching all flights
			search_all_flights();
			contFlag = 1;
			break;
		}
		case 2: {
			// Function call to book ticket by searching to and from destinations
			search_by_destination();
			contFlag = 1;
			break;
		}
		case 3: {
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
// Name: display_seat_chart
// Description: Takes input as flight id and class type.
//				Makes a GET call to server to fetch seat information.
//				Display them in console
/**********************************************************/
void Customer::display_seat_chart(char type, int fltID) {

	// Clearing available_options vector
	available_options.clear();

	// Make a GET call to server to fetch seat information
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/seatingChart/" + to_string(fltID) + "/" + type;
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);

	// Check if received any info from server
	if (!pairs.empty()) {

		// Clearing screen
		system("cls");

		cout << "\n*********************";
		cout << "\n SEATING ARRANGEMENT:";
		cout << "\n*********************";
		cout << "\n\n O - Open";
		cout << "\n X - Reserved";
		cout << "\n\n---------------------------------------";
		cout << endl;

		// Displaying seat information on console in rows of 6 seats
		int num_rows = pairs.size();
		int rownum1 = 1, rownum2 = 1, colnum;
		while (rownum1 <= num_rows&&rownum2 <= num_rows)
		{
			colnum = 1;
			for (int j = 0; j < 6 && rownum1 <= num_rows; j++)
			{

				// Validation for any open seat
				if (pairs.at(to_string(rownum1)) == "O") {
					all_occupied = 0;
				}

				cout << left << setw(5) << pairs.at(to_string(rownum1)) << right << "|";
				rownum1++;
			}
			cout << endl;
			colnum = 0;
			for (int j = 0; j < 6 && rownum2 <= num_rows; j++)
			{

				// Inserting seatnumbers in available_options vector
				available_options.push_back(rownum2);

				cout << left << setw(5) << rownum2 << right << "|";
				rownum2++;
			}
			cout << "\n---------------------------------------";
			cout << endl;
		}
	}
	else {
		cout << "\n\n\t\t\t All seats occupied. Please try again.\n\n\t\t\t ";
		system("pause");
	}
}

/**********************************************************/
// Name: display_final_summary
// Description: Last step of the booking process. Displays final booking summary.
//				Confirming final decision of the user to book the ticket. Validates
//				from database if this user is first to make confirmation. Validates
//				seat occupancy again before final booking.
/**********************************************************/
void Customer::display_final_summary(char type, int fltID, int seatNum)
{

	// Local variable declarations
	int choice;
	bool contFlag = 0;
	string hours, str;

	// Making a GET call to server to fetch flight information
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/flightDetails/" + to_string(fltID);
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);

	// Clearing screen
	system("cls");

	// Displaying final booking summary
	cout << "\n************************";
	cout << "\n FINAL BOOKING SUMMARY:";
	cout << "\n************************";
	cout << "\n\n" << left << setw(20) << "Flight Id" << right << "|";
	cout << left << setw(17) << "Flight Name" << right << "|";
	cout << left << setw(20) << "Departure Airport" << right << "|";
	cout << left << setw(20) << "Arrival Airport" << right << "|";
	cout << left << setw(20) << "Departure Time" << right << "|";
	cout << left << setw(20) << "Arrival Time" << right << "|";
	cout << left << setw(12) << "Class" << right << "|";
	cout << left << setw(20) << "Seat Number" << right << "|";
	cout << left << setw(9) << "Price" << right << "|";
	cout << endl;
	cout << left << setw(20) << pairs.at("flightid") << right << "|";
	cout << left << setw(17) << pairs.at("flightName") << right << "|";
	cout << left << setw(20) << pairs.at("departureAirport") << right << "|";
	cout << left << setw(20) << pairs.at("arrivalAirport") << right << "|";
	hours = pairs.at("departureTimeHours");
	cout << left << setw(20) << hours + ":" + pairs.at("departureTimeMinutes") << right << "|";
	hours = pairs.at("arrivalTimeHours");
	cout << left << setw(20) << hours + ":" + pairs.at("arrivalTimeMinutes") << right << "|";
	if (type == 'E') {
		cout << left << setw(12) << "Economy" << right << "|";
		cout << left << setw(20) << seatNum << right << "|";
		cout << left << "$" << left << setw(8) << pairs.at("priceEconomy") << right << "|";
	}
	else {
		cout << left << setw(12) << "Firstclass" << right << "|";
		cout << left << setw(20) << seatNum << right << "|";
		cout << left << "$" << left << setw(8) << pairs.at("priceFirstclass") << right << "|";
	}

	// do-while loop to continuous display options to user
	do {

		// Displaying options to user
		cout << "\n\n\n\n\n\t\t\t****************************";
		cout << "\n\t\t\tCONFIRM FINAL BOOKING:";
		cout << "\n\t\t\t1. Yes";
		cout << "\n\t\t\t2. No";
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

		// Get timestamp of confirmation
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch());

		// If user confirms YES
		if (choice == 1) {

			// Display timestamp information
			cout << "\n\n\t\t\t Timestamp of confirmation: " << ms.count();

			// Checking seat occupancy before final booking
			cout << "\n\n\t\t\t Checking Final Occupancy...";

			// Creating payload json object
			auto body = json::value::array();
			body[0] = json::value::string(to_utf16string(to_string(ms.count())));
			body[1] = json::value::string(to_utf16string(to_string(userId)));
			body[2] = json::value::string(to_utf16string(to_string(fltID)));
			body[3] = json::value::string(to_utf16string(to_string(seatNum)));
			string temp;
			temp.push_back(type);
			body[4] = json::value::string(to_utf16string(temp));

			// Making a POST call to server to create timestamp for the user
			string uri = "http://localhost:80/createTimestamp/";
			Requester obj(uri);
			obj.make_request(methods::POST, body);

			// Wait for the database to get synchronised
			Sleep(2000);

			// Making a GET call to server to fetch user id with first timestamp
			auto nullvalue = json::value::null();
			uri = "http://localhost:80/getUseridFromTimestamps/" + to_string(fltID) + "/" + type + "/" + to_string(seatNum);
			Requester obj1(uri);
			obj1.make_request(methods::GET, nullvalue);

			// Check if  fetched user id matches the current user
			if (userId == stoi(pairs.at("userid"))) {

				// Check if seat is available 
				if (check_seat_occupied(type, fltID, seatNum)) {
					cout << "\n\n\t\t\t Seat Available";

					// Creating payload json object
					auto body = json::value::array();
					body[0] = json::value::string(to_utf16string(to_string(userId)));
					body[1] = json::value::string(to_utf16string(to_string(fltID)));
					string temp;
					temp.push_back(type);
					body[2] = json::value::string(to_utf16string(temp));
					body[3] = json::value::string(to_utf16string(to_string(seatNum)));

					// Making POST call to server to make final booking
					string uri = "http://localhost:80/makeBooking/";
					Requester obj(uri);
					obj.make_request(methods::POST, body);

					cout << "\n\n\t\t\t Booking Done!\n\n\t\t\t ";
				}
			}
			else {
				cout << "\n\t\t\t Seat Occupied! Please try again.\n\n\t\t\t ";
			}
			contFlag = 1;
			system("pause");
		}

		// Go back if user enters NO
		else if (choice == 2) {
			contFlag = 1;
			system("pause");
		}

		// Error message for invalid user input
		else {
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
		}
	} while (contFlag == 0);
}

/**********************************************************/
// Name: check_seat_occupied
// Description: To check if seat is open or reserved. Makes a GET call
//				to server to fetch status of the seat. Retuens 1 if  seat is open and
//				returns 0 if seat is reserved.
/**********************************************************/
bool Customer::check_seat_occupied(char type, int fltID, int seatNum)
{

	// Making GET call to server to fetch seat status
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/getSeatOccupancy/" + to_string(fltID) + "/" + type + "/" + to_string(seatNum);
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);

	// Check if seat is open
	if (pairs.at("status") == "O") {
		return 1;
	}
	else {
		return 0;
	}
}

/**********************************************************/
// Name: book_economy
// Description: To do process of booking for economy class
/**********************************************************/
void Customer::book_economy(int fltID)
{
	// Local variable declarations
	int seatNum;
	string str;

	// Display seating chart on console
	display_seat_chart('E', fltID);

	// Check if all seats are occupied
	if (!all_occupied) {

		// Fetch and validate seat number
		while (1) {
			cout << "\n\n\tEnter seat number: ";
			getline(cin, str);
			if (!validate_int(str)) {
				cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
				system("pause");
				continue;
			}
			// Validation for seatnumber from available options
			if (find(available_options.begin(), available_options.end(), stoi(str)) == available_options.end()) {
				cout << "\n\n\t\t\t Please enter the seat number from available options\n\n\t\t\t ";
				system("pause");
				continue;
			}
			seatNum = stoi(str);
			break;
		}

		// Check seat occupancy
		if (check_seat_occupied('E', fltID, seatNum)) {
			cout << "\n\t Seat Available!\n\n";
			system("pause");

			// Do final booking steps
			display_final_summary('E', fltID, seatNum);
		}
		else {
			cout << "\n\t Seat Occupied! Please try again.";
			system("pause");
		}
	}
	else
	{
		all_occupied = 1;
		cout << "\n\t All seats occupied! Please try again.\n\t ";
		system("pause");
	}
}

/**********************************************************/
// Name: book_firstclass
// Description: To do process of booking for economy class
/**********************************************************/
void Customer::book_firstclass(int fltID)
{
	// Local variable declarations
	int seatNum;
	string str;

	// Display seating chart on console
	display_seat_chart('F', fltID);

	// Check if all seats are occupied
	if (!all_occupied) {

		// Fetch and validate seat number
		while (1) {
			cout << "\n\n\tEnter seat number: ";
			getline(cin, str);
			if (!validate_int(str)) {
				cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
				system("pause");
				continue;
			}
			// Validation for seatnumber from available options
			if (find(available_options.begin(), available_options.end(), stoi(str)) == available_options.end()) {
				cout << "\n\n\t\t\t Please enter the seat number from available options\n\n\t\t\t ";
				system("pause");
				continue;
			}
			seatNum = stoi(str);
			break;
		}

		// Check seat occupancy
		if (check_seat_occupied('F', fltID, seatNum)) {
			cout << "\n\t Seat Available!\n\n";
			system("pause");

			// Do final booking steps
			display_final_summary('F', fltID, seatNum);
		}
		else {
			cout << "\n\t Seat Occupied! Please try again.";
			system("pause");
		}
	}
	else
	{
		all_occupied = 1;
		cout << "\n\t All seats occupied! Please try again.\n\t ";
		system("pause");
	}
}

/**********************************************************/
// Name: view_bookings
// Description: Display all existing bookings of the customer.
//				Makes a GET call to server to fetch all bookings and display them.
/**********************************************************/
void Customer::view_bookings()
{
	// Local variable declarations
	string hours;

	// Making a GET call to server to fetch bookings information
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/getBookings/" + to_string(userId);
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);

	// Clearing screen
	system("cls");

	// Display all bookings summary
	cout << "\n*********************";
	cout << "\n ALL BOOKING SUMMARY:";
	cout << "\n*********************";
	cout << "\n\n" << left << setw(20) << "Flight Id" << right << "|";
	cout << left << setw(17) << "Flight Name" << right << "|";
	cout << left << setw(20) << "Departure Airport" << right << "|";
	cout << left << setw(20) << "Arrival Airport" << right << "|";
	cout << left << setw(20) << "Departure Time" << right << "|";
	cout << left << setw(20) << "Arrival Time" << right << "|";
	cout << left << setw(12) << "Class" << right << "|";
	cout << left << setw(20) << "Seat Number" << right << "|";
	cout << left << setw(9) << "Price" << right << "|";
	cout << endl;
	int num_rows = pairs_vector.size();
	for (int rownum = 0; rownum < num_rows; ++rownum)
	{
		cout << left << setw(20) << pairs_vector[rownum].at("flightid") << right << "|";
		cout << left << setw(17) << pairs_vector[rownum].at("flightName") << right << "|";
		cout << left << setw(20) << pairs_vector[rownum].at("departureAirport") << right << "|";
		cout << left << setw(20) << pairs_vector[rownum].at("arrivalAirport") << right << "|";
		hours = pairs_vector[rownum].at("departureTimeHours");
		cout << left << setw(20) << hours + ":" + pairs_vector[rownum].at("departureTimeMinutes") << right << "|";
		hours = pairs_vector[rownum].at("arrivalTimeHours");
		cout << left << setw(20) << hours + ":" + pairs_vector[rownum].at("arrivalTimeMinutes") << right << "|";
		if (pairs_vector[rownum].at("class") == "E") {
			cout << left << setw(12) << "Economy" << right << "|";
			cout << left << setw(20) << pairs_vector[rownum].at("seatNumber") << right << "|";
			cout << left << "$" << left << setw(8) << pairs.at("priceEconomy") << right << "|";
		}
		else {
			cout << left << setw(12) << "Firstclass" << right << "|";
			cout << left << setw(20) << pairs_vector[rownum].at("seatNumber") << right << "|";
			cout << left << "$" << left << setw(8) << pairs.at("priceFirstclass") << right << "|";
		}
		cout << endl;
	}
	system("pause");
}

/**********************************************************/
// Name: search_by_destination
// Description: To book a new ticket by searching by to and from destination.
//				Fetches departure and arrival airport from user and makes a
//				GET call to server to fetch all routes between two places.
//				Fetches flight id  and class type from the user and do futher steps.
/**********************************************************/
void Customer::search_by_destination() {

	//Clearing available_options vector
	available_options.clear();

	// Local varible declarations
	int fltID, choice;
	bool contFlag = 0;
	string hours, depAirport, arrAirport, str,temp;

	// Clearing screen
	system("cls");

	cout << "\n\n\t\t\t***********************************";
	cout << "\n\t\t\t SEARCH BY TO AND FROM DESTINATION:";
	cout << "\n\t\t\t***********************************";

	// Fetch and validate departure airport
	while (1) {
		cout << "\n\n\t\t\tEnter Departure Airport: ";
		getline(cin, str);
		if (!validate_alphastring(str)) {
			cout << "\n\t\t\t Please enter only alphabetic input.";
			continue;
		}
		temp = str;
		depAirport = convert_airport_name(str);
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
		if (temp == str) {
			cout << "\n\t\t\t Arrival Airport cannot be same as Departure airport.";
			continue;
		}
		arrAirport = convert_airport_name(str);
		break;
	}

	// Making a GET call to server to fetch all flights between two places
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/getFlightsByRoute/" + depAirport + "-" + arrAirport;
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);

	// Check if any flight exists between two places
	if (!pairs_vector.empty()) {

		// Clearing screen
		system("cls");

		// Display all available flight details
		cout << "\n*********************";
		cout << "\n ALL FLIGHT DETAILS:";
		cout << "\n*********************";
		cout << "\n\n" << left << setw(20) << "Flight Id" << right << "|";
		cout << left << setw(20) << "Flight Name" << right << "|";
		cout << left << setw(20) << "Departure Airport" << right << "|";
		cout << left << setw(20) << "Arrival Airport" << right << "|";
		cout << left << setw(20) << "Departure Time" << right << "|";
		cout << left << setw(20) << "Arrival Time" << right << "|";
		cout << endl << endl;
		int num_rows = pairs_vector.size();
		for (int rownum = 0; rownum < num_rows; ++rownum)
		{
			available_options.push_back(stoi(pairs_vector[rownum].at("flightid")));
			cout << left << setw(20) << pairs_vector[rownum].at("flightid") << right << "|";
			cout << left << setw(20) << pairs_vector[rownum].at("flightName") << right << "|";
			cout << left << setw(20) << pairs_vector[rownum].at("departureAirport") << right << "|";
			cout << left << setw(20) << pairs_vector[rownum].at("arrivalAirport") << right << "|";
			hours = pairs_vector[rownum].at("departureTimeHours");
			cout << left << setw(20) << hours + ":" + pairs_vector[rownum].at("departureTimeMinutes") << right << "|";
			hours = pairs_vector[rownum].at("arrivalTimeHours");
			cout << left << setw(20) << hours + ":" + pairs_vector[rownum].at("arrivalTimeMinutes") << right << "|";
			cout << endl << endl;
		}

		// Fetch and validate flight id
		while (1) {
			cout << "\n\n\tEnter the Flight Id: ";
			getline(cin, str);
			if (!validate_int(str)) {
				cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
				system("pause");
				continue;
			}
			// Validation for flight id from available options
			if (find(available_options.begin(), available_options.end(), stoi(str)) == available_options.end()) {
				cout << "\n\n\t\t\t Please enter the flight id from available options\n\n\t\t\t ";
				system("pause");
				continue;
			}
			fltID = stoi(str);
			break;
		}

		// Making GET call to server to fetch info for selected flight
		uri = "http://localhost:80/flightDetails/" + to_string(fltID);
		Requester obj1(uri);
		obj1.make_request(methods::GET, nullvalue);

		// Clearing screen
		system("cls");

		// Display flight information
		cout << "\n\n*********************";
		cout << "\n FLIGHT DETAILS:";
		cout << "\n*********************";
		cout << "\n\n" << left << setw(20) << "Flight Id" << right << "|";
		cout << left << setw(20) << "Flight Name" << right << "|";
		cout << left << setw(20) << "Departure Airport" << right << "|";
		cout << left << setw(20) << "Arrival Airport" << right << "|";
		cout << left << setw(20) << "Departure Time" << right << "|";
		cout << left << setw(20) << "Arrival Time" << right << "|";
		cout << endl;
		cout << left << setw(20) << pairs.at("flightid") << right << "|";
		cout << left << setw(20) << pairs.at("flightName") << right << "|";
		cout << left << setw(20) << pairs.at("departureAirport") << right << "|";
		cout << left << setw(20) << pairs.at("arrivalAirport") << right << "|";
		hours = pairs.at("departureTimeHours");
		cout << left << setw(20) << hours + ":" + pairs.at("departureTimeMinutes") << right << "|";
		hours = pairs.at("arrivalTimeHours");
		cout << left << setw(20) << hours + ":" + pairs.at("arrivalTimeMinutes") << right << "|";

		// do-while loop to continuously display options to user
		do {

			// Displaying options
			cout << "\n\n\n\n\n\t\t\t****************************";
			cout << "\n\t\t\tCHOOSE THE TICKET TYPE:";
			cout << "\n\t\t\t1. Economy Class: $" << pairs.at("priceEconomy");
			cout << "\n\t\t\t2. First Class: $" << pairs.at("priceFirstclass");
			cout << "\n\t\t\t3. Back";
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
				// Function call to book economy class
				book_economy(fltID);
				contFlag = 1;
				break;
			}
			case 2: {
				// Function call to book first class
				book_firstclass(fltID);
				contFlag = 1;
				break;
			}
			case 3: {
				// Go back to previous menu
				contFlag = 1;
				break;
			}
			default: {
				// Error message for invalied user input
				cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
				system("pause");
			}
			}
		} while (contFlag == 0);
	}
	else {
		cout << "\n\n\t\t\t No Flights exist between source and destination\n\n\t\t\t ";
		system("pause");
	}
}

/**********************************************************/
// Name: search_all_flights
// Description: To do booking from all existing flights.
//				Fetches flight id  and class type from the user and do futher steps.
/**********************************************************/
void Customer::search_all_flights()
{

	// Local variable declarations
	int fltID, choice;
	bool contFlag = 0;
	string hours, str;

	// Display all flight info
	display_all_flights();

	// Fetch and validate flight id 
	while (1) {
		cout << "\n\n\tEnter the Flight Id: ";
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
			continue;
		}
		// Validation for flight id from available options
		if (find(available_options.begin(), available_options.end(), stoi(str)) == available_options.end()) {
			cout << "\n\n\t\t\t Please enter the flight id from available options\n\n\t\t\t ";
			system("pause");
			continue;
		}
		fltID = stoi(str);
		break;
	}

	// Making a GET call to server to fetch flight info
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/flightDetails/" + to_string(fltID);
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);
	
	// Clearing screen
	system("cls");

	// Display flight info
	cout << "\n*********************";
	cout << "\n FLIGHT DETAILS:";
	cout << "\n*********************";
	cout << "\n\n" << left << setw(20) << "Flight Id" << right << "|";
	cout << left << setw(20) << "Flight Name" << right << "|";
	cout << left << setw(20) << "Departure Airport" << right << "|";
	cout << left << setw(20) << "Arrival Airport" << right << "|";
	cout << left << setw(20) << "Departure Time" << right << "|";
	cout << left << setw(20) << "Arrival Time" << right << "|";
	cout << endl;
	cout << left << setw(20) << pairs.at("flightid") << right << "|";
	cout << left << setw(20) << pairs.at("flightName") << right << "|";
	cout << left << setw(20) << pairs.at("departureAirport") << right << "|";
	cout << left << setw(20) << pairs.at("arrivalAirport") << right << "|";
	hours = pairs.at("departureTimeHours");
	cout << left << setw(20) << hours + ":" + pairs.at("departureTimeMinutes") << right << "|";
	hours = pairs.at("arrivalTimeHours");
	cout << left << setw(20) << hours + ":" + pairs.at("arrivalTimeMinutes") << right << "|";

	// do-while loop to display options to user
	do {
		cout << "\n\n\n\n\n\t\t\t****************************";
		cout << "\n\t\t\tCHOOSE THE TICKET TYPE:";
		cout << "\n\t\t\t1. Economy Class: $" << pairs.at("priceEconomy");
		cout << "\n\t\t\t2. First Class: $" << pairs.at("priceFirstclass");
		cout << "\n\t\t\t3. Back";
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

		// switch-case structure for various options
		switch (choice) {
		case 1: {
			// Function call to book economy class
			book_economy(fltID);
			contFlag = 1;
			break;
		}
		case 2: {
			// Function call to book first class
			book_firstclass(fltID);
			contFlag = 1;
			break;
		}
		case 3: {
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
// Name: display_all_flights
// Description: Display all flights information on console
/**********************************************************/
void Customer::display_all_flights() {

	// Clearing available options vector
	available_options.clear();

	// Local variables declarations
	string hours;

	// Make GET to server to fetch all flight details
	auto nullvalue = json::value::null();
	string uri = "http://localhost:80/flightDetails/";
	Requester obj(uri);
	obj.make_request(methods::GET, nullvalue);

	// Clearing screen
	system("cls");

	// Display flights info
	cout << "\n*********************";
	cout << "\n ALL FLIGHT DETAILS:";
	cout << "\n*********************";
	cout << "\n\n" << left << setw(20) << "Flight Id" << right << "|";
	cout << left << setw(20) << "Flight Name" << right << "|";
	cout << left << setw(20) << "Departure Airport" << right << "|";
	cout << left << setw(20) << "Arrival Airport" << right << "|";
	cout << left << setw(20) << "Departure Time" << right << "|";
	cout << left << setw(20) << "Arrival Time" << right << "|";
	cout << endl << endl;

	int num_rows = pairs_vector.size();
	for (int rownum = 0; rownum < num_rows; ++rownum)
	{

		// Insert flight id in avialable_options vector
		available_options.push_back(stoi(pairs_vector[rownum].at("flightid")));

		cout << left << setw(20) << pairs_vector[rownum].at("flightid") << right << "|";
		cout << left << setw(20) << pairs_vector[rownum].at("flightName") << right << "|";
		cout << left << setw(20) << pairs_vector[rownum].at("departureAirport") << right << "|";
		cout << left << setw(20) << pairs_vector[rownum].at("arrivalAirport") << right << "|";
		hours = pairs_vector[rownum].at("departureTimeHours");
		cout << left << setw(20) << hours + ":" + pairs_vector[rownum].at("departureTimeMinutes") << right << "|";
		hours = pairs_vector[rownum].at("arrivalTimeHours");
		cout << left << setw(20) << hours + ":" + pairs_vector[rownum].at("arrivalTimeMinutes") << right << "|";
		cout << endl << endl;
	}
}