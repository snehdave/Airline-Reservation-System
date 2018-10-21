#include "Flight.h"

string Flight::get_flightName()
{
	return flightName;
}

string Flight::get_departureAirport()
{
	return departureAirport;
}

string Flight::get_arrivalAirport()
{
	return arrivalAirport;
}

Time Flight::get_departureTime()
{
	return departureTime;
}

Time Flight::get_arrivalTime()
{
	return arrivalTime;
}

int Flight::get_seatingCapacityEconomy()
{
	return seatingCapacityEconomy;
}

int Flight::get_seatingCapacityFirstClass()
{
	return seatingCapacityFirstClass;
}

double Flight::get_economyPrice()
{
	return economyPrice;
}

double Flight::get_firstclassPrice()
{
	return firstclassPrice;
}

void Flight::set_flightName(string str)
{
	flightName = str;
}

void Flight::set_departureAirport(string str)
{
	departureAirport = str;
}

void Flight::set_arrivalAirport(string str)
{
	arrivalAirport = str;
}

void Flight::set_departureTime(Time t)
{
	departureTime.hours = t.hours;
	departureTime.minutes = t.minutes;
}

void Flight::set_arrivalTime(Time t)
{
	arrivalTime.hours = t.hours;
	arrivalTime.minutes = t.minutes;
}

void Flight::set_seatingCapacityEconomy(int n)
{
	seatingCapacityEconomy = n;
}

void Flight::set_seatingCapacityFirstClass(int n)
{
	seatingCapacityFirstClass = n;
}

void Flight::set_economyPrice(double price)
{
	economyPrice = price;
}

void Flight::set_firstclassPrice(double price)
{
	firstclassPrice = price;
}
