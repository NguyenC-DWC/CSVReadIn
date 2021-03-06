// CSVReadIn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <time.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>

using namespace std;

int randomize(int limit);
//Precondition: A random number is needed, and a limit is provided.
//Postcondition: A random number is returned within that limit.

void apostropheReplace(string& data);
//Precondition: A string with a single quote is passed in.
//Postcondition: The single quote is replaced with an apostrophe.

string randomizeGrade();
//Precondition: A string is needed.
//Postcondition: A random grade is returned.

int main()
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;

	driver = get_driver_instance();
	con = driver->connect("accessedu.cuir5e4ev2po.us-east-2.rds.amazonaws.com:3306", "admin", "pLLV48BqcPbdGnbMX66VAB");
	/* Connect to the MySQL test database */
	con->setSchema("AccessEdu");

	stmt = con->createStatement();

	//Used for random number generation.
	srand(time(NULL));

	//Used to calculate GPA.
	map<string, double> gradeScale = {{"A+",4.00},{"A",4.00},{"A-",3.70},{"B+",3.30},{"B",3.00},{"B-",2.70},{"C+",2.30},{"C",2.00},{"C-",1.70},{"D+",1.30},{"D",1.00},{"D-",.70},{"F",0.00}};

	//Used to import csv files to the program.
	ifstream inputFile;

	//Used to build the sql command to insert data.
	string tableName;
	string values;
	string data;

	//Represents the files to be read in.
	vector <string> fileNames = { "Person","Address","InstitutionSmall","Major","Course"};

	//Represents the command.
	string command;

	cout << "Importing from csv file." << endl;

	//Opens the file, and gets the table name, values to input, and the first set of data.
	for (int i = 0; i < fileNames.size(); i++)
	{
		tableName = fileNames[i];
		string fileName = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/" + tableName + ".csv";
		inputFile.open(fileName);
		getline(inputFile, values);
		
		/*
		if (fileNames[i] == "Person")
				{
					do
					{
						//Creates the beginning of the command.
						command = "insert into " + tableName + " (" + values + ") values ";
						string dataPart = "(";

						for (int j = 0; j < 7; j++)
						{
							if (j < 6)
							{
								getline(inputFile, data, ',');
								if (j == 1 || j == 2 || j == 3 || j == 4 || j == 5)
								{
									//These fields are varchar columns, so the fields read in need proper formating for insertion.
									//Replaces the single quotes with apostrophes.
									apostropheReplace(data);
									dataPart += "'" + data + "'";
								}
								else
								{
									//Represents numerical data values.
									dataPart += data;
								}
								dataPart += ",";
							}
							else
							{
								//Last column has varchar values. Format data.
								getline(inputFile, data);
								apostropheReplace(data);
								dataPart += "'" + data + "');";
							}
						}
						//Adds the rest of the command to the beginning template.
						command += dataPart;

						//Executes the statement.
						try
						{
							stmt->execute(command);
						}
						catch (sql::SQLException &e)
						{
							cout << "Error inserting data: " << command << endl;
						}

					} while (!inputFile.eof());
				}
			
			//Process is the same for the other tables.
		if (fileNames[i] == "Address")
				{
						do
						{
							command = "insert into " + tableName + " (" + values + ") values ";
							string dataPart = "(";

							for (int j = 0; j < 6; j++)
							{
								if (j < 5)
								{
									getline(inputFile, data, ',');
									if (j == 1 || j == 2 || j == 3 || j == 4)
									{
										dataPart += "'" + data + "'";
									}
									else
									{
										dataPart += data;
									}
									dataPart += ",";
								}
								else
								{
									getline(inputFile, data);
									dataPart += "'" + data + "');";
								}
							}
							command += dataPart;

							//Executes the statement.
							try
							{
								stmt->execute(command);
							}
							catch (sql::SQLException &e)
							{
								cout << "Error inserting data: " << command << endl;
							}
						} while (!inputFile.eof());
				}

		if (fileNames[i] == "InstitutionSmall")
		{
			int counter = 0;
			do
			{
				command = "insert into Institution(InstID," + values + ") values ";
				string dataPart = "(";

				for (int j = 0; j < 9; j++)
				{
					if (j < 8)
					{
						if (j < 8 && j > 0)
						{
							getline(inputFile, data, ',');
							//Some of the names of the instutition have a quote in the beginning when represented in csv. Everything inbetween the quotes is inserted as a single value.
							if (data[0] == '"')
							{
								string quotedPart = "";
								//Removes the quote at the beginning.
								data.erase(0, 1);
								//Gets each piece of the data until it reaches the other qote.
								do
								{
									quotedPart += data + ",";
									getline(inputFile, data, ',');
								} while (data[data.size() - 1] != '"');
								data.erase(data.size() - 1, data.size());
								quotedPart += data;

								//Replaces the single quotes with apostrophes in the name.
								apostropheReplace(quotedPart);
								dataPart += "'" + quotedPart + "'";
							}
							else
							{
								apostropheReplace(data);
								dataPart += "'" + data + "'";
							}

						}
						else
						{
							counter++;
							dataPart += to_string(counter);

						}
						dataPart += ",";
					}
					else
					{
						getline(inputFile, data);
						dataPart += "'" + data + "');";
					}
				}
				command += dataPart;

				//Executes the statement.
				try
				{
					stmt->execute(command);
				}
				catch (sql::SQLException &e)
				{
					cout << "Error inserting data: " << command << endl;
				}
			} while (!inputFile.eof());
		}
		
		if (fileNames[i] == "Major")
		{
			do
			{
				command = "insert into " + tableName + " (" + values + ") values ";
				string dataPart = "(";

				for (int j = 0; j < 5; j++)
				{
					if (j < 4)
					{
						getline(inputFile, data, ',');
						if (j == 1 || j == 2 || j == 3)
						{
							if (data[0] == '"')
							{
								string quotedPart = "";
								data.erase(0, 1);
								do
								{
									quotedPart += data + ",";
									getline(inputFile, data, ',');
								} while (data[data.size() - 1] != '"');
								data.erase(data.size() - 1, data.size());
								quotedPart += data;
								dataPart += "'" + quotedPart + "'";
							}
							else
							{
								dataPart += "'" + data + "'";
							}
						}
						else
						{
							dataPart += data;
						}
						dataPart += ",";
					}
					else
					{
						getline(inputFile, data);
						dataPart += data + ");";
					}
				}
				command += dataPart;

				//Executes the statement.
				try
				{
					stmt->execute(command);
				}
				catch (sql::SQLException &e)
				{
					cout << "Error inserting data: " << command << endl;
				}
			} while (!inputFile.eof());
		}
		
		if (fileNames[i] == "Course")
				{
					do
					{
						command = "insert into " + tableName + " (" + values + ") values ";
						string dataPart = "(";

						for (int j = 0; j < 4; j++)
						{
							if (j < 3)
							{
								getline(inputFile, data, ',');
								if (j == 2)
								{
									dataPart += "'" + data + "'";
								}
								else
								{
									dataPart += data;
								}
								dataPart += ",";
							}
							else
							{
								getline(inputFile, data);
								dataPart += "'" + data + "');";
							}
						}
						command += dataPart;

						//Executes the statement.
						try
						{
							stmt->execute(command);
						}
						catch (sql::SQLException &e)
						{
							cout << "Error inserting data: " << command << endl;
						}
					} while (!inputFile.eof());
				}
		*/	

		inputFile.close();
	}

	//Insert into the junction tables

