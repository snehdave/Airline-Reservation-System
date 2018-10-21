// Including header files
#pragma once
#include "CreateFlight.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: MakeBooking
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
CreateFlight::CreateFlight(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::POST, std::bind(&CreateFlight::handle_post, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_post
// Description: Handles the POST request and sends appropriate response
/**********************************************************/
void CreateFlight::handle_post(http_request request)
{
	TRACE("\nhandle POST\n");
	handle_request(
		request,
		[](json::value const & jvalue, json::value & answer)
	{
		// Extract json from body
		json::array e = jvalue.as_array();
		string fltname = slice(to_utf8string(e[0].to_string()));
		string depairport = slice(to_utf8string(e[1].to_string()));
		string arrairport = slice(to_utf8string(e[2].to_string()));
		string dephr = slice(to_utf8string(e[3].to_string()));
		string depmin = slice(to_utf8string(e[4].to_string()));
		string arrhr = slice(to_utf8string(e[5].to_string()));
		string arrmin = slice(to_utf8string(e[6].to_string()));
		string seateco = slice(to_utf8string(e[7].to_string()));
		string seatfc = slice(to_utf8string(e[8].to_string()));
		string priceeco = slice(to_utf8string(e[9].to_string()));
		string pricefc = slice(to_utf8string(e[10].to_string()));

		// Fire query to database
		PostgresHelper pghelper;
		pghelper.create_flight(fltname,depairport,arrairport,dephr,depmin,arrhr,arrmin,seateco,seatfc,priceeco,pricefc);
	});
};