/* 
 * File:   Program4.cpp
 * Author: Nicholas Hollis
 *
 * Created on November 6, 2012
 * 
 * This program reads in records from 2 input files (one file of students and their data
 * the other of classes students are taking associated by their student number)
 * into dynamic data stuctures from the Standard Template Library that are
 * managed by the classes. User will select search parameters of student numbers,
 * student name, or by course number to search for students or classes and 
 * (if they exist) will out put the requested data.  The user will then be able to 
 * cycle through the existing files until they quit to return to the main menu.
 * Program uses try/catch/throw for exception handeling.
 */

#include <cstdlib>	   //standard library
#include <iostream>    //for in/out stream to user
#include <string>      //for strings
#include <fstream>     //for input files
#include <sstream>	   //for string stream for parsing data
#include <cassert>     //for assert
#include <vector>	   //for vectors
#include <exception>   //for exception handleing with catch throw
#include "student.h"   //for student class
#include "Classes.h"   //for classes class

using namespace std;

bool getstudent(string);  //function to get student data from file
bool getclasses(string);  //fucntion to get classes data from file
bool is_valid_alpha(string data);  //function to check if string is all alphabetic
bool is_valid_num(string data);		//function to check if a string is all numeric
bool is_valid_alphanum(string data);  //function to check if a string is alpha-numeric

ifstream infile;
ifstream in;
student students;  //student class variable
Classes classes;   //classes class variable

