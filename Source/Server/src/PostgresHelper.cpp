// Including header files
#pragma once
#include "PostgresHelper.h"

/**********************************************************/
// Name: create_account
// Description: Fires query to create account
/**********************************************************/
void PostgresHelper::create_account(string name, string age, string username, string password,string email,string type)
{
	string query = "INSERT INTO Users(name, age, username, password, emailid,utype) VALUES('" + name + "'," + age + ",'" + username + "','" + password + "','" + email
		+ "','" + type + "')";
	conn.excecute_query(query);
}

/**********************************************************/
// Name: get_user_details
// Description: Fires query to get user details
/**********************************************************/
pqxx::result PostgresHelper::get_user_details(string username)
{
	string query = "SELECT * FROM Users WHERE username='" + username + "'";
	return conn.excecute_query(query);
}

/**********************************************************/
// Name: create_flight
// Description: Fires query to create flight
/**********************************************************/
void PostgresHelper::create_flight(string fltname,string depairport,string arrairport,string dephr,string depmin,string arrhr,string arrmin,string seateco,string seatfc,string priceeco,string pricefc)
{
	string query = "INSERT INTO Flights(flight_name, departure_airport,arrival_airport,departure_Time_hours, \
		departure_Time_minutes,arrival_Time_hours,arrival_Time_minutes,seating_capacity_economy,seating_capacity_firstclass,economy_price, \
		firstclass_price) VALUES('" + fltname + "','" + depairport + "','" + \
		arrairport + "'," + dephr + "," + depmin + "," \
		+ arrhr + "," + arrmin + "," + seateco \
		+ "," + seatfc + "," + priceeco + "," + pricefc + ")";
	conn.excecute_query(query);

	query = "SELECT flightid FROM Flights ORDER BY flightid DESC LIMIT 1";
	pqxx::result R = conn.excecute_query(query);
	string fltID = R[0][0].c_str();
	string tableName = "Flight_" + fltID;
	query = "CREATE TABLE " + tableName + "(seat_number INT,status VARCHAR(1),class VARCHAR(1))";
	conn.excecute_query(query);

	query = "INSERT INTO " + tableName + "(seat_number,status,class) VALUES ";
	for (int i = 1; i < stoi(seateco); i++) {
		query += "(" + to_string(i) + ",'O','E'),";
	}
	query += "(" + seateco + ",'O','E')";
	conn.excecute_query(query);

	query = "INSERT INTO " + tableName + "(seat_number,status,class) VALUES ";
	for (int i = 1; i < stoi(seatfc); i++) {
		query += "(" + to_string(i) + ",'O','F'),";
	}
	query += "(" + seatfc + ",'O','F')";
	conn.excecute_query(query);
}

/**********************************************************/
// Name: get_all_flight_details
// Description: Fires query to get all flight details
/**********************************************************/
pqxx::result PostgresHelper::get_all_flight_details()
{
	string query = "SELECT * FROM Flights";
	return conn.excecute_query(query);
}

/**********************************************************/
// Name: get_seating_chart
// Description: Fires query to get seating chart
/**********************************************************/
pqxx::result PostgresHelper::get_seating_chart(string fltID,string type)
{
	string tableName = "Flight_" + fltID;
	string query = "SELECT seat_number,status FROM " + tableName + " WHERE class='" + type + "' ORDER BY seat_number";
	return conn.excecute_query(query);
}

/**********************************************************/
// Name: get_flight_details_by_flightid
// Description: Fires query to get flight details by flight id
/**********************************************************/
pqxx::result PostgresHelper::get_flight_details_by_flightid(string fltID)
{
	string query = "SELECT * FROM Flights WHERE flightid=" + fltID;
	return conn.excecute_query(query);
	
}

/**********************************************************/
// Name: insert_timestamp
// Description: Fires query to create timestamp
/**********************************************************/
void PostgresHelper::insert_timestamp(string ms,string userId,string seatNum,string fltID,string type)
{
	string query = "INSERT INTO Timestamps (timestamp,userid,flightid,seat_number,class) VALUES(" + ms + "," + userId + "," + fltID + "," + seatNum + ",'" + type + "')";
	conn.excecute_query(query);
}

/**********************************************************/
// Name: get_userid_from_timestamps
// Description: Fires query to get userid from timestamps table
/**********************************************************/
pqxx::result PostgresHelper::get_userid_from_timestamps(string fltID,string type,string seatNum)
{
	string query = "SELECT userid FROM Timestamps WHERE flightid=" + fltID + " AND seat_number=" + seatNum + "AND class='"+type+ + "' ORDER BY timestamp LIMIT 1";
	return conn.excecute_query(query);
}

/**********************************************************/
// Name: make_booking
// Description: Fires query to make booking
/**********************************************************/
void PostgresHelper::make_booking(string userId, string fltID, string type, string seatNum)
{
	string query = "UPDATE Flight_" + fltID + " SET status='X' WHERE seat_number=" + seatNum + " AND class='" + type + "'";
	conn.excecute_query(query);
	query = "INSERT INTO Bookings(userid,flightid,seat_number,class) VALUES(" + userId + "," + fltID + "," + seatNum + ",'" + type + "')";
	conn.excecute_query(query);
	query = "DELETE FROM Timestamps WHERE seat_number=" + seatNum + " AND flightid=" + fltID + " AND userid="+ userId + " AND class = '" + type + "'";
	conn.excecute_query(query);
}

/**********************************************************/
// Name: get_seat_occupancy
// Description: Fires query to get seat occupancy status
/**********************************************************/
pqxx::result PostgresHelper::get_seat_occupancy(string fltID, string type, string seatNum)
{
	string query = "SELECT status FROM Flight_" + fltID + " WHERE seat_number=" + seatNum + " AND class='" + type + "'";
	return conn.excecute_query(query);
}

/**********************************************************/
// Name: get_bookings
// Description: Fires query to get existing bookings
/**********************************************************/
pqxx::result PostgresHelper::get_bookings(string userId)
{
	string query = "SELECT Flights.*,Bookings.* FROM Flights INNER JOIN Bookings ON Flights.flightid=Bookings.flightid WHERE Bookings.userid=" + userId;
	return conn.excecute_query(query);
}

/**********************************************************/
// Name: get_flights_by_route
// Description: Fires query to get all flight between two places
/**********************************************************/
pqxx::result PostgresHelper::get_flights_by_route(string depAirport,string arrAirport)
{
	string query = "SELECT * FROM Flights WHERE departure_airport='" + depAirport + "' AND arrival_airport='" + arrAirport + "'";
	PostgresConnector conn;
	return conn.excecute_query(query);
}

/**********************************************************/
// Name: delete_flight
// Description: Fires query to delete existing flight
/**********************************************************/
void PostgresHelper::delete_flight(string fltID)
{
	string query = "DELETE FROM Flights WHERE flightid=" + fltID;
	PostgresConnector conn;
	conn.excecute_query(query);

	query = "DELETE FROM Bookings WHERE flightid=" + fltID;
	conn.excecute_query(query);
}
