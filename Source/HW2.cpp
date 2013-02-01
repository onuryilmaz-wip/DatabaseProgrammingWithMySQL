// Onur Yilmaz
 

// MYSQL, string and standard headers

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>


using namespace std;

// Creating MYSQL connections and pointers
MYSQL *connection, mysql;
MYSQL *connection2, mysql2;
MYSQL_RES *result;
MYSQL_ROW row;

// Variable for storing state of query
int query_state;


// Start of main function
int main()
{	
	// Flag and string for commands
	int flag=1;
	string command;
	
	// Initialization of MYSQL connection to the provided host and database
	mysql_init(&mysql);
	// connection = mysql_real_connect(&mysql,"localhost","root","root","deneme",0,0,0);
	// connection2 = mysql_real_connect(&mysql2,"localhost","root","root","deneme",0,0,0);
	connection = mysql_real_connect(&mysql,"144.122.71.133","e1627868","W4H7J;QP","phw2_e1627868",0,0,0);
	connection2 = mysql_real_connect(&mysql2,"144.122.71.133","e1627868","W4H7J;QP","phw2_e1627868",0,0,0);

	// If connections fail print out the error
	if (connection == NULL || connection2 == NULL) 
	{
		cout << mysql_error(&mysql) << endl;
	}
	
// Start of commands and operations
	while (flag)
	{

	// Read the command from standard input
	cin >> command;


	// ---------------
	// CREATE
	//----------------


	if (command == "create")
	{	

	// SQL Queries for creating tables
	string CreatePlayers = "CREATE TABLE Players (id INT, name CHAR(50), no INT, teamid INT, height FLOAT, weight FLOAT, age INT, PRIMARY KEY(id), FOREIGN KEY (teamid) REFERENCES teams(id))";
	char* CharCreatePlayers = &CreatePlayers[0];

	string CreateTeams = "CREATE TABLE Teams (id INT, name CHAR(50), conference CHAR(10), division CHAR(10), coachname CHAR(50), PRIMARY KEY (id))";
	char* CharCreateTeams = &CreateTeams[0];

	string CreatePlayed = "CREATE TABLE Played (playerid INT, teamid INT, no int, startseason CHAR(4), endseason CHAR(4),  FOREIGN KEY (playerid) REFERENCES Players(id))";
	char* CharCreatePlayed = &CreatePlayed[0];

	string CreateChampions = "CREATE TABLE Champions (season CHAR(4), teamid INT, PRIMARY KEY (season))";
	char* CharCreateChampions = &CreateChampions[0];	

	// Running SQL queries on the provided connection
	mysql_query(&mysql, CharCreateTeams );			
	mysql_query(&mysql, CharCreatePlayers);
 	mysql_query(&mysql, CharCreatePlayed );
	mysql_query(&mysql, CharCreateChampions);

	}


	// ---------------
	// INSERT  
	//----------------

	else if (command == "insert")
	{

	// Open connection to Teams text file		
	fstream TeamsTxtFile;
	TeamsTxtFile.open ("Teams.txt", ios::in | ios::out);
	TeamsTxtFile.seekg (0, ios::beg);

	// Until end of file
	while( TeamsTxtFile)
	{
		// Initialize strings
		string Complete = "";
		string temp = ""; 		

		// Read fields		
		getline(TeamsTxtFile, temp, '|');
		Complete = Complete + temp;
		for(int i=0;i<3;i++)
		{
			getline(TeamsTxtFile, temp, '|');
			Complete = Complete + ',' + '\''+ temp +'\'';
		}
		getline(TeamsTxtFile, temp, '\n');
		Complete = Complete + ',' + '\''+ temp +'\'';

		// Use strings for SQL queries
		// 12 is used because, to reach end of file, an empty line is read 
		// and it has only , and " with the length of 12			
		if( Complete.length() > 12)
		{
			Complete = "INSERT INTO Teams VALUES (" + Complete + ")";
			char* CharComplete = &Complete[0];
			mysql_query(&mysql, CharComplete );		
		}
	}

	// Open connection to Players text file		
	fstream PlayersTxtFile;
	PlayersTxtFile.open ("Players.txt", ios::in | ios::out);
	PlayersTxtFile.seekg (0, ios::beg);

	// Until end of file
	while( PlayersTxtFile)
	{
		// Initialize strings
		string CompletePlayers = "";
		string tempPlayers;	
		
		// Read fields		
		getline(PlayersTxtFile, tempPlayers, '|');
		CompletePlayers = CompletePlayers + tempPlayers;
		getline(PlayersTxtFile, tempPlayers, '|');
		CompletePlayers = CompletePlayers + ',' + '\''+ tempPlayers +'\'';
		for(int i=0;i<4;i++)
		{ 		
			getline(PlayersTxtFile, tempPlayers, '|');
			CompletePlayers = CompletePlayers + ','+ tempPlayers ;
		}
		getline(PlayersTxtFile, tempPlayers, '\n');
		CompletePlayers = CompletePlayers + ','+ tempPlayers ;
		
		// Use strings for SQL queries
		// 12 is used because, to reach end of file, an empty line is read 
		// and it has only , and " with the length of 8			
		if( CompletePlayers.length() > 8)
		{
			CompletePlayers = "INSERT INTO Players VALUES (" + CompletePlayers + ")";
			char* CharCompletePlayers2 = &CompletePlayers[0];
			mysql_query(&mysql2, CharCompletePlayers2);		
		} 
	}

	// Open connection to Champions text file		
	fstream ChampionsTxtFile;
	ChampionsTxtFile.open ("Champions.txt", ios::in | ios::out);
	ChampionsTxtFile.seekg (0, ios::beg);
	
	// Until end of file
	while( ChampionsTxtFile)
	{
		// Initialize strings
		string CompleteChampions = "";
		string tempChampions = ""; 		

		// Read fields
		getline(ChampionsTxtFile, tempChampions, '|');
		CompleteChampions = CompleteChampions  + '\''+ tempChampions + '\'';	
		getline(ChampionsTxtFile, tempChampions, '\n');
		CompleteChampions = CompleteChampions + ',' + tempChampions ;

		// Use strings for SQL queries
		// 12 is used because, to reach end of file, an empty line is read 
		// and it has only , and " with the length of 4				 
		if( CompleteChampions.length() > 4)
		{
			CompleteChampions = "INSERT INTO Champions VALUES (" + CompleteChampions + ")";
			char* CharCompleteChampions = &CompleteChampions[0];
			mysql_query(&mysql, CharCompleteChampions );		
		}
	}

	// Open connection to Played text file
	fstream PlayedTxtFile;
	PlayedTxtFile.open ("Played.txt", ios::in | ios::out);
	PlayedTxtFile.seekg (0, ios::beg);
		
	// Until end of file
	while( PlayedTxtFile)
	{
		// Initialize strings
		string CompletePlayed = "";
		string tempPlayed = ""; 		
	
		// Read fields
		getline(PlayedTxtFile, tempPlayed, '|');
		CompletePlayed = CompletePlayed  + tempPlayed;		
		for(int i=0;i<2;i++)
		{
			getline(PlayedTxtFile, tempPlayed, '|');
			CompletePlayed = CompletePlayed + ',' + tempPlayed;
		}
		getline(PlayedTxtFile, tempPlayed, '|');
		CompletePlayed = CompletePlayed + ',' + '\''+ tempPlayed +'\'';
		getline(PlayedTxtFile, tempPlayed, '\n');
		CompletePlayed = CompletePlayed + ',' + '\''+ tempPlayed +'\'';

		// Use strings for SQL queries
		// 12 is used because, to reach end of file, an empty line is read 
		// and it has only , and " with the length of 9	 
		if( CompletePlayed.length() > 9)
		{
			CompletePlayed = "INSERT INTO Played VALUES (" + CompletePlayed + ")";
			char* CharCompletePlayed = &CompletePlayed[0];
			mysql_query(&mysql2, CharCompletePlayed );		
		}
	}

	// End of insert command
	}

	// ---------------
	// DROP  
	//----------------

	else if (command == "drop")
	{
		// String of SQL query
		// Added for test purposes
		string DropAll = "DROP TABLES Champions, Played, Players,Teams,WorkedYear";
		char* CharDropAll = &DropAll[0];
		mysql_query(&mysql, CharDropAll);
	}


	// ---------------
	// QUERIES
	//----------------

	else if (command == "query")
{
	// Read the query number
	int commandNumber;
	cin >> commandNumber;


	// ---------------
	// QUERY #1
	//----------------

	if(commandNumber == 1 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL query
	string Query1 = "SELECT N.name FROM Teams N WHERE N.id IN (SELECT C.teamid FROM Champions C GROUP BY C.teamid HAVING COUNT(C.teamid) >= ALL ( SELECT COUNT(D.teamid) FROM Champions D GROUP BY D.teamid))";
	char* CharQuery1 = &Query1[0];
	
	// Run and store result
	mysql_query(&mysql, CharQuery1);
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
		cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
	
}	

	// ---------------
	// QUERY #2
	//----------------

	if(commandNumber == 2 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// Strings for SQL queries
	string Query21 = "CREATE TABLE WorkedYear AS (SELECT P.playerid, P.startseason, P.endseason FROM Played P)";
	char* CharQuery21 = &Query21[0];
	mysql_query(&mysql, CharQuery21);

	string Query22 = "UPDATE WorkedYear SET endseason = '2012' WHERE endseason = '0'";
	char* CharQuery22 = &Query22[0];
	mysql_query(&mysql, CharQuery22);

	string Query23 = "SELECT N.name FROM Players N WHERE N.id IN ( SELECT P.playerid  FROM WorkedYear P  GROUP BY P.playerid  HAVING SUM(P.endseason - P.startseason) >= ALL (SELECT SUM(T.endseason - T.startseason) FROM WorkedYear T GROUP BY T.playerid))";
	char* CharQuery23 = &Query23[0];
	mysql_query(&mysql, CharQuery23);

	// Store result
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);	
}	

	// ---------------
	// QUERY #3
	//----------------

	if(commandNumber == 3 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL queries
	string Query3 = "SELECT X.name, X.height FROM Players X WHERE X.id IN (SELECT P.playerid FROM Played P, Played T WHERE T.playerid = P.playerid AND T.teamid=P.teamid AND ( P.endseason <> T.startseason AND P.startseason <> T.endseason AND P.startseason <> T.startseason))";
	char* CharQuery3 = &Query3[0];
	
	// Run and store result
	mysql_query(&mysql, CharQuery3);
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
}	

	// ---------------
	// QUERY #4
	//----------------

	if(commandNumber == 4 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL queries
	string Query4 = "SELECT N.name FROM Played P, Players N, Champions C WHERE N.id = P.playerid AND C.teamid = P.teamid AND C.season >= P.startseason AND ( C.season <= P.endseason OR P.endseason = 0)  GROUP BY P.playerid HAVING COUNT(P.Playerid) > 2";
	char* CharQuery4 = &Query4[0];
	
	// Run and store result
	mysql_query(&mysql, CharQuery4);
	result = mysql_store_result(&mysql);
	
	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
	
}	

	// ---------------
	// QUERY #5
	//----------------

	if(commandNumber == 5 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL queries
	string Query5 = "SELECT N.name FROM Players N WHERE N.id IN ( SELECT P.playerid FROM Played P WHERE P.teamid IN (SELECT T.teamid FROM Champions T WHERE T.teamid ) AND EXISTS ( SELECT K.playerid FROM Played K WHERE K.playerid = N.id AND K.teamid IN ( SELECT H.teamid FROM Champions H WHERE H.teamid <> P.teamid)))";
	char* CharQuery5 = &Query5[0];

	// Run and store result	
	mysql_query(&mysql, CharQuery5);
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
}	


	// ---------------
	// QUERY #6
	//----------------

	if(commandNumber == 6 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL queries
	string Query6 = "SELECT DISTINCT X.name FROM Teams X WHERE X.id IN (SELECT T.teamid FROM Champions T WHERE EXISTS  (SELECT Y.teamid FROM Champions Y WHERE (T.season = Y.season + 1 OR T.season = Y.season -1) AND Y.teamid=T.teamid))";
	char* CharQuery6 = &Query6[0];

	// Run and store result	
	mysql_query(&mysql, CharQuery6);
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
}	

	// ---------------
	// QUERY #7
	//----------------

	if(commandNumber == 7 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL queries
	string Query7 = "SELECT X.name FROM Players X WHERE EXISTS (SELECT Playerid, COUNT(DISTINCT(no)) from Played WHERE Playerid = X.id GROUP BY Playerid HAVING COUNT(no) > 2)";
	char* CharQuery7 = &Query7[0];

	// Run and store result	
	mysql_query(&mysql, CharQuery7);
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
}

	// ---------------
	// QUERY #8
	//----------------

	if(commandNumber == 8 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL queries
	string Query8 = "SELECT N.name FROM Players N WHERE N.id IN ( SELECT P.playerid FROM Played P WHERE P.teamid IN (SELECT T.id FROM Teams T WHERE T.conference = 'Western' ) AND EXISTS (SELECT Y.playerid FROM Played Y WHERE Y.playerid = P.playerid AND Y.teamid IN (SELECT Z.id FROM Teams Z WHERE Z.conference = 'Eastern' )))";
	char* CharQuery8 = &Query8[0];

	// Run and store result	
	mysql_query(&mysql, CharQuery8);
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
}


	// ---------------
	// QUERY #9
	//----------------

	if(commandNumber == 9 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL queries
	string Query9 = "SELECT N.name FROM Players N WHERE N.id IN ( SELECT P.playerid FROM Played P WHERE P.teamid IN (SELECT T.teamid FROM Champions T WHERE T.teamid IN (SELECT Z.id FROM Teams Z WHERE Z.conference = 'Eastern' )))  AND EXISTS ( SELECT K.playerid FROM Played K WHERE K.playerid = N.id AND K.teamid IN ( SELECT H.teamid FROM Champions H WHERE H.teamid IN (SELECT A.id FROM Teams A WHERE A.conference = 'Western' )))";
	char* CharQuery9 = &Query9[0];

	// Run and store result	
	mysql_query(&mysql, CharQuery9);
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
}



	// ---------------
	// QUERY #10
	//----------------

	if(commandNumber == 10 )
{
	// Define MYSQL result and row pointers
	MYSQL_RES *result;
	MYSQL_ROW row;
			  
	// String for SQL queries
	string Query10 = "SELECT COUNT(P.teamid) FROM Played P WHERE P.teamid IN (SELECT T.id FROM Teams T WHERE T.conference = 'Western' AND T.id = P.teamid)";
	char* CharQuery10 = &Query10[0];

	// Run and store result	
	mysql_query(&mysql, CharQuery10);
	result = mysql_store_result(&mysql);

	// Print result
	while ((row = mysql_fetch_row(result)))
	{
		if (row[0] != "NULL");
			cout << row[0] << endl;
	}

	// Clear
	mysql_free_result(result);
}



// End of query commands
}

	
	// ---------------
	// QUIT  
	//----------------

	else if (command == "quit")
	{
		// End of operations flag
		flag = 0;
	}
}

return 0;

// End of main function
}
// End of code

