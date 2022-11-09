/*
 testBook.cpp
 Student ID: M00737296
 Created: 1/4/2021
 Updated: 28/4/2021
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hashtable.h"
#include <iostream>

TEST_CASE("Adding Books to the hashtable", "[Hash]")
{
  hash Hashy;
  SECTION("Testing when adding the book, it is found within the hashtable")
  {
    Book book1 = Book("big world", "bob", "978121212456", 2);
    Book book2 = Book("small wolrd", "tom", "9786545436754", 2);
    Book book3 = Book("maybe", "mat;bob;pat", "9787785089456", 2);

    Hashy.AddBook(book1);
    Hashy.AddBook(book2);
    Hashy.AddBook(book3);

    REQUIRE(Hashy.fnd("big world")); // fnd() function checks if the title "big world" is within the hashtable
    REQUIRE(Hashy.fnd("small wolrd"));
    REQUIRE(Hashy.fnd("maybe"));
  }

  SECTION("Adding a node at the beginning of an index")
  {
    Book book4 = Book("Core Python Programming", "bod", "978121212146", 2);

    REQUIRE(Hashy.Prntindx(Hashy.HashFunction("Core Python Programming"))); // Prntindx function checks if index is empty

    Hashy.AddBook(book4);
  }

  SECTION("Adding a node at the end of index resulting in a seperate chaining within the hashtable")
  {
    Book book4 = Book("Core Python Programming", "bod", "978121212146", 2);
    Book book5 = Book("Nature-inspired Metaheuristic Algorithms", "tommy", "9786545436224", 2);

    REQUIRE(Hashy.HashFunction(book4.get_title()) == Hashy.HashFunction(book5.get_title())); // checks if both book objects has the same index

    Hashy.AddBook(book4);
    Hashy.AddBook(book5);
    std::cout << "ADD TEST DONE\n";
    std::cout << "----------------------------------------------------------\n";
  }
}

TEST_CASE("Hash Remove Book", "[Hash]")
{
  hash Hashy;

  SECTION("Testing when removing the book, the book is not found within the hashtable")
  {
    std::cout << "Testing when removing the book, the book is not found within the hashtable\n";
    Book book1 = Book("big world", "bob", "978121212112", 2);
    Book book2 = Book("small wolrd", "tom", "9786545436754", 1);
    Book book3 = Book("maybe", "mat;bob;pat", "9787785089456", 2);

    Hashy.AddBook(book1);
    Hashy.AddBook(book2);
    Hashy.AddBook(book3);

    Hashy.RemoveBook("small wolrd");
    std::cout << "\n";

    REQUIRE(Hashy.fnd("big world"));            // fnd() function checks if the title "big world" is within the hashtable
    REQUIRE(Hashy.fnd("small wolrd") == false); // we removed "small world" so it should equal fales
    REQUIRE(Hashy.fnd("maybe"));
  }

  SECTION("removing a node at the beginning of an index")
  {
    std::cout << "removing a node at the beginning of an index\n";
    Book book4 = Book("Core Python Programming", "bod", "978121212146", 1);

    Hashy.AddBook(book4);

    REQUIRE(Hashy.Prntindx(Hashy.HashFunction("Core Python Programming")) == false); //checks if index is empty

    Hashy.RemoveBook("Core Python Programming");
    std::cout << "\n";
  }

  SECTION("Removing a node at the end of index")
  {
    std::cout << "Removing a node at the end of index\n";
    Book book4 = Book("Core Python Programming", "bod", "978121212146", 1);
    Book book5 = Book("Nature-inspired Metaheuristic Algorithms", "tommy", "9786545436224", 1);

    Hashy.AddBook(book4);
    Hashy.AddBook(book5);

    REQUIRE(Hashy.HashFunction(book4.get_title()) == Hashy.HashFunction(book5.get_title())); //check if both book object index are the same

    Hashy.Printindex(Hashy.HashFunction(book4.get_title()));                                 //Printindex function prints the elements in the index
    std::cout << "\n";
    Hashy.RemoveBook("Nature-inspired Metaheuristic Algorithms");
    std::cout << "\n";
    std::cout << "after remove function:-\n";
    Hashy.Printindex(Hashy.HashFunction(book4.get_title()));
    std::cout << "REMOVE TEST DONE\n";
    std::cout << "----------------------------------------------------------\n";
  }
}

TEST_CASE("Hash Search Book", "[Hash]")
{
  hash Hashy;
  SECTION("Search a node at the end of index")
  {
    std::cout << "searched for the following:-\n";
    Book book4 = Book("Core Python Programming", "bod", "978121212146", 1);
    Book book5 = Book("Nature-inspired Metaheuristic Algorithms", "tommy", "9786545436224", 1);

    Hashy.AddBook(book4);
    Hashy.AddBook(book5);
    
    REQUIRE(Hashy.HashFunction(book4.get_title()) == Hashy.HashFunction(book5.get_title())); //check if both book object index are the same

    std::cout << "\n";
    Hashy.Find("Nature-inspired Metaheuristic Algorithms"); // searching after adding it. this will print out the details
  }

  SECTION("searching a node at the beginning of an index")
  {
    Book book4 = Book("Core Python Programming", "bod", "978121212146", 1);
    Hashy.AddBook(book4);
    
    REQUIRE(Hashy.numin(Hashy.HashFunction("Core Python Programming")) == 1); //numin function goes through hashtable and checks number of index 

    Hashy.Find("Core Python Programming"); 
    std::cout << "\n";
  }

  SECTION("Testing when searching for the book, it is found within the hashtable")
  {
    Book book1 = Book("big world", "bob", "978121212112", 2);
    Book book2 = Book("small wolrd", "tom", "9786545436754", 2);
    Book book3 = Book("maybe", "mat;bob;pat", "9787785089456", 2);

    Hashy.AddBook(book1);
    Hashy.AddBook(book2);
    Hashy.AddBook(book3);

    REQUIRE(Hashy.fnd("big world"));
    REQUIRE(Hashy.fnd("small wolrd"));
    REQUIRE(Hashy.fnd("maybe"));

    Hashy.Find("big world");
    std::cout << "\n";
    Hashy.Find("small wolrd");
    std::cout << "\n";
    Hashy.Find("maybe");
    std::cout << "\n";

    std::cout << "SEARCH TEST DONE\n";
    std::cout << "----------------------------------------------------------\n";
  }
}
