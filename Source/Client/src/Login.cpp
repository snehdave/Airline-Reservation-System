#pragma once
#include"Login.h"
#include"Admin.h"
#include"Customer.h"


/**********************************************************/
// Name: display_title
// Description: To display the title at start up of the application
/**********************************************************/
void Login::display_title() {
	cout << "\n\n\n\n\n\t\t\t****************************";
	cout<<"\n\t\t\tAIRLINE RESERVATION SYSTEM";
	cout<<"\n\t\t\tMADE BY: SNEH DAVE";
	cout << "\n\t\t\t****************************";
}


/**********************************************************/
// Name: display_menu
// Description: To display the main menu to the user. It provides
//				options for Creating new account or Sign in to existing
//				account or to exit the application.
/**********************************************************/
void Login::display_menu() {
	
	// Local Variable declarations
	bool contFlag=0;
	int choice;
	string str;

	// do-while loop for displaying options continuously until exit option is selected
	do{
		// Clearing screen
		system("cls");

		// Displaying options to the console
		cout << "\n\n\n\n\n\t\t\t****************************";
		cout << "\n\t\t\tLOGIN:";
		cout << "\n\n\t\t\t1. Create Account";
		cout << "\n\t\t\t2. Sign in";
		cout << "\n\t\t\t3. Exit";
		cout << "\n\t\t\t****************************";
		cout << "\n\n\t\t\t Enter your choice: ";

		// Fetching user input and validating it
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
			continue;
		}
		choice = stoi(str);

		// switch-case structure for handling different options
		switch (choice) {
		case 1: {
			// Function call for creating new account
			user_create_account();
			break;
		}
		case 2: {
			// Function call for sign in to existing account
			user_sign_in(); 
			break;
		}
		case 3: {
			// Exit the application
			contFlag = 1;
			break;
		}
		default: {
			// Error message for any other integer inputs
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
		}
		}
	} while (contFlag==0);
}


/**********************************************************/
// Name: user_create_account
// Description: To display options to user to choose the account
//				type - Administartor or Customer for creating
//				new account.
/**********************************************************/
void Login::user_create_account() {

	// Local variable decarations
	bool contFlag = 0;
	int choice;
	string str;

	// do-while loop for displaying options continuously until exit option is selected
	do{
		// Clearing screen
		system("cls");

		// Displaying options to user to choose account type
		cout << "\n\n\n\n\n\t\t\t****************************";
		cout << "\n\t\t\tCREATE ACCOUNT";
		cout << "\n\n\n\t\t\tCHOOSE ACCOUNT TYPE:";
		cout << "\n\n\t\t\t1. Administrator";
		cout << "\n\t\t\t2. Customer";
		cout << "\n\t\t\t3. Back";
		cout << "\n\t\t\t****************************";
		cout << "\n\n\t\t\t Enter your choice: ";

		// Fetching user input and validating it
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
			continue;
		}
		choice = stoi(str);

		// switch-case structure to handle different options
		switch (choice) {
		case 1: {
			// Function call to create new account as Administrator
			User *adn = new Admin();
			adn->create_account();
		    contFlag = 1;
			break;
		}
		case 2: {
			// Function call to create new account as Customer
			User *cust = new Customer();
			cust->create_account();
			contFlag = 1;
			break;
		}
		case 3: {
			// Go back to main menu
			contFlag = 1;
			break;
		}
		default:
			// Error message for any other user input
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
		}
	} while (contFlag==0);
}


/**********************************************************/
// Name: user_sign_in
// Description: To display options to user to choose the account
//				type - Administartor or Customer for signing
//				in to existing account.
/**********************************************************/
void Login::user_sign_in() {

	// Local variable decarations
	bool contFlag = 0;
	int choice;
	string str;

	// do-while loop for displaying options continuously until exit option is selected
	do {
		// Clearing screen
		system("cls");

		// Displaying options to user to choose account type
		cout << "\n\n\n\n\n\t\t\t****************************";
		cout << "\n\t\t\tSIGN IN";
		cout << "\n\n\n\t\t\tCHOOSE ACCOUNT TYPE:";
		cout << "\n\n\t\t\t1. Administrator";
		cout << "\n\t\t\t2. Customer";
		cout << "\n\t\t\t3. Back";
		cout << "\n\t\t\t****************************";
		cout << "\n\n\t\t\t Enter your choice: ";

		// Fetching user input and validating it
		getline(cin, str);
		if (!validate_int(str)) {
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
			continue;
		}
		choice = stoi(str);

		// switch-case structure to handle different options
		switch (choice) {
		case 1: {
			// Function call to sign in as Administrator
			User *adn = new Admin();
			if(adn->sign_in())
				adn->show_options();
			break;
		}
		case 2: {
			// Function call to sign in as Customer
			User *cust = new Customer();
			if(cust->sign_in())
				cust->show_options();
			break;
		}
		case 3: {
			// Go back to main menu
			contFlag = 1;
			break;
		}
		default:
			// Error message for any other integer inputs
			cout << "\n\n\t\t\t Please enter the correct choice\n\n\t\t\t ";
			system("pause");
		}
	} while (contFlag == 0);
}