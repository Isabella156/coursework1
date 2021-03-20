#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H

#include <string.h>
#include "global.h"



int store_books(const char* filename);
int load_books(const char* filename);
int add_book(char bookTitle[], char bookAuthors[], unsigned int bookCopies, unsigned int bookYear);
int remove_book(char title[], char authors[], unsigned int copies, unsigned int year);
BookArray find_book_by_title (const char *title);
BookArray find_book_by_author (const char *author);
BookArray find_book_by_year (unsigned int year);
Book* findBookByID (unsigned int id);
void borrowBook(Book *book, User user);
int checkSameBorrowBook(unsigned int id, User user);
BorrowBook* checkReturnBook(unsigned int id, User user);
void returnBook(BorrowBook* returnBook, User user);
void searchForBook(char myAnswer[50]);
int checkUsername(char *name);
void storeUsername(char username[], char password[]);
int storeUserInFile(const char* filename);
int loadUser(const char* filename);
void displayBookArray(BookArray bookArray);
#endif