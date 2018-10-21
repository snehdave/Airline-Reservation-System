// Including header files
#pragma once
#include"Requester.h"

// Declaring extern global variables
extern bool user_exists;
extern bool server_started;
extern vector<map<string, string>> pairs_vector;

/**********************************************************/
// Name: Requester
// Description: Parameterised constructor for Requestor class. Initializes 
//				http_client object with given uri
/**********************************************************/
Requester::Requester(string url):client(to_utf16string(url)) {

}

/**********************************************************/
// Name: make_task_request
// Description: Handles the task created by make_request function
/**********************************************************/
pplx::task<http_response> Requester::make_task_request(
	http_client & client,
	method mtd,
	json::value const & jvalue)
{
	return (mtd == methods::GET || mtd == methods::HEAD) ?
		client.request(mtd, L"/") :
		client.request(mtd, L"/", jvalue);
}

/**********************************************************/
// Name: make_request
// Description: Takes method type and json object as input.
//				Creates task to make request to server and waits for
//				the response from the server
/**********************************************************/
void Requester::make_request(
	method mtd,
	json::value const & jvalue)
{

	// Creates task to make request to server
	make_task_request(client, mtd, jvalue)
		.then([](http_response response)
	{
		server_started = 1;

		// If status code of response if OK then Extract json form response
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}

		// If status code of response if NotFound then unset user_exists flag
		if (response.status_code() == status_codes::NotFound)
		{
			user_exists = 0;
		}

		// If status code of response if NoContent then clear pairs_vector
		if (response.status_code() == status_codes::NoContent) {
			pairs_vector.clear();
		}
		return pplx::task_from_result(json::value());
	})
		.then([](pplx::task<json::value> previousTask)
	{
		try
		{
			// Extarct json from previous task
			auto jval = previousTask.get();

			// Check if Json contains Flights or Bookings array
			if (jval[L"Flights"].is_array() || jval[L"Bookings"].is_array()) {
				jsontopairvector(jval);
			}

			//display_json(previousTask.get(), L"R: ");

			// Convert json string to map
			stringtomap(to_utf8string(previousTask.get().serialize()));
		}
		catch (http_exception const & e)
		{
			wcout << "\n\n\t\t\t " <<e.what() << "\n\n\t\t\t " << endl;
			system("pause");
		}
	})
		.wait();
}
