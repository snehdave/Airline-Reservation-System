// Including header files
#include "PostgresConnector.h"

/**********************************************************/
// Name: PostgresConnector
// Description: Initialize database parameters 
/**********************************************************/
PostgresConnector::PostgresConnector()
{
	host = "airline.cs12px0ojkiu.us-east-2.rds.amazonaws.com"; 
	port = 5432;
	dbname = "airline_system";
	user = "snehdave94";
	password = "sneh1234";
}

/**********************************************************/
// Name: excecute_query
// Description: Executes the given query and returns the result
/**********************************************************/
pqxx::result PostgresConnector::excecute_query(string str) {
	try {
		string connectionString = "host = '" + host + "' port ='" + to_string(port) + "' dbname ='" + dbname + "' user ='" + user+"' password ='" + password + "'";
		pqxx::connection C(connectionString);
		cout << "Connection Successful" << endl;
		cout << "Connected to " << C.dbname() << endl;
		pqxx::work W(C);
		cout << "Executing Query: " << str << endl;
		pqxx::result R = W.exec(str);
		W.commit();
		return R;
	}
	catch (const exception &e) {
		cerr << e.what() << endl;
	}
}