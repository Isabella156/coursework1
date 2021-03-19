#include <stdio.h>
#include <string.h>
#include "../include/book_management.h"
#include "../include/display.h"
#include "../include/user.h"

int main(void){
    // declaration of users
    headPtrUser = (User*)malloc(sizeof(User));
    headPtrUser->next = &librarian;

    // declaration of borrow book
    headPtrBorrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
    headPtrBorrowBook->next = NULL;
    // declaration of library administrator (librarian)
    librarian.username = "librarian";
    librarian.password = "librarian";
    librarian.borrowBook = headPtrBorrowBook;
    librarian.borrowBook->next = NULL;
    librarian.next = NULL;

    load_books("books.txt");
    storeUserInFile("users.txt");
    loadUser("users.txt");

    while(1){
        printf("%s",firstPrompt);
        gets(answer);

        // wrong option
        if(*answer < '1' || *answer > '5'){
            nullifyString(answerPtr);
            printf("%s",invalidOption);
            
            continue;
            // register an account
        }else if(*answer == '1'){
            while(1){
                printf("Please enter a username: ");
                gets(answer);
                if(checkUsername(answer)){
                    printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
                    continue;
                }else{
                    break;
                }
            }
            printf("Please enter a password: ");
            gets(answer2);
            storeUsername(answer, answer2);
            storeUserInFile("users.txt");
            nullifyString(answerPtr);
            nullifyString(answerPtr2);
            // login
        }else if(*answer == '2'){
            while(1){
                if(*answer == '5'){
                    break;
                }
                printf("Please enter your username: ");
                gets(answer);
                if(checkUsername(answer)){
                    printf("Please enter your password: ");
                    gets(answer2);
                    if(checkPassword(answer,answer2)){
                        // library administrator account
                        if(!strcmp(answer,"librarian")){
                            nullifyString(answerPtr);
                            nullifyString(answerPtr2);
                            while(1){
                                printf("(logged in as: librarian)\n");
                                printf("%s",librarianPrompt);
                                gets(answer);
                                // wrong option
                                if(*answer<'1' || *answer>'5'){
                                    printf("%s",invalidOption);
                                    nullifyString(answerPtr);
                                    continue;
                                    // add a book
                                }else if(*answer == '1'){
                                    nullifyString(answerPtr);
                                    char title[50], authors[50];
                                    char copiesStr[10], yearStr[10];
                                    nullifyString(title);
                                    nullifyString(authors);
                                    nullifyString(copiesStr);
                                    nullifyString(yearStr);
                                    unsigned int copies, year;
                                    printf("Enter the title of the book you wish to add: ");
                                    gets(title);
                                    printf("Enter the author of the book you wish to add: ");
                                    gets(authors);
                                    printf("Enter the year of that the book you wish to add: ");
                                    gets(yearStr);
                                    if(yearStr[0]<='0' || yearStr[0]>'9'){
                                        printf("Invalid year!\n");
                                        continue;
                                    }else if(atoi(yearStr) > 2021){
                                        printf("Invalid year!\n");
                                        continue;
                                    }else{
                                        year = atoi(yearStr);
                                    }
                                    printf("Enter the number of book that you wish to add: ");
                                    gets(copiesStr);
                                    if(copiesStr[0]<='0' || copiesStr[0]>'9'){
                                        printf("Invalid copies!\n");
                                        continue;
                                    }else{
                                        copies = atoi(copiesStr);
                                    }
                                    getchar();
                                    if(!add_book(title, authors,copies,year)){
                                        printf("Books are added successfully!\n");
                                        store_books("books.txt");
                                    }else{
                                        printf("Failed to add books.\n");
                                    }
                                    // remove a book
                                }else if(*answer == '2'){
                                    nullifyString(answerPtr);
                                    char title[50], authors[50];
                                    char copiesStr[10], yearStr[10];
                                    nullifyString(title);
                                    nullifyString(authors);
                                    nullifyString(copiesStr);
                                    nullifyString(yearStr);
                                    unsigned int copies, year;
                                    printf("Enter the title of the book you wish to remove: ");
                                    gets(title);
                                    printf("Enter the author of the book you wish to remove: ");
                                    gets(authors);
                                    printf("Enter the year of that the book you wish to remove: ");
                                    gets(yearStr);
                                    if(yearStr[0]<='0' || yearStr[0]>'9'){
                                        printf("Invalid year!\n");
                                        continue;
                                    }else if(atoi(yearStr) > 2021){
                                        printf("Invalid year!\n");
                                        continue;
                                    }else{
                                        year = atoi(yearStr);
                                    }
                                    printf("Enter the number of book that you wish to remove: ");
                                    gets(copiesStr);
                                    if(copiesStr[0]<='0' || copiesStr[0]>'9'){
                                        printf("Invalid copies!\n");
                                        continue;
                                    }else{
                                        copies = atoi(copiesStr);
                                    }
                                    nullifyString(answerPtr);
                                    getchar();
                                    if(remove_book(title, authors, copies, year)){
                                        printf("Book was successfully removed!\n");
                                        store_books("books.txt");
                                    }else{
                                        printf("Failed to remove book\n");
                                    }
                                    //search for a book
                                }else if(*answer == '3'){
                                    nullifyString(answerPtr);
                                    searchForBook();
                                    // display all books
                                }else if(*answer == '4'){
                                    displayBooks();
                                    // log out
                                }else if(*answer == '5'){
                                    break;
                                }
                            }
                            // user account
                        }else{
                            User currentUser = *checkPassword(answer,answer2);
                            while(1){
                                printf("(logged in as: %s)\n",currentUser.username);
                                printf("%s", userPrompt);
                                nullifyString(answerPtr);
                                gets(answer);
                                // wrong option
                                if(*answer < '1' || *answer > '5'){
                                    nullifyString(answerPtr);
                                    printf("%s", invalidOption);
                                    // borrow a book
                                }else if(*answer == '1'){
                                    nullifyString(answerPtr);
                                    printf("Enter the ID number of the book you wish to borrow: ");
                                    gets(answer);
                                    // the book can be borrowed the book exists in the library 
                                    // and not borrowed by the same user
                                    if(findBookByID(atoi(answer)) != NULL &&\
                                    findBookByID(atoi(answer))->copies >= 0 && !checkSameBorrowBook\
                                    (atoi(answer),currentUser)){
                                        borrowBook(findBookByID(atoi(answer)),currentUser);
                                        printf("You have successfully borrowed the book!\n");
                                        // the book is already borrowed
                                    }else if(checkSameBorrowBook(atoi(answer),currentUser)){
                                        printf\
                                        ("Sorry, you already have a copy of this book on loan.\n");
                                        // the book can not be borrowd
                                    }else{
                                        printf("Sorry, book is borrowed unsuccessfully.\n");
                                    }
                                    // return a book
                                }else if(*answer == '2'){
                                    nullifyString(answerPtr);
                                    printf("Below is the list of Books you are currently borrowing:\n");
                                    displayBorrowBooks(currentUser);
                                    printf("Enter the ID number of the book you wish to return: ");
                                    gets(answer);
                                    // the book can be returned: the book was borrowed before
                                    if(checkReturnBook(atoi(answer),currentUser) != NULL){
                                        returnBook(checkReturnBook(atoi(answer),currentUser),\
                                        currentUser);
                                        printf("Returned book successfully!.\n");
                                    }else{
                                        printf("Cannot return book!\n");
                                    }
                                    // search for a book
                                }else if(*answer == '3'){
                                    nullifyString(answerPtr);
                                    searchForBook();
                                }else if(*answer == '4'){
                                    displayBooks();
                                }else if (*answer == '5'){
                                    printf("Logging out...\n");
                                    break;
                                }
                            }
                        }
                    }
                }else{
                    printf("Sorry, the username does not exist.\n");
                    continue;
                }
            }
            // search for a book
        }else if(*answer == '3'){
            searchForBook();
        }else if(*answer == '4'){
            displayBooks();
        }else if(*answer == '5'){
            printf("Thank you for using the library!\n");
            return 0;
        }
    }
}