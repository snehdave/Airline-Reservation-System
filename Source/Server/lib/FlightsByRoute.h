// Including header files
#pragma once
#include"PostgresHelper.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

// class FlightsByRoute
class FlightsByRoute
{
public:
	FlightsByRoute() {}											// Default constructor
	FlightsByRoute(utility::string_t url);						// Parameterised constructor to start listening at given uri
	string convert_airport_name(string);						// Method for converting incoming airport names from client

	pplx::task<void> open() { return m_listener.open(); }		// Method to open the listner
	pplx::task<void> close() { return m_listener.close(); }		// Method to close the listner

private:

	void handle_get(http_request);		// Method to handle GET call

	http_listener m_listener;			// Object of http_listner
};