/*
	string fileName = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/Person.csv";
	inputFile.open(fileName);
	getline(inputFile, values);
	do
	{
		getline(inputFile, values, ',');
		string commandAddress = "insert into PersonAddress(PersonID,AddressID) values (" + values + "," + to_string(randomize(5000) + 1) + ");";
		string commandInstitution = "insert into PersonInstitution(PersonID,InstiID) values (" + values + "," + to_string(randomize(993) + 1) + ");";

		wstring wCommandA = wstring(commandAddress.begin(), commandAddress.end());
		SQLWCHAR sqlCommandA = (SQLWCHAR)wCommandA.c_str();

		wstring wCommandI = wstring(commandInstitution.begin(), commandInstitution.end());
		SQLWCHAR sqlCommandI = (SQLWCHAR)wCommandI.c_str();

		//Prepare to execute the command in sql.
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		cout << "Error detected." << endl;

		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wCommandA.c_str(), SQL_NTS))
		{
			cout << "Error inserting data: " << commandAddress << endl;;
			cout << "\n";
		}

		//Prepare to execute the command in sql.
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
			cout << "Error detected." << endl;

		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wCommandI.c_str(), SQL_NTS))
		{
			cout << "Error inserting data: " << commandInstitution << endl;;
			cout << "\n";
		}
		getline(inputFile, values);
	}
	while (!inputFile.eof());
*/

