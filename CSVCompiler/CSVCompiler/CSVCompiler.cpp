// CSVCompiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
using namespace std;

int randomize(int limit);
//Precondition: A random number is needed, and a limit is provided.
//Postcondition: A random number is returned within that limit.

int main()
{
	//Used for random generation.
	srand(time(NULL));

	//Files to output and import data to, and the file path.
	ofstream outputFile;
	ifstream inputFile1;
	ifstream inputFile2;
	ifstream inputFile3;
	
	//Represents a line on each of the three cvs files.
	string fileLine1;
	string fileLine2;
	string fileLine3;

	//List of all majors and institutions.
	vector<string> majorList, institutionList;
	
	//Lists all possible states.
	vector <string> states= {"AL","AK","AZ","AR","CA","CO","CT","DE","FL","GA",
							 "HI","ID","IL","IN","IA","KS","KY","LA","ME","MD", 
							 "MA","MI","MN","MS","MO","MT","NE","NV","NH","NJ", 
							 "NM","NY","NC","ND","OH","OK","OR","PA","RI","SC", 
							 "SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"};

	//Filenames of the csvFiles.
	string outputFileName = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/csvPackage.csv";
	string fileName1 = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/MergerPersons1.csv";
	string fileName2 = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/Major.csv";
	string fileName3 = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/Institution.csv";

	//Stores at least 20 institutions into each state
	for (int i = 0; i < states.size(); i++)
	{
		int counter = 0;
		inputFile3.open(fileName3);
		
		//Removes the column headers.
		getline(inputFile3, fileLine3);

		do
		{	
			string linePart;
			do
			{
				getline(inputFile3, fileLine3,',');
				linePart += fileLine3 + ',';
			} 
			while (fileLine3.length() > 2);

			if (fileLine3 == states[i])
			{
				counter++;
				getline(inputFile3, fileLine3);
				linePart += fileLine3;
				institutionList.push_back(linePart);
				
			}
			else
			{
				//Goes to the next section.
				getline(inputFile3, fileLine3);
			}
		}
		while (!inputFile3.eof() && counter < 20);
		inputFile3.close();
	}

	/*
	//Opens each files.
	outputFile.open(outputFileName);
	inputFile1.open(fileName1);
	inputFile2.open(fileName2);
	inputFile3.open(fileName3);

	//Gets the first row (column names) of each file, and output it.
	getline(inputFile2, fileLine2);
	getline(inputFile3, fileLine3);
	outputFile << "FirstName,MiddleName,LastName,Gender,Address,ContactPhone,BirthDate" << "," << fileLine2 << "," << fileLine3;
	outputFile << endl;

	//Fills the list of majors.
	do
	{
		getline(inputFile2, fileLine2);
		majorList.push_back(fileLine2);
	} 
	while (!inputFile2.eof());

	do
	{	
		getline(inputFile1, fileLine1);
		outputFile << fileLine1 << "," << majorList[randomize(majorList.size())] << "," << institutionList[randomize(institutionList.size())];
		if(!inputFile1.eof())
		{
			outputFile << endl;
		}
	} 
	while (!inputFile1.eof());

	//Closes the files.
	inputFile1.close();
	inputFile2.close();
	inputFile3.close();
	outputFile.close();
	*/

	//Opens the files to create the csv file for the shrunken list.
	outputFileName = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/InstitutionSmall.csv";
	outputFile.open(outputFileName);
	inputFile3.open(fileName3);

	//Gets the column headers for the shrunken institution list.
	getline(inputFile3, fileLine3);
	outputFile << fileLine3 << endl;

	for (int i = 0; i < institutionList.size() - 1; i++)
	{
		outputFile << institutionList[i] << endl;
	}
	outputFile << institutionList[institutionList.size() - 1];
	outputFile.close();
	/*
	//Prepare to output a person/institution relationship.
	outputFileName = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/PersonAndInstitution.csv";
	outputFile.open(outputFileName);
	inputFile1.open(fileName1);
	inputFile3.open(fileName3);

	//Gets the column headers of the files.
	getline(inputFile3, fileLine3);
	outputFile << "FirstName,MiddleName,LastName,Gender,Address,ContactPhone,BirthDate,InstiID_F,InstiID_P," << fileLine3;

	//Outputs the data, connecting the id of the institution with the person data.
	int randomNum;
	do
	{
		randomNum = randomize(institutionList.size());
		getline(inputFile1, fileLine1);
		outputFile << fileLine1 << "," << randomNum << "," << randomNum << "," << institutionList[randomNum];
		if (!inputFile1.eof())
		{
			outputFile << endl;
		}
	} while (!inputFile1.eof());
    
	//Closes the files.
	inputFile1.close();
	inputFile3.close();
	outputFile.close();
	*/
	return 0;
}

int randomize(int limit)
{
	return rand() % limit;
}