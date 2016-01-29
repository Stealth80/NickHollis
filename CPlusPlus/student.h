/* 
 * File:   student.h
 * Author: Nick Hollis
 *
 * Created on October 15, 2012
 *
 * This class is designed to hold student data including first and last name, 
 * student number, major, and what year class they are.  It also allows for 
 * searching via both student number and by last name of student.
 */

#ifndef STUDENT_H
#define	STUDENT_H

#include <string>

class student           //object to hold each student
{
  public:
      int numberofclasses;


	  void enter_student(std::string, std::string, std::string, std::string, std::string);
      void search_studentnum();
      void search_last_name();
	  void display_student();

	  student();
      ~student();
      student(std::string, std::string, std::string, std::string, std::string);
  private:
	  std::string student_number;
      std::string last_name;
      std::string first_name;
      std::string major;
      std::string year;
};

#endif	/* STUDENT_H */

