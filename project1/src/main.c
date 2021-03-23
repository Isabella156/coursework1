#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/interface.h"

User* headPtrUser;


char searchMenu[] = "Please choose an option:\n1) Find books by title\n2) Find books \
by author\n3) Find books by year\n4) Return to previous menu\n Option:";

char noSuchBook[] = "Sorry, no such book.\n";

char firstPrompt[] = "Please choose an option:\n1) Register an account\n2) Login\n\
3) Search for books\n4) Display all books\n5) Quit\n Option:";

char librarianPrompt[] = "Please choose an option:\n1) Add a book\n2) Remove a book\n\
3) Search for a book\n4) Display all books\n5)Log out\n Option:";

char invalidOption[] = "Sorry, the option you entered was invalid, please try again.\n\n";

char userPrompt[] = "Please enter an option:\n1) Borrow a book\n2) Return a book\n\
3) Search for book\n4) Display all books\n5) Log out\n Option: ";
char answer[50];
char answer2[50];

// a head pointer that points to the head node of the user
User *headPtrUser;

// declare a libaray administrator
User* librarian;

// a head pointer that points to the head node of the book
Book *headPtrBook;

// a head
BorrowBook* headPtrBorrowBook;
int main(void){
    interface();
}