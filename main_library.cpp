/*
 main_library.cpp
 Student ID: M00737296
 Created: 1/4/2021
 Updated: 28/4/2021
*/

#include "hashtable.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{

  if (argc < 2) // system takes in 2 arguments if not it informs the user and exits.
  {
    std::cerr << "Expected 1 argument: " << argv[0]
              << " <DataFile>\n";
    exit(1);
  }

  hash Hashy;

  std::string title = "";
  std::string titl, author, ISBN, amount_string;
  std::string line;
  int amount;
  std::vector<long> isbn_num;
  std::vector<std::string> title_exist;
  std::ifstream inFile(argv[1]); // file to read from

  if (!inFile.is_open()) //if file (2nd argument) can't open informs the user
  {
    std::cout << "File Fail to open" << std::endl;
    exit(0);
  }


  while (getline(inFile, line)) // while loop which reads line by line of text file
  { 
    std::stringstream ss(line);
    getline(ss, titl, '\t');   // reads anyting after "\t" and stores it in "titl"
    getline(ss, author, '\t'); // reads anyting after "\t" and stores it in "author"
    getline(ss, ISBN, '\t');  // reads anyting after "\t" and stores it in "ISBN"
    getline(ss, amount_string, '\t'); // reads anyting after "|" and stores it in "amount_string"
    amount = stoi(amount_string);     // converts amount_string into an int
  
    isbn_num.push_back(stol(ISBN)); // array of ISBN
    title_exist.push_back(titl);    // array of titles

    Book b = Book(titl, author, ISBN, amount); // createing book object with information from file
    Hashy.AddBook(b); //adding book object to the hash table
  }
  inFile.close();

  std::string choice;
  std::string input;
  int val_choice;
  bool n = true;
  bool t = false;

  do
  {
    std::string name = "";
    std::string writer = "";
    std::string w = "";
    int numA;
    std::string num = "";
    int q = 0;
    system("clear"); // clears system for every user choice so terminal is clean.

    // prints user menu
    std::cout << "--------------------------------------\n";
    std::cout << "WELCOME TO THE LIBRARY SYSTEM\n";
    std::cout << "--------------------------------------\n";
    std::cout << "ENTER YOUR CHOICE:\n";
    std::cout << "\n1. Add a new Book:\n";
    std::cout << "\n2. Remove a Book:\n";
    std::cout << "\n3. Search for a Book:\n";
    std::cout << "\n4. Quit \n";
    std::cout << "--------------------------------------\n";
    std::cout << "INPUT: ";
    std::cin >> choice;
    std::cout << "-*************************************-\n";

    // validates user choice
    if (!(choice == "1" || choice == "2" || choice == "3" || choice == "4"))
    {
      std::cout << "Choose options from menu.\n";
      // std::cin >> choice;
      std::cout << "\nEnter any character to return to menu\n";
        std::cin.ignore();
        getline(std::cin, input); // reads the line in which user entered (not just one word)
        continue;
    }

    val_choice = stoi(choice); // change string to int

    switch (val_choice)
    {
    case 1:
    {
      std::cin.ignore();

      std::cout << "\nADD A BOOK:\n";

      std::cout << "\nEnter Book name: ";
      getline(std::cin, name); // reads the line in which user entered (not just one word)

      if (name == "") // validates if user input a name
      {
        std::cout << "\nEnter name for the Book. ";
        std::cout << "\nEnter any character to return to menu\n";
        getline(std::cin, input); // reads the line in which user entered (not just one word)
        break;
      }

      for (unsigned long i = 0; i < title_exist.size(); i++) // goes through the array of titles and validate if a title already exist
      {
        if (name == title_exist[i])
        {
          std::cout << name << " already exist";
          std::cout << "\nEnter any character to return to menu\n";
          getline(std::cin, input); // reads the line in which user entered (not just one word)
          t = true;
          break;
        }
      }

      if (t == true)
      {
        t=false;
        n = false;
        break;
      }

      std::cout << "\nEnter number of Book authors: ";
      std::cin >> numA;
      if (std::cin.fail() || std::cin.get() != '\n')
      {                                                                     // validation of user input (if it matches the type int )
        std::cin.clear();                                                   // reset cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
        std::cout << "\nEnter a positive whole number.incorrect input.\n";
        std::cout << "\nEnter any character to return to menu\n";
        getline(std::cin, input); // reads the line in which user entered (not just one word)
        break;
      }
      if (numA < 1) // validates if user input a positive number
      {
        std::cout << "\nEnter a positive number.incorrect input.\n";
        std::cout << "\nEnter any character to return to menu\n";
        getline(std::cin, input); // reads the line in which user entered (not just one word)
        break;
      }
      for (int i = 0; i < numA; i++)// goes through number of book authors and allows the user to input authors name
      {
        std::cout << "\nEnter (one) author full name: ";
        getline(std::cin, w); // reads the line in which user entered (not just one word)
        if (w == "") // validate if user input a name
        {
          t = true;
          std::cout << "\nEnter name of author.\n";
          std::cout << "\nEnter any character to return to menu\n";
          getline(std::cin, input); // reads the line in which user entered (not just one word)
          break;
        }
        writer = writer + w + ";"; // create a string in which the string can easily split authors
        
      }
      if (t == true)
      {
        writer = "";
        t = false;
        break;
      }
      t = false;

      std::cout << "\nEnter 10 digits for Book ISBN: ";

      std::cout << "978";
      std::cin >> num;
      if (num.size() > 10 || num.size() < 10 || num.find_first_not_of("0123456789") == std::string::npos != true) //validates if user input correct number
      {
        std::cout << "please enter 10 digits";
        std::cout << "\nEnter any character to return to menu\n";
        std::cin.ignore();
        getline(std::cin, input); // reads the line in which user entered (not just one word)
        break;
      }

      for (unsigned long i = 0; i < isbn_num.size(); i++) // goes through the arrays of ISBN to check if user inputted exitsing ISBN
      {
        if (stol("978" + num) == isbn_num[i])
        {
          std::cout << stol("978" + num) << "ISBN already exist choose another";
          std::cout << "\nEnter any character to return to menu\n";
          std::cin.ignore();
          getline(std::cin, input); // reads the line in which user entered (not just one word)
          t = true;
          break;
        }
      }

      if (t == true)
      {
        t = false;
        break;
      }

      std::cout << "\nEnter Book Quantity: ";
      std::cin >> q;
      if (std::cin.fail() || std::cin.get() != '\n')
      {                                                                     // validation of user input (if it matches the type int )
        std::cin.clear();                                                   // reset cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
        std::cout << "\nEnter a positive whole number.incorrect input.\n";
        std::cout << "\nEnter any character to return to menu\n";
        getline(std::cin, input); // reads the line in which user entered (not just one word)
        break;
      }
      if (q < 1) // validates if user inputted positive number
      {
        std::cout << "\nEnter a positive number.incorrect input.\n";
        std::cout << "\nEnter any character to return to menu\n";
        getline(std::cin, input); // reads the line in which user entered (not just one word)
        break;
      }

      Book bo = Book(name, writer, "978" + num, q); // create a book object with user inputs
      isbn_num.push_back(stol(bo.get_ISBN())); // adding ISBN to array
      title_exist.push_back(bo.get_title()); // adding title to array

      Hashy.AddBook(bo); // adding book (user created) to the hash table
      std::cout << "\nBook has been Added.\n";
      std::cout << "\nEnter any character to return to menu\n";
      getline(std::cin, input); // reads the line in which user entered (not just one word)
      n = true;
      break;
    }

    case 2:
    {
      std::cin.ignore();

      std::cout << "\nREMOVE A BOOK:\n";

      std::cout << "\nEnter Book name: ";
      getline(std::cin, name); // reads the line in which user entered (not just one word)
      if (name == "") // validates if user inpuuted name
      {
        std::cout << "\nEnter name for the Book.\n";
        std::cout << "\nEnter any character to return to menu\n";

        getline(std::cin, input); // reads the line in which user entered (not just one word)
        break;
      }

      Hashy.RemoveBook(name); // call RemoveBook function to remove the book with "name" (the user inputted).

      if(Hashy.fnd(name)==false){
      std::vector<std::string>::iterator result = find(title_exist.begin(), title_exist.end(), name);
    // If result points to game_list.end() it couldn't find the game so
    // we can't delete it. If it isn't it delete the game.
    if (result == title_exist.end())
        std::cout << "That game is not in there!" << std::endl;
    else
        title_exist.erase(result);
      }
      std::cout << "\nEnter any character to return to menu\n";
      getline(std::cin, input); // reads the line in which user entered (not just one word)
      break;
    }

    case 3:
    {
      std::cin.ignore();

      std::cout << "\nSEARCH A BOOK:\n";
      std::cout << "\nEnter Book name: ";
      getline(std::cin, name); // reads the line in which user entered (not just one word)

      if (name == "") // validates if user inpuuted name
      {
        std::cout << "\nEnter name for the Book.\n";
        std::cout << "\nEnter any character to return to menu\n";
        getline(std::cin, input); // reads the line in which user entered (not just one word)
        break;
      }

      Hashy.Find(name); // searches for the booke name in which the user inputted
      std::cout << "\nEnter any character to return to menu\n";
      getline(std::cin, input); // reads the line in which user entered (not just one word)
      n = true;
      break;
    }

    case 4:
    {
      std::cout << "SYSTEM IS CLOSED\n";
      break;
    }

    default:
    {
      std::cout << "choose from menu."; // validation of user choice
      std::cout << "\nEnter any character to return to menu\n";
      getline(std::cin, input); // reads the line in which user entered (not just one word)
      break;
    }
    }

  } while (val_choice != 4); // system (loop) runs until user inputs "4"

  return 0;
}


