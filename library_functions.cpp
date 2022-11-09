/*
 library_functions.cpp
 Student ID: M00737296
 Created: 2/4/2021
 Updated: 28/4/2021
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "hashtable.h"

/*
Book constructor 
*/
Book::Book(std::string title, std::string authors, std::string ISBN, int numOfcopies)
{
  this->title = title;
  this->authors = authors;
  this->ISBN = ISBN;
  this->numOfcopies = numOfcopies;
}

/*
Empty Book constructor 
*/
Book::Book()
{
}

/*
get_title function: gets the title of the book
*/
std::string Book::get_title()
{
  return this->title;
}

/*
set_title function: sets the title of the book
@param title, the title of a book.
*/
void Book::set_title(std::string title)
{
  this->title = title;
}

/*
get_authors function: gets the authors of the book
*/
std::string Book::get_authors()
{
  return this->authors;
}

/*
set_authors function: sets the authors of the book
@param authors, the authors of a book.
*/
void Book::set_authors(std::string authors)
{
  this->authors = authors;
}

/*
get_ISBN function: gets the ISBN of the book
*/
std::string Book::get_ISBN()
{
  return this->ISBN;
}

/*
set_ISBN function: sets the ISBN of the book
@param ISBN, the ISBN of a book.
*/
void Book::set_ISBN(std::string ISBN)
{
  this->ISBN = ISBN;
}

int Book::get_numofcopies()
{
  return this->numOfcopies;
}

/*
set_numofcopies function: sets the quantity of the book
@param numofcopies, the quantity of a book.
*/
void Book::set_numofcopies(int numOfcopies)
{
  this->numOfcopies = numOfcopies;
}

/*
constructor which creates an "empty" node within all the index of the hash table 
*/
hash::hash()
{

  for (int i = 0; i < TABLESIZE; i++)
  {
    HashTable[i] = new Book();
    HashTable[i]->set_title("empty");
    HashTable[i]->set_authors("empty");
    HashTable[i]->set_ISBN("empty");
    HashTable[i]->set_numofcopies(0);
    HashTable[i]->next = NULL;
  }
}

/*
 HashFunction creates an index depending on the book title.
 it iterates through each letter and adds the ascii value of the letters
 then modulas it by tablesize which is 251.
 @param title the title of a book.
 @return the hash index depending on the book title
*/
int hash::HashFunction(std::string title)
{
  int hash = 0;
  int index;

  for (unsigned long i = 0; i < title.length(); i++)
  {
    hash = (hash + (int)title[i]);
  }

  index = hash % TABLESIZE;

  return index;
}

/*
 AddBook adds an book object into the hashtable.
 if index is not empty (collusion) it makes a linked list type of structure (separate chaining).
 this happens since the Ptr points to the end node within the index and overides the NULL node with a book object.
 @param: book the book object being added to hash table.
*/
void hash::AddBook(Book book)
{
  int index = HashFunction(book.get_title()); //creates index of book object

  if (fnd(book.get_title()) == true) //checks if title exist
  {
    std::cout << "book already exist";
    return;
  }

  if (HashTable[index]->get_title() == "empty")         //checks if index of hash table contains "empty". 
  {                                                     // if it does it overides the node and makes the book object the first node of the index.
    HashTable[index]->set_title(book.get_title());
    HashTable[index]->set_authors(book.get_authors());
    HashTable[index]->set_ISBN(book.get_ISBN());
    HashTable[index]->set_numofcopies(book.get_numofcopies());
  }
  else //else it goes through the nodes within the index until it reaches last node and adds a new book object at the end of the index.
  {
    Book *Ptr = HashTable[index];
    Book *n = new Book();
    n->set_title(book.get_title());
    n->set_authors(book.get_authors());
    n->set_ISBN(book.get_ISBN());
    n->set_numofcopies(book.get_numofcopies());
    n->next = NULL;
    while (Ptr->next != NULL)
    {
      Ptr = Ptr->next;
    }
    Ptr->next = n;
  }
}

/*
 numin function: counts the number of nodes within the index.
 @param: book the book object being added to hash table.
*/
int hash::numin(int index)
{
  int count = 0;

  if (HashTable[index]->get_title() == "empty") // check if first node is empty
  {
    return count;
  }
  else  // goes through the index incrementing count by 1
  {
    count++;
    Book *Ptr = HashTable[index];
    while (Ptr->next != NULL)
    {

      count++;
      Ptr = Ptr->next;
    }
    return count;
  }
}

