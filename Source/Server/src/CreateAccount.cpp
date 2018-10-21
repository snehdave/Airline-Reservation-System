// Including header files
#pragma once
#include "CreateAccount.h"

using namespace std;
using namespace web; 
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

/**********************************************************/
// Name: MakeBooking
// Description: Initialize the http_listner object with uri and bind the methods with client call
/**********************************************************/
CreateAccount::CreateAccount(utility::string_t url) : m_listener(url)
{
    m_listener.support(methods::POST, std::bind(&CreateAccount::handle_post, this, std::placeholders::_1));
   
}

/**********************************************************/
// Name: handle_post
// Description: Handles the POST request and sends appropriate response
/**********************************************************/
void CreateAccount::handle_post(http_request request)
{
	TRACE("\nhandle POST\n");
	handle_request(
		request,
		[](json::value const & jvalue, json::value & answer)
	{
		// Extract json from body
		json::array e = jvalue.as_array();
		string name = slice(to_utf8string(e[0].to_string()));
		string age = slice(to_utf8string(e[1].to_string()));
		string username = slice(to_utf8string(e[2].to_string()));
		string password = slice(to_utf8string(e[3].to_string()));
		string emailid = slice(to_utf8string(e[4].to_string()));
		string type = slice(to_utf8string(e[5].to_string()));

		// Fire query to database
		PostgresHelper pghelper;
		pghelper.create_account(name, age, username, password, emailid, type);
	});
};