// Including header files
#pragma once
#include"User.h"

// class Admin derived from class User
class Admin:public User {
public:
	void create_account();		// Method for creating new account
	bool sign_in();				// Method for signing in to existing account
	void show_options();		// Method for displaying options for various tasks
	void create_flight();		// Method for creating new flight
	void delete_flight();		// Method for deleting existing flight
	void display_all_flights(); // Method to display existing flights
};