// Including header files
#pragma once
#include "CreateAccount.h"
#include "UserDetails.h"
#include "CreateFlight.h"
#include "FlightDetails.h"
#include"SeatingChart.h"
#include"CreateTimestamp.h"
#include"TimestampsUserid.h"
#include"MakeBooking.h"
#include"SeatOccupancy.h"
#include"GetBookings.h"
#include"FlightsByRoute.h"
#include"DeleteFlight.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<CreateAccount> g_http_createaccount;
std::unique_ptr<UserDetails> g_http_userdetails;
std::unique_ptr<CreateFlight> g_http_createflight;
std::unique_ptr<FlightDetails> g_http_flightdetails;
std::unique_ptr<SeatingChart> g_http_seatingchart;
std::unique_ptr<CreateTimestamp> g_http_createtimestamp;
std::unique_ptr<TimestampsUserid> g_http_timestampuserid;
std::unique_ptr<MakeBooking> g_http_makebooking;
std::unique_ptr<SeatOccupancy> g_http_seatoccupancy;
std::unique_ptr<GetBookings> g_http_getbookings;
std::unique_ptr<FlightsByRoute> g_http_flightsbyroute;
std::unique_ptr<DeleteFlight> g_http_deleteflight;

/**********************************************************/
// Name: on_initialize
// Description: Initialize all the constructors with uri on start of application
/**********************************************************/
void on_initialize(const string_t& address)
{
    // Build our listener's URI from the configured address and the hard-coded path "CreateAccount/Action"

	wstring addr = address + L"createAccount/";
	g_http_createaccount = std::unique_ptr<CreateAccount>(new CreateAccount(addr));
	g_http_createaccount->open().wait();
    
    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"userDetails/";
	g_http_userdetails = std::unique_ptr<UserDetails>(new UserDetails(addr));
	g_http_userdetails->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"createFlight/";
	g_http_createflight = std::unique_ptr<CreateFlight>(new CreateFlight(addr));
	g_http_createflight->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"flightDetails/";
	g_http_flightdetails = std::unique_ptr<FlightDetails>(new FlightDetails(addr));
	g_http_flightdetails->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"seatingChart/";
	g_http_seatingchart = std::unique_ptr<SeatingChart>(new SeatingChart(addr));
	g_http_seatingchart->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();


	addr = address + L"createTimestamp/";
	g_http_createtimestamp = std::unique_ptr<CreateTimestamp>(new CreateTimestamp(addr));
	g_http_createtimestamp->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"getUseridFromTimestamps/";
	g_http_timestampuserid = std::unique_ptr<TimestampsUserid>(new TimestampsUserid(addr));
	g_http_timestampuserid->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"makeBooking/";
	g_http_makebooking = std::unique_ptr<MakeBooking>(new MakeBooking(addr));
	g_http_makebooking->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"getSeatOccupancy/";
	g_http_seatoccupancy = std::unique_ptr<SeatOccupancy>(new SeatOccupancy(addr));
	g_http_seatoccupancy->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"getBookings/";
	g_http_getbookings = std::unique_ptr<GetBookings>(new GetBookings(addr));
	g_http_getbookings->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"getFlightsByRoute/";
	g_http_flightsbyroute = std::unique_ptr<FlightsByRoute>(new FlightsByRoute(addr));
	g_http_flightsbyroute->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

	addr = address + L"deleteFlight/";
	g_http_deleteflight = std::unique_ptr<DeleteFlight>(new DeleteFlight(addr));
	g_http_deleteflight->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
	addr.empty();

    return;
}

/**********************************************************/
// Name: on_shutdown
// Description: Wait for all the process to complete before exiting the application
/**********************************************************/
void on_shutdown()
{
	g_http_createaccount->close().wait();
	g_http_userdetails->close().wait();
	g_http_createflight->close().wait();
	g_http_flightdetails->close().wait();
	g_http_seatingchart->close().wait();
	g_http_createtimestamp->close().wait();
	g_http_timestampuserid->close().wait();
	g_http_makebooking->close().wait();
	g_http_seatoccupancy->close().wait();
	g_http_getbookings->close().wait();
	g_http_flightsbyroute->close().wait();
    return;
}

/**********************************************************/
// Name: wmain
// Description: Start point of application
/**********************************************************/
int wmain(int argc, wchar_t *argv[])
{
    utility::string_t address = U("http://localhost:80/");

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}