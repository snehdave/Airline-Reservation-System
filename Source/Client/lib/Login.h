// Including header files
#pragma once
#include"stdafx.h"
#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

// class Login
class Login{
public:
	void display_title();			// Method to display title of the application
	void display_menu();			// Method to display main menu
	void user_create_account();		// Method to display options of account type for creating a new account
	void user_sign_in();			// Method to display options of account type for signing in to existing account
};
