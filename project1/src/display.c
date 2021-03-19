#include <stdio.h>
#include "../include/display.h"

// function to display the book array
void displayBookArray(BookArray bookArray){
    // declare a book pointer to traverse the linked list for books
    Book *bookPtr = bookArray.array->next;
    printf("ID    Title                                                 Authors\
                                            year  copies\n");
    while(bookPtr != NULL){
        printf("%-2d    %-50s    %-50s ",bookPtr->id, bookPtr->title, bookPtr->authors);
        printf("%-4d  %-2d\n", bookPtr->year, bookPtr->copies);
        bookPtr = bookPtr->next;
    }
}

// function to display all books
void displayBooks(){
    Book* bookPtr = headPtrBook->next;
    printf("ID    Title                                                 Authors\
                                            year  copies\n");
    
    while(bookPtr != NULL){
        printf("%-2u    %-50s    %-50s ",bookPtr->id, bookPtr->title, bookPtr->authors);
        printf("%-4u  %-2u\n", bookPtr->year, bookPtr->copies);
        bookPtr = bookPtr->next;
    }
}

// function to display all borrow books
void displayBorrowBooks(User user){
    printf("ID    Title                                                 Authors\
                                               year\n");
    BorrowBook* borrowBookPtr = user.borrowBook->next;
    while(borrowBookPtr != NULL){
        printf("%-2u    %-50s    %-50s    ",borrowBookPtr->id, borrowBookPtr->title, borrowBookPtr->authors);
        printf("%-4u\n", borrowBookPtr->year);
        borrowBookPtr = borrowBookPtr->next;
    }
}