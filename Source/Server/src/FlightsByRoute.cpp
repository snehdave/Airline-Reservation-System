// Including header files
#pragma once
#include "FlightsByRoute.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: MakeBooking
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
FlightsByRoute::FlightsByRoute(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&FlightsByRoute::handle_get, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_get
// Description: Handles the GET request and sends appropriate response
/**********************************************************/
void FlightsByRoute::handle_get(http_request request)
{
	TRACE(L"\nhandle GET\n");

	// Extract arrival airport from uri
	string str = to_utf8string(request.request_uri().to_string());
	size_t found = str.find_last_of("-");
	string tempstr = str.substr(1, found-1);
	string destination = convert_airport_name(str.substr(found + 1));

	// Extract departure airport from uri
	found = tempstr.find_last_of("/");
	string source = convert_airport_name(tempstr.substr(found + 1));

	// Fire query to database
	PostgresHelper pghelper;
	pqxx::result R = pghelper.get_flights_by_route(source,destination);

	// Send response as json array
	if (R.size() > 0) {
		vector<json::value> arrFlights;
		int num_rows = R.size();
		for (int rownum = 0; rownum < num_rows; ++rownum) {
			web::json::value flight;
			flight[L"flightName"] = json::value::string(to_utf16string(R[rownum][0].c_str()));
			flight[L"departureAirport"] = json::value::string(to_utf16string(R[rownum][1].c_str()));
			flight[L"arrivalAirport"] = json::value::string(to_utf16string(R[rownum][2].c_str()));
			flight[L"departureTimeHours"] = json::value::string(to_utf16string(R[rownum][3].c_str()));
			flight[L"departureTimeMinutes"] = json::value::string(to_utf16string(R[rownum][4].c_str()));
			flight[L"arrivalTimeHours"] = json::value::string(to_utf16string(R[rownum][5].c_str()));
			flight[L"arrivalTimeMinutes"] = json::value::string(to_utf16string(R[rownum][6].c_str()));
			flight[L"priceEconomy"] = json::value::string(to_utf16string(R[rownum][7].c_str()));
			flight[L"priceFirstclass"] = json::value::string(to_utf16string(R[rownum][8].c_str()));
			flight[L"flightid"] = json::value::string(to_utf16string(R[rownum][9].c_str()));
			flight[L"seatingCapacityEconomy"] = json::value::string(to_utf16string(R[rownum][10].c_str()));
			flight[L"seatingCapacityFirstclass"] = json::value::string(to_utf16string(R[rownum][11].c_str()));

			arrFlights.push_back(flight);
		}

		json::value answer;
		answer[L"Flights"] = web::json::value::array(arrFlights);


		display_json(json::value::null(), L"R: ");
		display_json(answer, L"S: ");

		request.reply(status_codes::OK, answer);
	}
	else
	{
		request.reply(status_codes::NoContent, json::value::null());
	}
};

/**********************************************************/
// Name: convert_airport_name
// Description: Replace underscore by space in given string
/**********************************************************/
string FlightsByRoute::convert_airport_name(string str) {
	string result;
	size_t n = std::count(str.begin(), str.end(), '_');

	if (n == 0)
		return str;

	size_t found;
	for (int i = 0; i < n; i++) {
		found = str.find("_");
		result += str.substr(0, found) + " ";
		str = str.substr(found + 1);
	}
	result += str;
	return result;
}