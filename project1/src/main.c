#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/interface.h"

User* headPtrUser;

BorrowBook* headPtrBorrowBook;

const char searchMenu[] = "Please choose an option:\n1) Find books by title\n2) Find books \
by author\n3) Find books by year\n4) Return to previous menu\n Option:";

const char noSuchBook[] = "Sorry, no such book.\n";

// a head pointer that points to the head node of the user
User *headPtrUser;

// a head pointer that points to the head node of the user
BorrowBook *headPtrBorrowBook;

// declare a libaray administrator
User librarian;

// a head pointer that points to the head node of the book
Book *headPtrBook;
int main(void){
    int i = 1;
    printf("lala");
    interface();
}