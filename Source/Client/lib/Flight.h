#pragma once
#include<iostream>
using namespace std;

struct Time {
	int hours;
	int minutes;
};

class Flight {
private:
	string flightName;
	string departureAirport;
	string arrivalAirport;
	Time departureTime;
	Time arrivalTime;
	int seatingCapacityEconomy;
	int seatingCapacityFirstClass;
	double economyPrice;
	double firstclassPrice;
public:
	string get_flightName();
	string get_departureAirport();
	string get_arrivalAirport();
	Time get_departureTime();
	Time get_arrivalTime();
	int get_seatingCapacityEconomy();
	int get_seatingCapacityFirstClass();
	double get_economyPrice();
	double get_firstclassPrice();
	void set_flightName(string);
	void set_departureAirport(string);
	void set_arrivalAirport(string);
	void set_departureTime(Time);
	void set_arrivalTime(Time);
	void set_seatingCapacityEconomy(int);
	void set_seatingCapacityFirstClass(int);
	void set_economyPrice(double);
	void set_firstclassPrice(double);
};