#include "amalgam\sqlite3.h"

#include <iostream>

int sqlite_callback(void*, int, char**, char**); //Callback for sqlite3_exec

int main()
{
	sqlite3* db;
	
	if(sqlite3_open("test.db", &db) == SQLITE_OK)
	{
		std::cout << "Database opened!" << std::endl;
		
		char *createTableSql = "CREATE TABLE IF NOT EXISTS PERSON(ID INTEGER PRIMARY KEY, NAME VARCHAR(20) NOT NULL, SURNAME VARCHAR(20) NOT NULL, AGE INTEGER)";
		
		char *error = NULL;
		
		if(sqlite3_exec(db, createTableSql, sqlite_callback, NULL, &error) != SQLITE_OK)
		{
			std::cout << "Could not execute the CREATE TABLE statement!" << std::endl;
			std::cout << "Sqlite Error: " << error << std::endl;
		}
		
		char *insertTableSql = "INSERT INTO PERSON VALUES(1, 'Mario', 'Rossi', 42)," \
							   "(2, 'Giuseppe', 'Verdi', 87),"\
							   "(3, 'Roberto', 'Gialli', 23),"\
							   "(4, 'Maria', 'Bianchi', 32),"\
							   "(5, 'Carla', 'Neri', 54);";
		
		if(sqlite3_exec(db, insertTableSql, sqlite_callback, NULL, &error) != SQLITE_OK)
		{
			std::cout << "Could not execute the INSERT statements!" << std::endl;
			std::cout << "Sqlite Error: " << error << std::endl;
		}
		
		char *selectAvgEtaSql = "SELECT AVG(AGE) FROM PERSON";
		
		if(sqlite3_exec(db, selectAvgEtaSql, sqlite_callback, NULL, &error) != SQLITE_OK)
		{
			std::cout << "Could not execute the SELECT statement!" << std::endl;
			std::cout << "Sqlite Error: " << error << std::endl;
		}
		
	} else {
		std::cout << "Failed to open the database!" << std::endl;
	}
	
	std::cout << "Closing the database." << std::endl;
	sqlite3_close(db);
	
	return 0;
}

int sqlite_callback(void* firstArg, int resultColumns, char** rowData, char** columnsHeaders) {
	int i = 0;
	while(i < resultColumns) {
		
		std::cout << columnsHeaders[i] << "|";
		i++;
	}
	
	std::cout << std::endl;
	
	i = 0;
	while(i < resultColumns) {
		
		if(rowData[i])
			std::cout << rowData[i] << "|";
		else
			std::cout << "NULL|";
		
		i++;
	}
	
	std::cout << std::endl;
	
	return 0;
}