/*
 Printindex function: prints the detail of all elements within the index.
 @param: index the index within the hash table.
*/
void hash::Printindex(int index)
{
  std::string authors;
  std::string author;
  std::vector<std::string> author_array;
  Book *Ptr = HashTable[index];

  if (Ptr->get_title() == "empty") // checks if the index is empty. if it is informs the user
  {
    std::cout << "index " << index << " is empty \n";
  }
  else    // goes through the index printing the Book details
  {
    std::cout << "index " << index << " contains\n";
    while (Ptr != NULL)
    {
      authors = Ptr->get_authors();
      std::stringstream ss(authors);
      while (getline(ss, author, ';'))
      {
        author_array.push_back(author);
      }
      std::cout << "------------------\n";
      std::cout << Ptr->get_title() << "\n";
      for (unsigned long i = 0; i < author_array.size(); i++)
      {
        std::cout << author_array[i] << "\n";
      }
      std::cout << Ptr->get_ISBN() << "\n";
      std::cout << Ptr->get_numofcopies() << "\n";
      std::cout << "------------------\n";
      Ptr = Ptr->next;
    }
  }
}

/*
 Prntindx function: checks if an index is "empty" or not.
 @param: index the index within the hash table.
 @returns: if index contains "empty" @returns true else @returns false
*/
bool hash::Prntindx(int index)
{
  Book *Ptr = HashTable[index];

  if (Ptr->get_title() == "empty")
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*
 Find function: searches for title of book within the index nodes by going through the index.
 this happens since the Ptr is updated to the next node within the index within the while loop.
 if title matches the book object title within the index it prints the details of the book object.
 @param title the title of a book.
*/
void hash::Find(std::string title)
{
  int index = HashFunction(title); //finds the index of title 
  bool foundname = false;
  std::string authors;
  std::string author;
  std::vector<std::string> author_array;
  std::string ISBN;
  int numofcopies;
  Book *Ptr = HashTable[index]; //points to first item in bucket of that index

  while (Ptr != NULL) // goes through the nodes within the index.
  {
    if (Ptr->get_title() == title) //if the book object title matches the title being searched then the book is found within the hash table.
    {
      foundname = true;
      authors = Ptr->get_authors();
      ISBN = Ptr->get_ISBN();
      numofcopies = Ptr->get_numofcopies();
    }
    Ptr = Ptr->next; //points to next item in list
  }

  std::stringstream ss(authors);
  while (getline(ss, author, ';')) // separates the authors and puts it within an array.
  {
    author_array.push_back(author);
  }
  if (foundname == true) // prints detail of book if book was found in hash table.
  {
    std::cout << "Title = " << title << "\n";
    for (unsigned long i = 0; i < author_array.size(); i++)
    {
      std::cout << "author " << i + 1 << " = " << author_array[i] << "\n";
    }
    std::cout << "ISBN = " << ISBN << "\n";
    std::cout << "numofcopies = " << numofcopies << "\n";
  }
  else // book was not found in hash table.
  {
    std::cout << title << " not found in the library \n";
  }
}

/*
 Fnd function: searches for title of book within the index nodes by going through the index.
 this happens since the Ptr is updated to the next node within the index in the while loop.
 @returns: if title matches the book object title (within the index) it returns true else returns false.
 @param: title the title of a book.
*/
bool hash::fnd(std::string title)
{
  int index = HashFunction(title);
  Book *Ptr = HashTable[index];

  while (Ptr != NULL)
  {
    if (Ptr->get_title() == title)
    {
      return true;
    }
    Ptr = Ptr->next;
  }
  return false;
}

/*
 RemoveBook function: removes the node in which the book object is in. 
 this occurs if the title matches the book object title.
 it checks if the node is the first node, last node or in between (within the index).
 @param title the title of a book being removed.
*/
void hash::RemoveBook(std::string title)
{
  int index = HashFunction(title); // finds the index for the title to be removed

  Book *delPtr; 
  Book *Ptr1; 
  Book *Ptr2; 
  int stock;

//case 1: bucket is empty means no item in hashtable with that index
  if (HashTable[index]->get_title() == "empty") 
  {
    std::cout << title << " not found in library\n";
  }
  //case 2: only one item in bucket and that item has index with matching name
  else if (HashTable[index]->get_title() == title && HashTable[index]->next == NULL)
  {
    if (HashTable[index]->get_numofcopies() > 1)
    {
      std::cout << "\nEnter the number of books you want to remove: ";
      std::cin >> stock;

      if (stock < 1 || stock > HashTable[index]->get_numofcopies())
      {
        std::cout << "\nEnter a valid number.incorrect input.\n";
        return;
      }

      if (std::cin.fail() || std::cin.get() != '\n')
      { 
        std::cin.clear();                                                   // reset failbit
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
        std::cout << "\nincorrect input. Enter a valid number\n";
      }
      HashTable[index]->set_numofcopies(HashTable[index]->get_numofcopies() - stock);
      if (HashTable[index]->get_numofcopies() == 0)
      {
        HashTable[index]->set_title("empty");
        HashTable[index]->set_authors("empty");
        HashTable[index]->set_ISBN("empty");
        HashTable[index]->set_numofcopies(0);
        std::cout << title << " removed \n";
      }
      else
      {
        std::cout << "\nTitle: " << HashTable[index]->get_title() << "\n";
        std::cout << "\nquantity: " << HashTable[index]->get_numofcopies() << "\n";
      }
    }
    else
    {
      HashTable[index]->set_title("empty");
      HashTable[index]->set_authors("empty");
      HashTable[index]->set_ISBN("empty");
      HashTable[index]->set_numofcopies(0);
      std::cout << title << " removed \n";
    }
  }
  // case 3: match is in first item in bucket but there are more items in bucket
  else if (HashTable[index]->get_title() == title)
  {
    if (HashTable[index]->get_numofcopies() > 1)
    {
      std::cout << "\nEnter the number of books you want to remove: ";
      std::cin >> stock;

      if (stock < 1 || stock > HashTable[index]->get_numofcopies())
      {
        std::cout << "\nEnter a valid number.incorrect input.\n";
        return;
      }

      if (std::cin.fail() || std::cin.get() != '\n')
      { 
        std::cin.clear();                                                   // reset failbit
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
        std::cout << "\nincorrect input. Enter a valid number\n";
      }
      HashTable[index]->set_numofcopies(HashTable[index]->get_numofcopies() - stock);
      if (HashTable[index]->get_numofcopies() == 0)
      {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;   // delete the node

        std::cout << title << " removed \n";
      }
      else
      {
        std::cout << "\nTitle: " << HashTable[index]->get_title() << "\n";
        std::cout << "\nquantity: " << HashTable[index]->get_numofcopies() << "\n";
      }
    }
    else
    {

      delPtr = HashTable[index];
      HashTable[index] = HashTable[index]->next;
      delete delPtr;  // delete the node

      std::cout << title << " removed \n";
    }
  }
  // case 4 bucket contains item but first item is not match
  else
  {
    Ptr1 = HashTable[index]->next;
    Ptr2 = HashTable[index]; // Ptr2 trails one item behind Ptr1 until we find match

    while (Ptr1 != NULL && Ptr1->get_title() != title)
    {
      Ptr2 = Ptr1;           // Ptr2 moves up 1 item in list
      Ptr1 = Ptr1->next;     // and Ptr1 does the same
    }
    if (Ptr1 == NULL)  // means theres no match cos Ptr1 went through the list and didn't find a match
    {
      std::cout << title << " not found\n";
    }
    else // if we reach this else statement it means we found a match
    {
      delPtr = Ptr1; // points to item we want to remove

      if (delPtr->get_numofcopies() > 1)
      {
        std::cout << "\nEnter the number of books you want to remove: ";
        std::cin >> stock;

        if (std::cin.fail() || std::cin.get() != '\n')
        { 
          std::cin.clear();                                                   // reset failbit
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
          std::cout << "\nincorrect input. Enter a valid number\n";
          // std::cin.ignore();
          return;
        }

        if (stock < 1 || stock > delPtr->get_numofcopies())
        {
          std::cout << "\nEnter a valid number.incorrect input.\n";
          return;
        }

        delPtr->set_numofcopies(delPtr->get_numofcopies() - stock);
        if (delPtr->get_numofcopies() == 0)
        {
          Ptr1 = Ptr1->next; // this equals to the next item from the Ptr1 that will be deleted
          Ptr2->next = Ptr1; // this now points to the new item Ptr1 is pointing to
          delete delPtr; // remove item where Ptr1 was pointing to originally
          std::cout << title << " removed \n";
        }
        else
        {
          std::cout << "\nTitle: " << delPtr->get_title() << "\n";
          std::cout << "\nquantity: " << delPtr->get_numofcopies() << "\n";
        }
      }
      else
      {
        Ptr1 = Ptr1->next;
        Ptr2->next = Ptr1;
        delete delPtr;
        std::cout << title << " removed \n";
      }
    }
  }
}

/*
destructor which deletes all indexes within the hash table
*/
hash::~hash()
{
  Book *Ptr;
  for (int i = 0; i < TABLESIZE; i++)
  {
    while (HashTable[i] != NULL)
    {
      Ptr = HashTable[i];
      HashTable[i] = HashTable[i]->next;
      delete Ptr;
    }
  }
}
