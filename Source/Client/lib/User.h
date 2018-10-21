// Including header files
#pragma once
#include"stdafx.h"
#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<chrono>
using namespace std;
using namespace std::chrono;

// class User
class User{
public:
	string username;					// stores username
	string password;					// stores password
	string name;						// stores name of the user
	string emailid;						// stores emailid of the user
	int age;							// stores age of the user
	int userId;							// stores user id
	bool login_details();				// Method for inputing login details while creating new account
	virtual void create_account()=0;	// Pure virtual function for creating new account
	virtual bool sign_in()=0;			// Pure virtual function for signing in to existing account
	virtual void show_options() = 0;	// Pure virtual function for showing various options
	string fetch_password(string);		// Method for fetching password from the console
}; 
