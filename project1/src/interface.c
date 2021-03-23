#include "../include/interface.h"



int interface(){
     // declaration of book
    headPtrBook = (Book*)malloc(sizeof(Book));
    headPtrBook->id = 0;
    headPtrBook->title = NULL;
    headPtrBook->authors = NULL;
    headPtrBook->year = 0;
    headPtrBook->copies = 0;
    headPtrBook->next = NULL;



    // declaration of library administrator (librarian)
    User* librarian = (User*)malloc(sizeof(User));
    char string[10] = "librarian";
    librarian->username = (char*)malloc(sizeof(string));
    librarian->password = (char*)malloc(sizeof(string));
    librarian->username = string;
    librarian->password = string;
    librarian->borrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
    librarian->borrowBook->authors = NULL;
    librarian->borrowBook->id = 0;
    librarian->borrowBook->title = NULL;
    librarian->borrowBook->year = 0;
    librarian->borrowBook->next = NULL;
    librarian->next = NULL;


    // declaration of users
    headPtrUser = (User*)malloc(sizeof(User));
    headPtrUser->username = NULL;
    headPtrUser->password = NULL;
    headPtrUser->borrowBook = NULL;
    headPtrUser->next = librarian;

    // storeUserInFile();
    load_books();
    loadUser();


    while(1){
        printf("%s",firstPrompt);
        scanf("%s",answer);

        // wrong option
        if(*answer < '1' || *answer > '5'){
            memset(answer,'\0',50);
            printf("%s",invalidOption);
            
            continue;
            // register an account
        }else if(*answer == '1'){
            printf("Please enter a username: ");
            scanf("%s",answer);
            if(checkUsername(answer)){
                printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
                printf("********************\n");
                continue;
            }
            printf("Please enter a password: ");
            memset(answer2,'\0',50);
            scanf("%s",answer2);
            storeUsername(answer, answer2);
            storeUserInFile();
            memset(answer,'\0',50);
            memset(answer2,'\0',50);
            printf("Registered successfully!\n");
            printf("********************\n");
            // login
        }else if(*answer == '2'){
            if(*answer == '5'){
                break;
            }
            getchar();
            printf("Please enter your username: ");
            scanf("%s",answer);
            if(checkUsername(answer)){
                printf("Please enter your password: ");
                scanf("%s",answer2);
                if(checkPassword(answer,answer2)){
                    // library administrator account
                    if(!strcmp(answer,"librarian")){
                        memset(answer,'\0',50);
                        memset(answer2,'\0',50);
                        while(1){
                            printf("(logged in as: librarian)\n");
                            printf("%s",librarianPrompt);
                            scanf("%s",answer);
                            // wrong option
                            if(*answer<'1' || *answer>'5'){
                                printf("%s",invalidOption);
                                printf("********************\n");
                                memset(answer,'\0',50);
                                continue;
                                // add a book
                            }else if(*answer == '1'){
                                getchar();
                                memset(answer,'\0',50);
                                char title[50], authors[50];
                                char copiesStr[10], yearStr[10];
                                memset(title,'\0',50);
                                memset(authors,'\0',50);
                                memset(copiesStr,'\0',10);
                                memset(yearStr,'\0',10);
                                unsigned int copies, year;
                                printf("Enter the title of the book you wish to add: ");
                                scanf("%[^\n]s",title);
                                getchar();
                                printf("Enter the author of the book you wish to add: ");
                                scanf("%[^\n]s",authors);
                                getchar();
                                printf("Enter the year of that the book you wish to add: ");
                                scanf("%[^\n]s",yearStr);
                                getchar();
                                if(yearStr[0]<='0' || yearStr[0]>'9'){
                                    printf("Invalid year!\n");
                                    printf("********************\n");
                                    continue;
                                }else if(atoi(yearStr) > 2021){
                                    printf("Invalid year!\n");
                                    printf("********************\n");
                                    continue;
                                }else{
                                    year = atoi(yearStr);
                                }
                                printf("Enter the number of book that you wish to add: ");
                                scanf("%[^\n]s",copiesStr);
                                if(copiesStr[0]<='0' || copiesStr[0]>'9'){
                                    printf("Invalid copies!\n");
                                    printf("********************\n");
                                    continue;
                                }else{
                                    copies = atoi(copiesStr);
                                }

                                if(!add_book(title, authors,copies,year)){
                                    printf("Books are added successfully!\n");
                                    printf("********************\n");
                                    store_books();
                                }else{
                                    printf("Failed to add books.\n");
                                    printf("********************\n");
                                }
                                // remove a book
                            }else if(*answer == '2'){
                                getchar();
                                memset(answer,'\0',50);
                                char title[50], authors[50];
                                char copiesStr[10], yearStr[10];
                                memset(title,'\0',50);
                                memset(authors,'\0',50);
                                memset(copiesStr,'\0',10);
                                memset(yearStr,'\0',10);
                                unsigned int copies, year;
                                printf("Enter the title of the book you wish to remove: ");
                                scanf("%[^\n]s",title);
                                getchar();
                                if(find_book_by_title(title).array->next == NULL){
                                    printf("Invalid book!\n");
                                    printf("********************\n");
                                    continue;
                                }
                                printf("Enter the author of the book you wish to remove: ");
                                scanf("%[^\n]s",authors);
                                getchar();
                                if(find_book_by_author(authors).array->next == NULL){
                                    printf("Invalid book!\n");
                                    printf("********************\n");
                                    continue;
                                }
                                printf("Enter the year of that the book you wish to remove: ");
                                scanf("%[^\n]s",yearStr);
                                getchar();
                                if(yearStr[0]<='0' || yearStr[0]>'9'){
                                    printf("Invalid year!\n");
                                    printf("********************\n");
                                    continue;
                                }else if(atoi(yearStr) > 2021){
                                    printf("Invalid year!\n");
                                    printf("********************\n");
                                    continue;
                                }else if(find_book_by_year(atoi(yearStr)).array->next == NULL){
                                    printf("Invalid year!\n");
                                    printf("********************\n");
                                    continue;
                                }else{
                                    year = atoi(yearStr);
                                }
                                if(remove_book(title, authors, year)){
                                    printf("Book was successfully removed!\n");
                                    printf("********************\n");
                                    store_books();
                                }else{
                                    printf("Failed to remove book\n");
                                    printf("********************\n");
                                }
                                //search for a book
                            }else if(*answer == '3'){
                                memset(answer,'\0',50);
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
                            memset(answer,'\0',50);
                            printf("(logged in as: %s)\n",currentUser.username);
                            printf("%s", userPrompt);
                            scanf("%s",answer);
                            // wrong option
                            if(*answer < '1' || *answer > '5'){
                                memset(answer,'\0',50);
                                printf("%s", invalidOption);
                                // borrow a book
                            }else if(*answer == '1'){
                                memset(answer,'\0',50);
                                printf("Enter the ID number of the book you wish to borrow: ");
                                scanf("%s",answer);
                                // the book can be borrowed the book exists in the library 
                                // and not borrowed by the same user
                                if(findBookByID(atoi(answer)) != NULL &&\
                                findBookByID(atoi(answer))->copies >= 0 && !checkSameBorrowBook\
                                (atoi(answer),currentUser)){
                                    borrowBook(findBookByID(atoi(answer)),currentUser);
                                    storeUserInFile();
                                    printf("You have successfully borrowed the book!\n");
                                    printf("********************\n");
                                    getchar();
                                    // the book is already borrowed
                                }else if(checkSameBorrowBook(atoi(answer),currentUser)){
                                    printf\
                                    ("Sorry, you already have a copy of this book on loan.\n");
                                    printf("********************\n");
                                    // the book can not be borrowd
                                }else{
                                    printf("Sorry, book is borrowed unsuccessfully.\n");
                                    printf("********************\n");
                                }
                                // return a book
                            }else if(*answer == '2'){
                                memset(answer,'\0',50);
                                if(currentUser.borrowBook->next == NULL){
                                    printf("You don't have any book to return!\n");
                                    printf("********************\n");
                                }else{
                                    printf("Below is the list of Books you are currently borrowing:\n");
                                    displayBorrowBooks(currentUser);
                                    printf("Enter the ID number of the book you wish to return: ");
                                    scanf("%s",answer);
                                    // the book can be returned: the book was borrowed before
                                    if(checkReturnBook(atoi(answer),currentUser) != NULL){
                                        returnBook(checkReturnBook(atoi(answer),currentUser),\
                                        currentUser);
                                        findBookByID(atoi(answer))->copies++;
                                        storeUserInFile();
                                        printf("Returned book successfully!.\n");
                                        printf("********************\n");
                                    }else{
                                        printf("Cannot return book!\n");
                                        printf("********************\n");
                                    }
                                }
                                // search for a book
                            }else if(*answer == '3'){
                                memset(answer,'\0',50);
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
                printf("********************\n");
                continue;
            }
            // search for a book
        }else if(*answer == '3'){
            searchForBook();
        }else if(*answer == '4'){
            displayBooks();
        }else if(*answer == '5'){
            printf("Thank you for using the library!\n");
            printf("********************\n");
            return 0;
        }
    }
    }
