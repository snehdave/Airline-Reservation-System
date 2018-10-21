// Including header files
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace utility::conversions;
using namespace std;

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#else
# include <sys/time.h>
#endif

#define TRACE(msg)            wcout << msg
#define TRACE_ACTION(a, k, v) wcout << a << L" (" << k << L", " << v << L")\n"

// Global Function declarations
string slice(string str);				// Method to remove first and last character from string

void display_json(						// Method to display json object as string
	json::value const & jvalue,
	utility::string_t const & prefix);

void handle_request(http_request request,		
	function<void(json::value const &, json::value &)> action);		// Method to handle request from client


