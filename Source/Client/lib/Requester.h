// Including header files
#pragma once
#include"stdafx.h"

// class Requester
class Requester {
private:
	http_client client;								// http_client object to make request to server
public:
	//map<string, string> pairs;
	Requester(string);								// Constructor to initialize the http_client object with request uri
	pplx::task<http_response> make_task_request(	// Method for handling tasks of making request
		http_client & client,
		method mtd,
		json::value const & jvalue);

	void make_request(								// Method for making requests to the server
		method mtd,
		json::value const & jvalue);

};