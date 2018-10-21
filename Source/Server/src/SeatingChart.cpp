// Including header files
#pragma once
#include "SeatingChart.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: SeatingChart
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
SeatingChart::SeatingChart(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&SeatingChart::handle_get, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_get
// Description: Handles the GET request and sends appropriate response
/**********************************************************/
void SeatingChart::handle_get(http_request request)
{
	TRACE(L"\nhandle GET\n");

	//Extract flight id from URI
	string str = to_utf8string(request.request_uri().to_string());
	size_t found = str.find_last_of("/");
	string tempstr = str.substr(0, found);

	// Extract class typr from uri
	string type = str.substr(found + 1);
	found = tempstr.find_last_of("/");
	string fltID = tempstr.substr(found + 1);

	// Fire query to database
	PostgresHelper pghelper;
	pqxx::result R = pghelper.get_seating_chart(fltID, type);

	// Send response as json object
	auto answer = json::value::object();

	int num_rows = R.size();
	for (int rownum = 0; rownum < num_rows; ++rownum) {
		wstring seatnum = to_string_t(R[rownum][0].c_str());
		answer[seatnum] = json::value::string(to_utf16string(R[rownum][1].c_str()));
	}

	display_json(json::value::null(), L"R: ");
	display_json(answer, L"S: ");

	request.reply(status_codes::OK, answer);
};