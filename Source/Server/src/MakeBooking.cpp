// Including header files
#pragma once
#include "MakeBooking.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: MakeBooking
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
MakeBooking::MakeBooking(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::POST, std::bind(&MakeBooking::handle_post, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_post
// Description: Handles the POST request and sends appropriate response
/**********************************************************/
void MakeBooking::handle_post(http_request request)
{
	TRACE("\nhandle POST\n");
	handle_request(
		request,
		[](json::value const & jvalue, json::value & answer)
	{
		json::array e = jvalue.as_array();
		string userid = slice(to_utf8string(e[0].to_string()));
		string fltID = slice(to_utf8string(e[1].to_string()));
		string type = slice(to_utf8string(e[2].to_string()));
		string seatnum = slice(to_utf8string(e[3].to_string()));

		// Fire query to database
		PostgresHelper pghelper;
		pghelper.make_booking(userid, fltID, type, seatnum);
	});
};