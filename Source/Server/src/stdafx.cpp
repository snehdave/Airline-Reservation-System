// Including header files
#pragma once
#include"stdafx.h"

/**********************************************************/
// Name: slice
// Description: Removes first and last character from string 
/**********************************************************/
string slice(string str) {
	return str.substr(1, str.size() - 2);
}

/**********************************************************/
// Name: display_json
// Description: Displays json as string on console
/**********************************************************/
void display_json(
	json::value const & jvalue,
	utility::string_t const & prefix)
{
	wcout << prefix << jvalue.serialize() << endl;
}

/**********************************************************/
// Name: handle_request
// Description: Handles various request from client
/**********************************************************/
void handle_request(http_request request,
	function<void(json::value const &, json::value &)> action)
{
	auto answer = json::value::object();

	request
		.extract_json()
		.then([&answer, &action](pplx::task<json::value> task) {
		try
		{
			auto const & jvalue = task.get();
			display_json(jvalue, L"R: ");
			if (!jvalue.is_null())
			{
				action(jvalue, answer);
			}
		}
		catch (http_exception const & e)
		{
			wcout << e.what() << endl;
		}
	})
		.wait();

	display_json(answer, L"S: ");

	request.reply(status_codes::OK, answer);
}
