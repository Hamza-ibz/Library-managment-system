/*
 library.cpp
 Student ID: M00737296
 Created: 1/4/2021
 Updated: 28/4/2021
*/

#ifndef _HASHTABLE_H_INCLUDED_
#define _HASHTABLE_H_INCLUDED_

#include <iostream>
#include <string>
#include <string.h>
#include "book_class.h"

class hash
{
private:
  static const int TABLESIZE = 251;
  Book *HashTable[TABLESIZE];

public:
  hash();
  ~hash();
  bool fnd(std::string title);
  bool Prntindx(int index);
  int HashFunction(std::string key);
  void AddBook(Book b);
  int numin(int index);
  void Printindex(int index);
  void Find(std::string title);
  void RemoveBook(std::string title);
};

#endif
