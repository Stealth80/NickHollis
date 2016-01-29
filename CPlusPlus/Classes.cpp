/* * 
 * File:   Clalsses.cpp
 * Author: Nick Hollis
 *
 * Created on October 15, 2012
 *
 * This class is designed to hold classes data including course number, 
 * section number, number of students in the class, classroom the class is 
 * held in, and the faculty ID number for that class.  It also allows for 
 * searching via course number.
 */

#include "Classes.h"    //for declaration
#include <iostream>     //for output to user
#include <cstdlib>      //for STL
#include <algorithm>	//for sort
#include <vector>		//for STL vector
#include <string>       //for string

using namespace std;

  
vector<Classes*> university;		//STL container to hold classes data

// Constructor
Classes::Classes(string num, string sect, string num_of_students, string room, string ID)
{
    course_number = num;
    section = sect;
    number_of_students = num_of_students;
    classroom = room;
    faculty_ID = ID;
    
    return;
}

// Default constructor
Classes::Classes()
{
    course_number = "empty";
    section = "Default";
    number_of_students = "0";
    classroom = "Constructor";
    faculty_ID = "0000";
}

void Classes::display_class()                                  //public function for student class to display student info
{
                                       //output student
    cout << endl << "Course number:                   " << course_number << endl;
    cout << endl << "Section:                         " << section << endl;
    cout << endl << "Number of Students:              " << number_of_students << endl;
    cout << endl << "Classroom:                       " << classroom << endl;
    cout << endl << "Faculty ID:                      " << faculty_ID << endl;
    cout << endl << endl << endl << endl;
    return;
}

// Description:  Adds pointer of classes to vector.

// Precondition: Must pass all required data to create classes: course number,
//		section, number of students in class, classroom, and faculty ID.

// Postcondistion:  Adds pointer to this class to vector.

// Implementation:  Creats classes pointer.  Passes class data to constructor to 
//		create class record.  Then pushes pointer to this record into vector.
void Classes::enter_class(string num, string sect, string num_of_students, string room, string ID)
{
    Classes* class_pointer;
    class_pointer = new Classes(num, sect, num_of_students, room, ID);
    university.push_back(class_pointer);
}


// Description:  This public function uses a STL sort to sort the 
// vector by course number and allows the user to search for 
// a course and/or search through the class records one at 
// a time.

// Precondition:  void function; no parameters passed.

// Postcondition:  returns to main menu

/* Implementatin:  Sorts vector of classes pointers in order of course numbers.
 * Then allows user to search for a course.  If found; displays class data. 
 * If not, presents error.  Then allows user to cycle through the sorted records  
 * in order (by typing "next") until they choose to return to the main menu 
 * (by typing "quit")
 */
void Classes::search_coursenum()
{
	sort(university.begin(), university.end());	//sorts class data by course number
	string course;
	cout << endl << "Enter course number:  ";				//prompts user to enter course number
	cin >> course;		
	int iter = 0;
	bool match = false;
    int b = university.size();
    for(int i = 0; i<b; i++)                        
    {                                                                       // match current course #
        if(university[i]->course_number == course)
        {
            match = true; 
            university[i]->display_class();                                //after match; call function to display that student
			iter = i;
        }
    }
    if (match == false)
    { 
		iter =  0;												//or if next, display first class record
        if(course == "next" || course == "NEXT")
			university[iter]->display_class();
		else
		{                                                            //if course # does not exist, output error
        cout << endl << "Requested data not found" << endl;  
        cout << endl << endl << endl << endl;
		}
    }

	string next;														//wait for input next or quit
	cin >> next;
	int input_length = next.length();
    for(int a = 0; a<input_length; a++)
    {
        next[a] = tolower(next[a]);      //make input upper case
    }
	while(next != "next")												//test input
	{
		if (next == "quit")
		{
			return;
		}													//prompt user for correct input if invalid
		cout << "Invalid command. (Next for next class record.  Quit to return to menu.)   " << endl;
		cin >> next;	//wait for input next or quit
	}
				
	iter++;
	while (next == "next")		//while loop cylces through records as long as user keeps typing "next"
	{
		if(iter == university.size())
		{											//if at end of the records list, output no more records
			cout << endl << endl << "No more class records" << endl << endl;
			cin >> next;		//wait for input next or quit
			input_length = next.length();
			for(int a = 0; a<input_length; a++)
			{
				next[a] = tolower(next[a]);      //make input upper case
			}
			if(next == "quit")
				return;
			iter = 0;
		}
		university[iter]->display_class();		//output class data
		cin >> next;		//wait for input next or quit
		iter++;
		input_length = next.length();
		for(int d = 0; d<input_length; d++)
		{
			next[d] = tolower(next[d]);      //make input upper case
		}
		while(next != "next")												//test input
		{
			if (next == "quit")
			{
				return;
			}											//prompt user for correct input if invalid
			cout << "Invalid command. (Next for next class record.  Quit to return to menu.)   " << endl;
			cin >> next;		//wait for input next or quit
			input_length = next.length();
			for(int e=0; e<input_length; e++)
			{
				next[e] = tolower(next[e]);      //make input upper case
			}
		}
	}
}

//Deconstructor
Classes::~Classes()
{
				//with a vector, default constructor deallocates memory
	return;
}

