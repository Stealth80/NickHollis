/* 
 * File:   student.cpp
 * Author: Nick Hollis
 *
 * Created on October 15, 2012
 *
 * This class is designed to hold student data including first and last name, 
 * student number, major, and what year class they are.  It also allows for 
 * searching via both student number and by last name of student.
 */

#include "student.h"    //for declaration
#include <iostream>     //for output to user
#include <cstdlib>      //STL
#include <algorithm>	//for sort
#include <vector>		//for STL vector
#include <string>       //for string

using namespace std;
  
vector<student*> student_body;		//STL container object to hold students

//Constructor
student::student(string num, string last, string first, string m, string y)   
{
    student_number = num;
    last_name = last;
    first_name = first;
    major = m;
    year = y;
    
    return;
}

//default constructor
student::student()
{
    student_number = "000000000";
    last_name = "constructor";
    first_name = "default";
    major = "undeclared";
    year = "none";
}

// Description:  Outputs student data to user.
// Precondition: void function; no parameters passed. Must be called through class.
// Postcondistion:  Displays current student data.
// Implementation:  Uses cout statements.
void student::display_student()                                  
{
                                       //output student
    cout << endl << "ID number                   " << student_number << endl;
    cout << endl << "Last name                   " << last_name << endl;
    cout << endl << "First name                  " << first_name << endl;
    cout << endl << "Major                       " << major << endl;
    cout << endl << "Class                       " << year << endl;
    cout << endl << endl << endl << endl;
    return;
}

// Description:  Adds pointer of student to vector.

// Precondition: Must pass all required data to create student: student number,
//		last and first name, major, and year.

// Postcondistion:  Adds pointer to this student to vector.

// Implementation:  Creats student pointer.  Passes student data to constructor to 
//		create student record.  Then pushes pointer to this record into vector.
void student::enter_student(string num, string last, string first, string m, string y)
{
    student* student_pointer;
    student_pointer = new student(num, last, first, m, y);
    student_body.push_back(student_pointer);
}


// Description:  This public function uses a STL sort to sort the 
// vector by student ID number and allows the user to search for 
// a student ID and/or search through the student records one at 
// a time.

// Precondition:  void function; no parameters passed.

// Postcondition:  returns to main menu

/* Implementatin:  Sorts vector of student pointers in order of student numbers.
 * Then allows user to search for a student number.  If found; displays student data. 
 * If not, presents error.  Then allows user to cycle through the sorted records  
 * in order (by typing "next") until they choose to return to the main menu 
 * (by typing "quit")
 */
void student::search_studentnum()
{
	sort(student_body.begin(), student_body.end(), [](student* a, student* b) -> bool	//sort vector by student numbers
		{
			return a->student_number < b->student_number;
		});
	string id;
	cout << endl << "Enter student ID:  ";		//prompt user for student ID
	cin >> id;
	int iter = 0;
	bool match = false;
    int b = student_body.size();
    for(int i = 0; i<b; i++)                        
    {                                                                       // match current student #
        if(student_body[i]->student_number == id)
        {
            match = true; 
            student_body[i]->display_student();                                //after match; call function to display that student
			iter = i;
        }
    }
    if (match == false)
    {																	//next displays first student
		iter =  0;
		if(id == "next" || id == "NEXT")
			student_body[iter]->display_student();
		else
		{
			                                                                //if student # does not exist, output error
			cout << endl << "Requested data not found" << endl;  
			cout << endl << endl << endl << endl;
		}
    }

	string next;														//wait for input next or quit
	cin >> next;
	int input_length = next.length();
    for(int a = 0; a<input_length; a++)
    {
        next[a] = tolower(next[a]);      //make input lower case
    }
	while(next != "next")												//test input
	{
		if (next == "quit")
		{
			return;
		}																//prompt user for correct input if invalid
		cout << "Invalid command. (Next for next student record.  Quit to return to menu.)   " << endl;
		cin >> next;		//wait for input next or quit
	}
				
	iter++;
	while (next == "next")			//while loop cylces through records as long as user keeps typing "next"
	{
		if(iter == student_body.size())
		{									//if at end of the records list, output no more records
			cout << endl << endl << "No more student records" << endl << endl;
			cin >> next;							//wait for input next or quit
			input_length = next.length();
			for(int a = 0; a<input_length; a++)
			{
				next[a] = tolower(next[a]);      //make input lower case
			}
			if(next == "quit")		//quit if user enters "quit"
				return;
			iter = 0;
		}
		student_body[iter]->display_student();		//display student data
		cin >> next;						//wait for input next or quit
		iter++;
		input_length = next.length();
		for(int d = 0; d<input_length; d++)
		{
			next[d] = tolower(next[d]);      //make input lower case
		}
		while(next != "next")												//test input
		{
			if (next == "quit")
			{
				return;
			}															//prompt user for correct input if invalid
			cout << "Invalid command. (Next for next student record.  Quit to return to menu.) " << endl << endl;
			cin >> next;			//wait for user input next or quit
			input_length = next.length();
			for(int d = 0; d<input_length; d++)
			{
				next[d] = tolower(next[d]);      //make input upper case
			}
		}
	}
}


