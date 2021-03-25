#ifndef DISPLAY_GUARD__H 
#define DISPLAY_GUARD__H

#include <stdio.h>
#include "../include/global.h"

extern Book* headPtrBook;

// function to display all borrow books
void displayBorrowBooks(User user);
// function to display all books
void displayBooks();
// function to display the book array
void displayBookArray(BookArray bookArray);

#endif