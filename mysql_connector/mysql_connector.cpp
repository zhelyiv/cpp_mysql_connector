// mysql_connector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mysql_connector.h"

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
using namespace std;
/*
Include directly the different
headers from cppconn/ and mysql_driver.h + mysql_util.h
(and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;


string server = "tcp://127.0.0.1:3306";
string username = "root";
string password = "csu123"; // 

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: change error code to suit your needs
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
			//try 
			//{
			//	sql::Driver *driver;
			//	sql::Connection *con;
			//	sql::Statement *stmt;
			//	sql::ResultSet *res;
			//
			//	/* Create a connection */
			//	driver = get_driver_instance();
			//	con = driver->connect("tcp://127.0.0.1:3306", "root", "csu123");
			//	/* Connect to the MySQL test database */
			//	con->setSchema("adibe_db");
			//
			//	stmt = con->createStatement();
			//	res = stmt->executeQuery("select idAdibe_FileType, name from adibe_filetype");
			//	if (res)
			//	{
			//		while (res->next())
			//		{
			//			cout << "id: " << res->getInt(0);
			//			cout << " status: " << res->getString(1);
			//		}
			//	}
			//	delete res;
			//	delete stmt;
			//	delete con;
			//
			//}
			//catch (sql::SQLException &e) 
			//{
			//	cout << "# ERR: SQLException in " << __FILE__;
			//	cout << "(" << __FUNCTION__ << ") on line "  
			//		<< __LINE__ << endl;
			//	cout << "# ERR: " << e.what();
			//	cout << " (MySQL error code: " << e.getErrorCode();
			//	cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			//}

			sql::Driver     *driver; // MySQL Driver Object
			sql::Connection *connection; // MySQL connection Object
			sql::Statement  *statement;   // Statement which holds SQL commands
			sql::ResultSet  *resultSet;    // ResultSet to hold the results
										   //Here is the connection
			try
			{
				driver = get_driver_instance();
				connection = driver->connect("tcp://127.0.0.1:3306", "root", "uuuu");
				//driver = get_driver_instance();
				//connection = driver->connect(server, username, password);
				statement = connection->createStatement();
				statement->execute("USE adibe_db");

				
				//resultSet = statement->executeQuery("show tables");
				 
				resultSet = statement->executeQuery("CALL testproc(10)");
				while (resultSet->next()) 
				{
					// Iterating the result set
					sql::SQLString str = resultSet->getString(1);
					cout << str.c_str() << endl;
				}
			}
			catch (sql::SQLException e)
			{
				cout << "Error message: " << e.what() << endl;
				system("pause");
				exit(1);
			}

			//Clear resources
			delete resultSet;
			delete statement;
			delete connection;

			system("pause");
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

	char c;
	cin >> c;
    return nRetCode;
}
