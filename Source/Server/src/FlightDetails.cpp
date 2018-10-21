// Including header files
#pragma once
#include "FlightDetails.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: MakeBooking
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
FlightDetails::FlightDetails(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&FlightDetails::handle_get, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_get
// Description: Handles the GET request and sends appropriate response
/**********************************************************/
void FlightDetails::handle_get(http_request request)
{
	TRACE(L"\nhandle GET\n");
	
	// To get all flight details
	string str = to_utf8string(request.request_uri().to_string());
	if (str == "/flightDetails/" || str == "/flightDetails") {

		// Fire query to database
		PostgresHelper pghelper;
		pqxx::result R = pghelper.get_all_flight_details();

		// Send response as json array
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

	// To get flight details by flight id
	else {

		//Extract flight id from URI
		size_t found = str.find_last_of("/");
		string fltID = str.substr(found + 1);

		// Fire query to database
		PostgresHelper pghelper;
		pqxx::result R = pghelper.get_flight_details_by_flightid(fltID);

		// Send response as json object
		auto answer = json::value::object();

		answer[L"flightName"] = json::value::string(to_utf16string(R[0][0].c_str()));
		answer[L"departureAirport"] = json::value::string(to_utf16string(R[0][1].c_str()));
		answer[L"arrivalAirport"] = json::value::string(to_utf16string(R[0][2].c_str()));
		answer[L"departureTimeHours"] = json::value::string(to_utf16string(R[0][3].c_str()));
		answer[L"departureTimeMinutes"] = json::value::string(to_utf16string(R[0][4].c_str()));
		answer[L"arrivalTimeHours"] = json::value::string(to_utf16string(R[0][5].c_str()));
		answer[L"arrivalTimeMinutes"] = json::value::string(to_utf16string(R[0][6].c_str()));
		answer[L"priceEconomy"] = json::value::string(to_utf16string(R[0][7].c_str()));
		answer[L"priceFirstclass"] = json::value::string(to_utf16string(R[0][8].c_str()));
		answer[L"flightid"] = json::value::string(to_utf16string(R[0][9].c_str()));
		answer[L"seatingCapacityEconomy"] = json::value::string(to_utf16string(R[0][10].c_str()));
		answer[L"seatingCapacityFirstclass"] = json::value::string(to_utf16string(R[0][11].c_str()));

		display_json(json::value::null(), L"R: ");
		display_json(answer, L"S: ");

		request.reply(status_codes::OK, answer);
	}
};