// Including header files
#pragma once
#include"stdafx.h"
#include<chrono>
#include"PostgresConnector.h"
#include"Flight.h"
using namespace std::chrono;

// class PostgresHelper
class PostgresHelper {
private:
	PostgresConnector conn;		// Object of PostgresConnector class
	pqxx::result result;		// Stores the result of query
public:
	void create_account(string, string, string, string,string,string);	// Method to create account of user
	pqxx::result get_user_details(string);								// Method to get user details
	void create_flight(string, string, string, string, string, string, string, string, string, string, string);	// Method to create flight
	pqxx::result get_all_flight_details();								// Method to get all flight details
	pqxx::result get_seating_chart(string,string);						// Method to get seating chart
	pqxx::result get_flight_details_by_flightid(string);				// Method to get flight details by flight id
	void insert_timestamp(string,string,string,string,string);			// Method to create timestamp
	pqxx::result get_userid_from_timestamps(string,string,string);		// Method to get user id from timestamps table
	void make_booking(string,string,string,string);						// Method to make booking
	pqxx::result get_seat_occupancy(string, string, string);			// Method to get seat occupancy
	pqxx::result get_bookings(string);									// Method to get existing bookings
	pqxx::result get_flights_by_route(string,string);					// Method to get flights by route
	void delete_flight(string);											// Method to delete existing flight
};