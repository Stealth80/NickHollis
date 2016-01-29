/* 
 * File:   student.h
 * Author: Nick Hollis
 *
 * Created on October 15, 2012
 */


#ifndef CLASSES_H
#define	CLASSES_H

#include <string>

class Classes
{
  public:
	  void enter_class(std::string, std::string, std::string, std::string, std::string);
	  void search_coursenum();
	  void display_class();
	  
	  bool operator<(const Classes* a)
	  {
		return this->course_number < a->course_number;
	  }

	  Classes();
      ~Classes();
      Classes(std::string, std::string, std::string, std::string, std::string);
  private:
	  std::string course_number;
      std::string section;
      std::string number_of_students;
      std::string classroom;
	  std::string faculty_ID;

};


#endif	/* CLASSES_H */