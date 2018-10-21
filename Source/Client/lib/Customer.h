// Including header files
#pragma once
#include"User.h"

// class Customer derived from class User
class Customer: public User{
public:
	void create_account();						// Method for creating new account
	bool sign_in();								// Method for signing in to existing account
	void show_options();						// Method for displaying options for various tasks
	void book_ticket();							// Method for displaying options to book a new flight
	void book_economy(int);						// Method for booking a economy class ticket
	void book_firstclass(int);					// Method for booking a first class ticket
	void view_bookings();						// Method to display existing bookings
	void search_by_destination();				// Method for booking ticket by destinations
	void search_all_flights();					// Method for booking new ticket from all existing flights
	void display_all_flights();					// Method to display all flights
	void display_seat_chart(char,int);			// Method to display seating chart 
	void display_final_summary(char, int,int);	// Method to display final booking summary and book ticket
	bool check_seat_occupied(char, int, int);	// Method to check the seat occupancy
};