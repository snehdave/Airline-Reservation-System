// Including header files
#include <iostream>
#include <string>
#include <pqxx/pqxx>
using namespace std;

// class PostgresConnector
class PostgresConnector {
private:
	string host;		// Host name of database
	int port;			// Port number of database
	string dbname;		// Database name
	string user;		// Username of database
	string password;	// Password of database
public:
	PostgresConnector();					// Constructor to initialize all database parameters
	pqxx::result excecute_query(string);	// Method to execute query
};