// Including header files
#pragma once
#include "SeatOccupancy.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: SeatOccupancy
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
SeatOccupancy::SeatOccupancy(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&SeatOccupancy::handle_get, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_get
// Description: Handles the GET request and sends appropriate response
/**********************************************************/
void SeatOccupancy::handle_get(http_request request)
{
	TRACE(L"\nhandle GET\n");

	// Extract seat number from uri
	string str = to_utf8string(request.request_uri().to_string());
	size_t found = str.find_last_of("/");
	string tempstr = str.substr(0, found);
	string seatnum = str.substr(found + 1);

	// Extract class type from uri
	found = tempstr.find_last_of("/");
	string tempstr2 = tempstr.substr(0, found);
	string type = tempstr.substr(found + 1);

	// Extract flight id from uri
	found = tempstr2.find_last_of("/");
	string fltID = tempstr2.substr(found + 1);

	// Fire query to database
	PostgresHelper pghelper;
	pqxx::result R = pghelper.get_seat_occupancy(fltID, type, seatnum);

	// Send response as json object
	auto answer = json::value::object();

	answer[L"status"] = json::value::string(to_utf16string(R[0][0].c_str()));

	display_json(json::value::null(), L"R: ");
	display_json(answer, L"S: ");

	request.reply(status_codes::OK, answer);
};