// Description:  This public function uses a STL sort to sort the 
// vector by student last name and allows the user to search for 
// a student last name and/or search through the student records one at 
// a time.  Search assumes name will be entered with first letter capital 
// followed by lower case.  Otherwise will not recognize name.

// Precondition:  void function; no parameters passed.

// Postcondition:  returns to main menu

/* Implementatin:  Sorts vector of student pointers in order of student last names.
 * Then allows user to search for a student by last name.  If found; displays student data. 
 * If not, presents error.  Then allows user to cycle through the sorted records  
 * in order (by typing "next") until they choose to return to the main menu 
 * (by typing "quit")
 */
void student::search_last_name()
{
	sort(student_body.begin(), student_body.end(), [](student* a, student* b) -> bool	//sort vector by student last names
		{
			return a->last_name < b->last_name;
		});
	string last;
	cout << endl << "Enter student last name:  ";		//prompt user for student's last name to search for
	cin >> last;		//program assumes last name will be entered first letter capitalized followed by all lowercase. 
	int iter = 0;				//else will not recognize name
	bool match = false;
    int c = student_body.size();
    for(int j = 0; j<c; j++)                        
    {                                                                       // match current student last name
        if(student_body[j]->last_name == last)
        {
            match = true; 
            student_body[j]->display_student();                                //after match; call function to display that student
			iter = j;
        }
    }
    if (match == false)
    {																//or if next; display first record
		iter =  0;
		if(last == "next" || last == "NEXT")
			student_body[iter]->display_student();
		else
		{                                                                  //if student # does not exist, output error
			cout << endl << "Requested data not found" << endl;  
			cout << endl << endl << endl << endl;
		}

    }

	string next;														//wait for input next or quit
	cin >> next;
	int input_length = next.length();
    for(int d = 0; d<input_length; d++)
    {
        next[d] = tolower(next[d]);      //make input lower case
    }
	while(next != "next")												//test input
	{
		if (next == "quit")
		{
			return;
		}													//prompt user for correct input if invalid
		cout << "Invalid command. (Next for next student record.  Quit to return to menu.)   " << endl;
		cin >> next;		//wait for input next or quit
	}
				
	iter++;
	while (next == "next")		//while loop cylces through records as long as user keeps typing "next"
	{
		if(iter == student_body.size())
		{										//if at end of the records list, output no more records
			cout << endl << endl << "No more student records" << endl << endl;
			cin >> next;			//wait for input next or quit
			input_length = next.length();
			for(int a = 0; a<input_length; a++)
			{
				next[a] = tolower(next[a]);      //make input lower case
			}
			if (next == "quit")
				return;
			iter = 0;
		}
		student_body[iter]->display_student();			//output student data
		cin >> next;							//wait for input next or quit
		iter++;
		input_length = next.length();
		for(int a = 0; a<input_length; a++)
		{
			next[a] = tolower(next[a]);      //make input lower case
		}
		while(next != "next")												//test input
		{
			if (next == "quit")
			{
				return;
			}											//prompt user for correct input if invalid
			cout << "Invalid command. (Next for next student record.  Quit to return to menu.)   " << endl;
			cin >> next;			//wait for input next or quit
			input_length = next.length();
			for(int a = 0; a<input_length; a++)
			{
				next[a] = tolower(next[a]);      //make input lower case
			}
		}
	}
}

// Deconstructor
student::~student()
{
	for (int i = student_body.size()-1; i>=0; i--) //deletion of pointers called by new
	{
		delete student_body[i];
	}
    			//with a vector, default constructor deallocates memory
    return;
}