/*
	//Insert into InstitutionMajor
	for (int i = 0; i < 993; i++)
	{
		vector <int> usedCategories = {};
		int categoryNumber;
		int repeat = randomize(4) + 3;
		
		for (int j = 0; j < repeat; j++)
		{
			//
			categoryNumber = randomize(16) + 1;
			bool sameFlag;
			
			do
			{
				sameFlag = false;
				for (int c = 0; c < usedCategories.size(); c++)
				{
					if(usedCategories[c] == categoryNumber)
					{
						categoryNumber = randomize(16) + 1;
						sameFlag = true;
					}
				}
			} 
			while (sameFlag);
			
			usedCategories.push_back(categoryNumber);
			
			string command = "insert into InstitutionMajor(InstID,CategoryID) values (" + to_string(i + 1) + "," + to_string(categoryNumber) + ");";
			
			wCommand = wstring(command.begin(), command.end());
			sqlCommand = (SQLWCHAR)wCommand.c_str();

			//Prepare to execute the command in sql.
			if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
				cout << "Error detected." << endl;

			if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)wCommand.c_str(), SQL_NTS))
			{
				cout << "Error inserting data: " << command << endl;
				cout << "\n";
			}
		}
	}
	*/

//Insert into MajorCourse
/*
int counter = 1;
for (int i = 1; i <= 173; i++)
{
	for (int j = 0; j < 40; j++)
	{
		string command = "insert into MajorCourse(MajorID,CourseID) values (" + to_string(i) + "," + to_string(counter++) + ");";

		try
		{
			stmt->execute(command);
		}
		catch (sql::SQLException &e)
		{
			cout << "Error inserting data: " << command << endl;
		}
	}
}
*/


//Files used to create the student course table.
ifstream majorCheck;
ifstream courseCheck;

