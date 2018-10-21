// Including header files
#pragma once
#include "GetBookings.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: MakeBooking
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
GetBookings::GetBookings(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&GetBookings::handle_get, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_get
// Description: Handles the GET request and sends appropriate response
/**********************************************************/
void GetBookings::handle_get(http_request request)
{
	TRACE(L"\nhandle GET\n");

	// Extract user id from uri
	string str = to_utf8string(request.request_uri().to_string());
	size_t found = str.find_last_of("/");
	string userid = str.substr(found + 1);

	// Fire query to database
	PostgresHelper pghelper;
	pqxx::result R = pghelper.get_bookings(userid);

	// Send response as json array
	vector<json::value> arrBookings;
	int num_rows = R.size();
	for (int rownum = 0; rownum < num_rows; ++rownum) {
		web::json::value booking;
		booking[L"flightName"] = json::value::string(to_utf16string(R[rownum][0].c_str()));
		booking[L"departureAirport"] = json::value::string(to_utf16string(R[rownum][1].c_str()));
		booking[L"arrivalAirport"] = json::value::string(to_utf16string(R[rownum][2].c_str()));
		booking[L"departureTimeHours"] = json::value::string(to_utf16string(R[rownum][3].c_str()));
		booking[L"departureTimeMinutes"] = json::value::string(to_utf16string(R[rownum][4].c_str()));
		booking[L"arrivalTimeHours"] = json::value::string(to_utf16string(R[rownum][5].c_str()));
		booking[L"arrivalTimeMinutes"] = json::value::string(to_utf16string(R[rownum][6].c_str()));
		booking[L"priceEconomy"] = json::value::string(to_utf16string(R[rownum][7].c_str()));
		booking[L"priceFirstclass"] = json::value::string(to_utf16string(R[rownum][8].c_str()));
		booking[L"flightid"] = json::value::string(to_utf16string(R[rownum][9].c_str()));
		booking[L"seatingCapacityEconomy"] = json::value::string(to_utf16string(R[rownum][10].c_str()));
		booking[L"seatingCapacityFirstclass"] = json::value::string(to_utf16string(R[rownum][11].c_str()));
		booking[L"userid"] = json::value::string(to_utf16string(R[rownum][12].c_str()));
		booking[L"seatNumber"] = json::value::string(to_utf16string(R[rownum][14].c_str()));
		booking[L"class"] = json::value::string(to_utf16string(R[rownum][15].c_str()));

		arrBookings.push_back(booking);
	}

	json::value answer;
	answer[L"Bookings"] = web::json::value::array(arrBookings);


	display_json(json::value::null(), L"R: ");
	display_json(answer, L"S: ");

	request.reply(status_codes::OK, answer);
};