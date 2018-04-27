// CourseCSVCompiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
int main()
{
		ifstream inputFile;
		ofstream outputFile;
		string fileNameI = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/Major.csv";
		string fileNameO = "C:/Users/NguyenChris/Desktop/Folders/VS Programs/Course.csv";
		string data;

		//Opens the major file and eats the column headers.
		inputFile.open(fileNameI);
		outputFile.open(fileNameO);
		getline(inputFile, data);


		//Outputs the column headers of the course class to the output file.
		outputFile << "CourseID,ClassID,CourseName,CourseDesc" << endl;

		//Used to assign a unique id to each class.
		int counter = 1;

		do
		{
		//Retrieves the initials from the major table.
		string initials;
		getline(inputFile, data, ',');
		getline(inputFile, initials, ',');
		getline(inputFile, data);

		for (int courseLevel = 100; courseLevel <= 400; courseLevel += 100)
		{
			//Sets the academic level of the course.
			string academicLevel;
			if (courseLevel == 100)
			{
				academicLevel = "Freshman";
			}
			else if (courseLevel == 200)
			{
				academicLevel = "Sophomore";
			}
			else if (courseLevel == 300)
			{
				academicLevel = "Junior";
			}
			else
			{
				academicLevel = "Senior";
			}

			for (int classNum = 1; classNum <= 10; classNum++)
			{
				//Gets the class number and course level put together.
				int classID = courseLevel + classNum;

				string className = initials + "-" + to_string(classID);
				string classDesc = initials + "-" + academicLevel + "-" + to_string(classID);
				
				outputFile << counter++ << "," << classID << "," << className << "," << classDesc;
				
				if(courseLevel < 400 || classNum < 10)
				{
					outputFile << endl;
				}
			}
		}
		if (!inputFile.eof())
		{
			outputFile << endl;
		}
	}
	while (!inputFile.eof());
    return 0;
}

