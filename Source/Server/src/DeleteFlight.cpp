// Including header files
#pragma once
#include "DeleteFlight.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: MakeBooking
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
DeleteFlight::DeleteFlight(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::DEL, std::bind(&DeleteFlight::handle_delete, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_get
// Description: Handles the GET request and sends appropriate response
/**********************************************************/
void DeleteFlight::handle_delete(http_request request)
{
	TRACE(L"\nhandle DELETE\n");

	//Extract flight id from URI
	string str = to_utf8string(request.request_uri().to_string());
	size_t found = str.find_last_of("/");
	string fltID = str.substr(found + 1);
	
	// Fire query to database
	PostgresHelper pghelper;
	pghelper.delete_flight(fltID);

	// Send response as json object
	display_json(json::value::null(), L"R: ");
	display_json(json::value::null(), L"S: ");

	request.reply(status_codes::OK, json::value::null());
};