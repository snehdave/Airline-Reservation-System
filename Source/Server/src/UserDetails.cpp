// Including header files
#pragma once
#include "UserDetails.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: UserDetails
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
UserDetails::UserDetails(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&UserDetails::handle_get, this, std::placeholders::_1));

}

/**********************************************************/
// Name: handle_get
// Description: Handles the GET request and sends appropriate response
/**********************************************************/
void UserDetails::handle_get(http_request request)
{
	TRACE(L"\nhandle GET\n");
	
		// Extract Username from URI
		string str = to_utf8string(request.request_uri().to_string());
		size_t found=str.find_last_of("/");
		string username=str.substr(found+1);
		
		// Fire query to database
		PostgresHelper pghelper;
		pqxx::result R=pghelper.get_user_details(username);

		// If user exists
		if (R.size() == 1) {

			// Send response as json object
			auto answer = json::value::object();

			answer[L"name"] = json::value::string(to_utf16string(R[0][0].c_str()));
			answer[L"age"] = json::value::string(to_utf16string(R[0][1].c_str()));
			answer[L"username"] = json::value::string(to_utf16string(R[0][2].c_str()));
			answer[L"password"] = json::value::string(to_utf16string(R[0][3].c_str()));
			answer[L"utype"] = json::value::string(to_utf16string(R[0][4].c_str()));
			answer[L"userid"] = json::value::string(to_utf16string(R[0][5].c_str()));
			answer[L"emailid"] = json::value::string(to_utf16string(R[0][6].c_str()));


			display_json(json::value::null(), L"R: ");
			display_json(answer, L"S: ");

			request.reply(status_codes::OK, answer);
		}
		else {
			auto nullvalue = json::value::null();
			request.reply(status_codes::NotFound, nullvalue);
		}
};