int main(int argc, char** argv) 
{
    string filename = "student.txt";                    //input file names
	string file2name = "class.txt";
    int num_of_students = 0;

	try
	{
		while(getstudent(filename))			//get student data
		{
			num_of_students++;
		}
	}
	catch (bool file)	//catches file open error
	{
		cout << endl << " Could not open " << filename << ", program is ending" << endl;
		system ("PAUSE");
		return 1;
	}
	
	catch (double num_of_data_fields) //catches invalid number of fields error
	{
		cout << endl << "Error in input file:  " << (int)num_of_data_fields << " data fields on line " << num_of_students+1
			<< " in student.txt; there should be 5." << endl;
		system ("PAUSE");
		return 2;
	}

	catch (int data_size) //catches size of data if input line has too many or too few data members 
	{
		cout << endl << "Error in input file:  Invalid input on line " << num_of_students +1
			<< " of " << filename << ".  Input has too many or too few characters:  " << data_size << endl;
		system ("PAUSE");
		return 3;
	}

	catch (string data)  //catches string of bad data that contains invalid characters
	{
		cout << endl << "Error in input file:  Invalid student data on line " << num_of_students +1
			<< " of " << filename << " contains invalid characters:  " << data << endl;
		system ("PAUSE");
		return 4;
	}

	catch(...)
	{
		cout << "Error:  Unknown exception occured.  Program ending..." << endl;
		system ("PAUSE");
		return -2;
	}

    if (num_of_students == 0)
	{
		cout << endl << "Error:  No students in student.txt file.  Program ending..." << endl;
		system ("PAUSE");
        return -1;
	}
    cout << "Total number of student records in file student.txt:  " << num_of_students << endl << endl;  //display number of student files loaded


	int num_of_classes = 0;
	try
	{
		while(getclasses(file2name))		//get class data
		{
			num_of_classes++;
		}
	}
	catch (bool file)	//catches file open error
	{
		cout << endl << " Could not open " << file2name << ", program is ending" << endl;
		system ("PAUSE");
		return 5;
	}
	
	catch (double num_of_data_fields) //catches invalid number of fields error
	{
		cout << endl << "Error in input file:  " << (int)num_of_data_fields << " data fields on line " << num_of_classes 
			<< " in class.txt; there should be 5." << endl;
		system ("PAUSE");
		return 6;
	}

	catch (int data_size) //catches size of data if input line has too many or too few data members 
	{
		cout << endl << "Error in input file:  Invalid input on line " << num_of_classes+1 
			<< " of " << file2name << ".  Input has too many or too few characters:  " << data_size << endl;
		system ("PAUSE");
		return 7;
	}

	catch (string data)  //catches string of bad data that contains invalid characters
	{
		cout << endl << "Error in input file:  Invalid student data on line " << num_of_classes+1
			<< " of " << file2name << " contains invalid characters:  " << data << endl;
		system ("PAUSE");
		return 8;
	}

	catch(...)
	{
		cout << "Error:  Unknown exception occured.  Program ending..." << endl;
		system ("PAUSE");
		return -2;
	}

    if (num_of_classes == 0)
    {
		cout << endl << "Error:  No classes in class.txt file. Program Ending..." << endl;
        return -1;
	}
    cout << "Total number of class records in file class.txt:  " << num_of_classes << endl << endl;  //display number of class files loaded

	int response;
    cout << endl << endl << "Select an option:  " << endl;						//display selection screen to user
	cout << endl << "1 student data (by student ID)" << endl;
	cout << endl << "2 student data (by student last name" << endl;
	cout << endl << "3 class data (by course number)" << endl;
	cout << endl << "4 end the program" << endl << endl;
	cin >> response;
	while (response < 1 || response >4)
	{															//check that selection is valid
		cout << endl << "Invalid selection!" << endl;				//if not, print error and re-display selection screen
		cout << "Please try again."  << endl; 
		cout << endl << endl << "Select an option:  " << endl;
		cout << endl << "1 student data (by student ID)" << endl;
		cout << endl << "2 student data (by student last name" << endl;
		cout << endl << "3 class data (by course number)" << endl;
		cout << endl << "4 end the program" << endl << endl;
		cin >> response;
	}
	while (response != 4)		//switch statement for main menu   (if 4 will exit)
	{
		switch(response)
		{
			case 1:			//case 1 sorsts, searches, and displays student records by student numbers
				students.search_studentnum();
				break;
	
			case 2:			//case 2 sorsts, searches, and displays student records by student last names
				students.search_last_name();
				break;

			case 3:			//case 3 sorsts, searches, and displays class records by course numbers
				classes.search_coursenum();
				break;

		}
		cout << endl << endl << "Select an option:  " << endl;						//display selection screen to user
		cout << endl << "1 student data (by student ID)" << endl;
		cout << endl << "2 student data (by student last name" << endl;
		cout << endl << "3 class data (by course number)" << endl;
		cout << endl << "4 end the program" << endl << endl;
		cin >> response;
		while (response < 1 || response >4)
		{															//check that selection is valid
			cout << endl << "Invalid selection!" << endl;				//if not, print error and re-display selection screen
			cout << "Please try again."  << endl; 
			cout << endl << "Select an option:  " << endl;
			cout << endl << "1 student data (by student ID)" << endl;
			cout << endl << "2 student data (by student last name" << endl;
			cout << endl << "3 class data (by course number)" << endl;
			cout << endl << "4 end the program" << endl << endl;
			cin >> response;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Description:  Gets student data and sends it to class to be put into a vector.

// Precondition:  Must pass file name where student data is located

// Postcondistion:  All student data read into student class

// Implementation:  Retrieves studend data from file, tests data for good input, and passes to student class
// in a loop until all data is read from file. (if bad data, then exception is thrown)

bool getstudent(string filename)             //function to retrieve students from input file until end of file
{  
   string line;
   string num;
   string last;
   string first;
   string m;
   string y;
   bool file = true; 
   if(!infile.is_open())
   {  
      infile.open(filename.c_str());
      if (infile.fail())
      {                                 //check if file opened.  if not throw error
		  file = false;
          throw file;
      }
   }
    // load student data
   getline(infile, line);
    if(infile.eof())		//check for end of file
   {  infile.close();
      return false;
   }
   else
   {  
	   assert(!infile.fail());
   }

   istringstream input(line);
   string parse;
   vector<string> data;
   input >> parse;
   while(input)
   {
	  	   data.push_back(parse);
		   input >> parse;
   }
   int num_of_data_fields = data.size(); 
   if(num_of_data_fields != 5)			//check for proper number of fields in the line of data before processing
   {									//if not 5 fields, then throw error
	   throw (double)num_of_data_fields;
   }
  
   //process student data
   num = data[0];
   int num_size = num.size();
   if(num_size != 9)			//check student numbers are 9 digits
   {							//if not then throw error
	   throw num_size;
   }
   if(!(is_valid_num(num)))	//check if student numbers are all digits.  
   {								//if not then throw error
	   throw num;
   }

   last = data[1];
   int last_size = last.size();
   if(last_size > 20)				//check students' last names do not exceed 20 characters
   {
	   throw last_size;
   }
   if(!(is_valid_alpha(last)))	//check if student last names are all letters.  
   {								//if not then throw error
	   throw last;
   }

   first = data[2];
   int first_size = first.size();
   if(first_size > 20)				//check students' first names do not exceed 20 characters
   {
	   throw first_size;
   }
   if(!(is_valid_alpha(first)))	//check if student first names are all letters.  
   {								//if not then throw error
	   throw first;
   }

   m = data[3];
   int m_size = m.size();
   if(m_size != 2)				//check students' majors do not exceed 2 characters
   {
	   throw m_size;
   }
   if(!(is_valid_alpha(m)))	 //check if student majors are represented by letters.  
   {								//if not then throw error
	   throw m;
   }
   
   y = data[4];
   int y_size = y.size();
   if(y_size != 2)				//check students' class years do not exceed 2 characters
   {
	   throw y_size;
   }
   if(!(is_valid_alpha(y)))	//check if student class years are represented by letters.  
   {								//if not then throw error
	   throw y;
   }
   
   students.enter_student(num, last, first, m, y);		//call students member function to enter student data into student class
   assert(!infile.fail());
   return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Description:  Gets class data and sends it to classes class to be put into a vector.

// Precondition:  Must pass file name where class data is located

// Postcondistion:  All class data read into classes class

// Implementation:  Retrieves classes data from file, tests data for good input and passes to the classes class
// in a loop until all data is read from file.  (if input is bad, exception is thrown)

bool getclasses(string file2name)      //function to get classes from second input file until end of file        
{
   string line;
   string num;
   string sect;
   string numb_of_students;
   string room;
   string ID;
   bool file = true; 
   if(!in.is_open())
   {  
      in.open(file2name.c_str());
      if (in.fail())
      {                                 //check if file opened.  if not throw error
		  file = false;
          throw file;
      }
   }
    // load classes data
   getline(in, line);
    if(in.eof())		//check for end of file
   {  in.close();
      return false;
   }
   else
   {  
	   assert(!in.fail());
   }

   istringstream input(line);
   string parse;
   vector<string> data;
   input >> parse;
   while(input)
   {
	  	   data.push_back(parse);
		   input >> parse;
   }
   int num_of_data_fields = data.size(); 
   if(num_of_data_fields != 5)			//check for proper number of fields in the line of data before processing
   {									//if not 5 fields, then throw error
	   throw (double)num_of_data_fields;
   } 
  

   // process classes data
   num = data[0];
   int num_size = num.size();
   if(num_size != 5)			//check course numbers are 5 characters
   {							//if not then throw error
	   throw num_size;
   }
   if(!(is_valid_alphanum(num)))	//check if course numbers are all represented by alpha-numeric.  
   {								//if not then throw error
	   throw num;
   }
   
   sect = data[1];
   int sect_size = sect.size();
   if(sect_size > 2)				//check section numbers are no greater than 2 digits
   {
	   throw sect_size;
   }
   if(!(is_valid_num(sect)))	//check if section number is represented by all digits.  
   {								//if not then throw error
	   throw sect;
   }
   if(sect == "0" || sect == "00")		//check if section number is zero; if so throw error
   {
	   throw sect;
   }
   
   numb_of_students = data[2];
   int numb_of_students_size = numb_of_students.size();
   if(numb_of_students_size > 3)				//check number of students are prepresented by no more than 3 digits
   {
	   throw numb_of_students_size;
   }
   if(!(is_valid_num(numb_of_students)))	//check if the number of students are all digits.  
   {								//if not then throw error
	   throw numb_of_students;
   }
   
   room = data[3];
   int room_size = room.size();
   if(room_size > 10)				//check classrooms do not exceed 10 characters
   {
	   throw room_size;
   }
   if(!(is_valid_alphanum(room)))	 //check if classrooms are represented by alpha-numeric.  
   {								//if not then throw error
	   throw room;
   }

   ID = data[4];
   int ID_size = ID.size();
   if(ID_size != 9)				//check faculty IDs are 9 digits
   {
	   throw ID_size;
   }
   if(!(is_valid_num(ID)))	//check if faculty IDs are represented by all digits.  
   {								//if not then throw error
	   throw ID;
   }
   
   classes.enter_class(num, sect, numb_of_students, room, ID);  //call classes member function to enter class data
   assert(!in.fail());
   return true;
}

bool is_valid_num(string data)
{
	bool valid = true;
	for(int i=0; i<data.size(); i++)
	{
		if(!isdigit(data[i]))
		{
			valid = false;
		}
	}
	return valid;
}

bool is_valid_alpha(string data)
{
	bool valid = true;
	for(int i=0; i<data.size(); i++)
	{
		if(!isalpha(data[i]))
		{
			valid = false;
		}
	}
	return valid;
}

bool is_valid_alphanum(string data)
{
	bool valid = true;
	for(int i=0; i<data.size(); i++)
	{
		if(!isalnum(data[i]))
		{
			valid = false;
		}
	}
	return valid;
}