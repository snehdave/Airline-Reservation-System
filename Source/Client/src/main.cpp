// Including header files
#include "Login.h"
#include"stdafx.h"
#include"Requester.h"

// Global variable declarations
#ifndef GLOBALS
#define GLOBALS
map<string, string> pairs;
vector<map<string, string>> pairs_vector;
vector<int> available_options;
bool all_occupied = 1;
bool user_exists = 1;
bool server_started = 0;
#endif

/**********************************************************/
// Name: main
// Description: Starting point of the application. Displays title and main menu to user.
/**********************************************************/
int main() {

	// Adjust the console size on startup
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 1500, 500, TRUE); // 1500 width, 500 height

	Login login;

	// Display title
	login.display_title();

	Sleep(2000);

	// Display main menu
	login.display_menu();
	return 0;
}