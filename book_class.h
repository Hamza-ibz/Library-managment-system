/*
 library.cpp
 Student ID: M00737296
 Created: 1/4/2021
 Updated: 28/4/2021
*/

#ifndef _BOOK_CLASS_H_INCLUDED_
#define _BOOK_CLASS_H_INCLUDED_

#include <iostream>
#include <string>
#include <string.h>

class Book
{
private:
  std::string title;
  std::string authors;
  std::string ISBN;
  int numOfcopies;

public:
  Book(std::string title, std::string authors, std::string ISBN, int numOfcopies);
  Book();
  std::string get_title();
  void set_title(std::string title);
  std::string get_authors();
  void set_authors(std::string authors);
  int get_numofcopies();
  void set_numofcopies(int title);
  std::string get_ISBN();
  void set_ISBN(std::string authors);
  Book *next;
};

#endif