//Insert into student table. Also insert into student course table.
string fileName = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/Person.csv";
inputFile.open(fileName);
getline(inputFile, values);
do
{
	string personID;
	getline(inputFile, personID, ',');
	string addressID = to_string(randomize(5000) + 1);
	string majorID = to_string(randomize(173) + 1);
	string instID = to_string(randomize(993) + 1);
	string degreeID = to_string(randomize(3) + 1);
	string academicID;

	//If the degree is graduate, then the student in not in an academic level.
	if (degreeID == "3")
	{
		academicID = to_string(5);
	}
	else
	{
		//Assigns a random academic level to the student.
		academicID = to_string(randomize(4) + 1);
	}
	string command = "insert into Student(PersonID,AddressID,MajorID,InstID,AcademicID,DegreeID) values (" + personID + "," + addressID + "," + majorID + "," + instID + "," + academicID + "," + degreeID + ");";

	try
	{
		stmt->execute(command);
	}
	catch (sql::SQLException &e)
	{
		cout << "Error inserting data: " << command << endl;
	}
	getline(inputFile, values);

	//Inserts the courses the student completed into the class_record table. Number of courses completed depends on the academic level of the student.
	//Opens the two files.
	majorCheck.open("C:/Users/NguyenChris/Desktop/Folders/VS Programs/Major.csv");
	courseCheck.open("C:/Users/NguyenChris/Desktop/Folders/VS Programs/Course.csv");
	
	// Eats the column headers.
	getline(majorCheck, values);
	getline(courseCheck, values);

	//Gets the major abbreviation from the major file correlating to the student's major.
	string checkMajorID;
	string majorAB;
	do
	{
		getline(majorCheck,checkMajorID,',');
		getline(majorCheck, majorAB, ',');
		if (majorID != checkMajorID)
		{
			getline(majorCheck, majorAB);
		}
	} 
	while (majorID != checkMajorID);

	//Check which course has the same major assigned as the student.
	string courseID;
	string checkCourseAB;
	do
	{
		getline(courseCheck, courseID, ',');
		getline(courseCheck, checkCourseAB, ',');
		getline(courseCheck, checkCourseAB, '-');
		if (checkCourseAB != majorAB)
		{
			getline(courseCheck, checkCourseAB);
		}
	} while (checkCourseAB != majorAB);

	//Reads the rest of the line.
	getline(courseCheck, checkCourseAB);

	//Determines how many courses are completed depending on the academic level.
	int courseCounter;

	//Determines how much courses the student take depending on academic level.
	switch (stoi(academicID))
	{
		case 1:
			courseCounter = 10;
			break;
		case 2:
			courseCounter = 20;
			break;
		case 3:
			courseCounter = 30;
			break;
		default:
			courseCounter = 40;
			break;
	}

	//Represents the year the course was taken.
	int year = 1;
	double GPA = 0.00;

	for (int i = 0; i < courseCounter; i++)
	{
		//Represents the term the course was taken. Half is in the fall, and half is in the spring.
		string term;
		//Represents the grade the student gets.
		string grade;

		//Assigns a term to a class depending on the course id.
		if (stoi(courseID) % 10 <= 5 && stoi(courseID) % 10 != 0)
		{
			term = "1";
		}
		else
		{
			term = "2";
		}

		//Randomizes the grade the user gets for the class.
		grade = randomizeGrade();

		//Adds the grade gpa value to the student's gpa, used to calculate the actual gpa.
		GPA += (gradeScale.at(grade) * 3);

		command = "insert into Class_Record(TermID,PersonID,CourseID,Grade) values (" + term + "," + personID + "," + courseID + ",\'" + grade + "\');";
		
		try
		{
			stmt->execute(command);
		}
		catch (sql::SQLException &e)
		{
			cout << "Error inserting data: " << command << endl;
		}

		//Calculates the GPA for each term.
		if (i > 0 && stoi(courseID) % 5 == 0)
		{
			GPA /= 15;
			command = "insert into Term_Record(PersonID,TermID,Year,totalCredits,GPA) values (" + personID + "," + term + "," + to_string(year) + ",15," + to_string(GPA) + ");";
			
			try
			{
				stmt->execute(command);
			}
			catch (sql::SQLException &e)
			{
				cout << "Error inserting data: " << command << endl;
			}
			
			//Resets to 0 for the next term.
			GPA = 0.00;
		}

		if (stoi(courseID) % 10 == 0)
		{
			year++;
		}

		getline(courseCheck, courseID, ',');
		getline(courseCheck, checkCourseAB);
	}
		//Closes the files.
		majorCheck.close();
		courseCheck.close();

} while (!inputFile.eof());

	inputFile.close();
	delete stmt;
	delete con;

	system("pause");
	return 0;
}

int randomize(int limit)
{
	return rand() % limit;
}

void apostropheReplace(string & data)
{
	int counter = 0;
	bool foundQuote = false;

	if(data == "")
	{
		return;
	}

	do
	{
		
		if (data[counter] == '\'')
		{
			data[counter] = '`';
			foundQuote = true;
		}
		counter++;
	} while (!foundQuote && counter < data.size());
}

string randomizeGrade()
{
	string grade = "";
	int letter = randomize(5);
	int follower = randomize(3);
	
	switch (letter)
	{
		case 0:
			grade += "F";
			break;
		case 1:
			grade += "D";
			break;
		case 2:
			grade += "C";
			break;
		case 3:
			grade += "B";
			break;
		default:
			grade += "A";
			break;
	}

	if (grade == "F")
	{
		grade += "";
	}
	else
	{
		switch (follower)
		{
		case 0:
			grade += "-";
			break;
		case 1:
			grade += "+";
			break;
		default:
			grade += "";
			break;
		}
	}
	return grade;
}