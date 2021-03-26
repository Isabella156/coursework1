
#include "../include/book_management.h"
#include "../include/display.h"

int store_books(){
    FILE *file;
    file = fopen("books.txt", "w");
    Book* bookPtr = headPtrBook->next;
    char title[50];
    char authors[50];

    if(!file){
        printf("Error in handling files!\n");
        return -1;
    }

    while(bookPtr){
        strcpy(title,bookPtr->title);
        strcpy(authors,bookPtr->authors);
        // output the data of the node to the file books.txt
        if(bookPtr->next == NULL){
            fprintf(file,"%u\n%s\n%s\n%u\n%u",bookPtr->id, title, authors,\
        bookPtr->year, bookPtr->copies);
        }else{
            fprintf(file,"%u\n%s\n%s\n%u\n%u\n\n",bookPtr->id, title, authors,\
        bookPtr->year, bookPtr->copies);
        }
        memset(title,'\0',sizeof(title));
        memset(authors,'\0',sizeof(authors));
        bookPtr = bookPtr->next;
    }
    fclose(file);

    return 0;
}

int load_books(){
    Book* bookPtr;
    Book* newBook;
    bookPtr = headPtrBook;
    FILE *file;
    file = fopen("books.txt", "r");
    if (!file) {
        printf("Error in handling files!\n");
        return -1;
	}
    char str[50];
    while(!feof(file)){
        newBook = (Book*)malloc(sizeof(Book));
        
        fscanf(file,"%u",&newBook->id);
        fgetc(file);

        fscanf(file,"%[^\n]s",str);
        newBook->title = (char*)malloc(sizeof(str));
        strcpy(newBook->title,str);
        memset(str,'\0',strlen(str));
        fgetc(file);

        fscanf(file,"%[^\n]s",str);
        newBook->authors = (char*)malloc(sizeof(str));
        strcpy(newBook->authors,str);
        memset(str,'\0',strlen(str));
        fgetc(file);

        fscanf(file,"%u",&newBook->year);
        fgetc(file);

        fscanf(file,"%u",&newBook->copies);
        newBook->initialCopies = newBook->copies;
        fgetc(file);
        bookPtr->next = newBook;
        bookPtr = newBook;
    }
    bookPtr->next = NULL;
    fclose(file);

    return 0;
}

int add_book(char bookTitle[], char bookAuthors[], unsigned int bookCopies, unsigned int bookYear){
    if(bookCopies <= 0){
        return -1;
    }else{
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->title = (char*)malloc(50);
    strcpy(newBook->title, bookTitle);
    newBook->authors = (char*)malloc(50);
    strcpy(newBook->authors, bookAuthors);
    newBook->copies = bookCopies;
    newBook->initialCopies = bookCopies;
    newBook->year = bookYear;
    newBook->next = NULL;

    Book* bookPtr = headPtrBook->next;
    while(bookPtr->next != NULL){
        bookPtr = bookPtr->next;
    }
    newBook->id = (bookPtr->id)+1;
    bookPtr->next = newBook;

    return 0;
    }

}

int remove_book(char title[], char authors[], unsigned int year){
    Book* bookPtr = headPtrBook;
    while(bookPtr->next != NULL){
        if(!strcmp (bookPtr->next->title,title) && !strcmp(bookPtr->next->authors,authors) && \
         bookPtr->next->year == year){
            break;
        }
        bookPtr = bookPtr->next;
    }    
    // book can not be removed
    if(bookPtr->next == NULL || bookPtr->copies != bookPtr->initialCopies){
        return 0;
    // book can be removed
    }else{
        bookPtr->next = bookPtr->next->next;
        bookPtr = bookPtr->next;
        while(bookPtr != NULL){
            bookPtr->id--;
            bookPtr = bookPtr->next;
        }
        return 1;
    }
}

BookArray find_book_by_title (const char *title){
    char str[50];
    memset(str,'\0',50);
    // declare a BookArray
    BookArray titleArray;
    // initialize the book array
    titleArray.array = (Book*)malloc(sizeof(Book));
    titleArray.length = 0;

    Book* arrayPtr = titleArray.array;

    Book* bookPtr = headPtrBook->next;
    while(bookPtr != NULL){
        if(strstr(bookPtr->title,title)){
            Book* newArray = (Book*)malloc(sizeof(Book));
            newArray->id = bookPtr->id;

            strcpy(str,bookPtr->title);
            newArray->title = (char*)malloc(sizeof(str));
            strcpy(newArray->title,str);
            memset(str,'\0',50);

            strcpy(str,bookPtr->authors);
            newArray->authors = (char*)malloc(sizeof(str));
            strcpy(newArray->authors,str);
            memset(str,'\0',50);

            newArray->year = bookPtr->year;
            newArray->copies = bookPtr->copies;
            newArray->next = NULL;

            // assign the newArray
            titleArray.length ++;
            arrayPtr->next = newArray;
            arrayPtr = arrayPtr->next;
            
        }
        bookPtr = bookPtr->next;
    }
    arrayPtr->next = NULL;
    return titleArray;
}

BookArray find_book_by_author (const char *author){
    // declare a BookArray
    BookArray authorArray;
    // initialize the book array
    char str[50];
    memset(str,'\0',50);
    authorArray.array = (Book*)malloc(sizeof(Book));
    authorArray.length = 0;

    Book* arrayPtr = authorArray.array;

    Book* bookPtr = headPtrBook->next;
    while(bookPtr != NULL){
        if(strstr(bookPtr->authors,author)){
            Book* newArray = (Book*)malloc(sizeof(Book));
            newArray->id = bookPtr->id;

            strcpy(str,bookPtr->title);
            newArray->title = (char*)malloc(sizeof(str));
            strcpy(newArray->title,str);
            memset(str,'\0',50);

            strcpy(str,bookPtr->authors);
            newArray->authors = (char*)malloc(sizeof(str));
            strcpy(newArray->authors,str);
            memset(str,'\0',50);

            newArray->year = bookPtr->year;
            newArray->copies = bookPtr->copies;
            newArray->next = NULL;

            // assign the newArray
            authorArray.length ++;
            arrayPtr->next = newArray;
            arrayPtr = arrayPtr->next;
            
        }
        bookPtr = bookPtr->next;
    }
    arrayPtr->next = NULL;
    return authorArray;
}

BookArray find_book_by_year (unsigned int year){
    char str[50];
    memset(str,'\0',50);
        // declare a BookArray
    BookArray yearArray;
    // initialize the book array
    yearArray.array = (Book*)malloc(sizeof(Book));
    yearArray.length = 0;

    Book* arrayPtr = yearArray.array;

    Book* bookPtr = headPtrBook->next;
    while(bookPtr != NULL){
        if(bookPtr->year == year){
            Book* newArray = (Book*)malloc(sizeof(Book));
            newArray->id = bookPtr->id;

            strcpy(str,bookPtr->title);
            newArray->title = (char*)malloc(sizeof(str));
            strcpy(newArray->title,str);
            memset(str,'\0',50);

            strcpy(str,bookPtr->authors);
            newArray->authors = (char*)malloc(sizeof(str));
            strcpy(newArray->authors,str);
            memset(str,'\0',50);
            newArray->year = bookPtr->year;
            newArray->copies = bookPtr->copies;
            newArray->next = NULL;

            // assign the newArray
            yearArray.length ++;
            arrayPtr->next = newArray;
            arrayPtr = arrayPtr->next;
            
        }
        bookPtr = bookPtr->next;
    }
    arrayPtr->next = NULL;
    return yearArray;
}

Book* findBookByID (unsigned int id){
    // declare a book pointer to traverse the linked list for books
    Book *bookPtr = headPtrBook->next;
    while(bookPtr != NULL){
        if(bookPtr->id == id){
            break;
        }
        bookPtr = bookPtr->next;
    }
    return bookPtr;
}

void borrowBook(Book* book, User user){
    book->copies--;
    BorrowBook* borrowBookPtr = user.borrowBook;
    // find the end of the borrowed book
    while(borrowBookPtr->next != NULL){
        borrowBookPtr = borrowBookPtr->next;
    }
    // new borrowBook
    BorrowBook* newBorrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
    newBorrowBook->id = book->id;

    char str[50];
    memset(str,'\0',50);

    strcpy(str,book->authors);
    newBorrowBook->authors = (char*)malloc(sizeof(str));
    strcpy(newBorrowBook->authors,str);
    memset(str,'\0',50);

    strcpy(str,book->title);
    newBorrowBook->title = (char*)malloc(sizeof(str));
    strcpy(newBorrowBook->title,str);
    memset(str,'\0',50);

    newBorrowBook->year = book->year;
    newBorrowBook->next = NULL;

    // assign the new borrowBook
    borrowBookPtr->next = newBorrowBook;
}

int checkSameBorrowBook(unsigned int id, User user){
    int i = 0;
    BorrowBook* borrowBookPtr = user.borrowBook->next;
    while(borrowBookPtr != NULL){
        if(borrowBookPtr->id == id){
            i = 1;
            break;
        }
        borrowBookPtr = borrowBookPtr->next;
    }
    return i;
}

BorrowBook* checkReturnBook(unsigned int id, User user){
    BorrowBook* borrowBookPtr = user.borrowBook->next;
    while(borrowBookPtr != NULL){
        if(borrowBookPtr->id == id){
            break;
        }
        borrowBookPtr = borrowBookPtr->next;
    }
    return borrowBookPtr;
}

void returnBook(BorrowBook* returnBook, User user){
    BorrowBook* borrowBookPtr = user.borrowBook;
    while(borrowBookPtr->next != returnBook && borrowBookPtr != NULL){
        borrowBookPtr = borrowBookPtr->next;
    }
    borrowBookPtr->next = returnBook->next;
    returnBook->next = NULL;
}

void searchForBook(char Menu[]){
    while (1){
        printf("Loading search menu...\n\n");
        printf("%s",Menu);
        scanf("%s",answer);
        // wrong option
        if(*answer <'1' || *answer > '4' || strlen(answer) >1){
            printf("Invalid option!\n");
            // find books by title
        }else if(*answer == '1'){
            memset(answer,'\0',50);
            getchar();
            printf("Please enter the title: ");
            scanf("%[^\n]s",answer);
             BookArray array;
            array = find_book_by_title(answer);
            // find the book
            if(array.array->next != NULL){
                displayBookArray(array);
                freeBookArray(array);
                // can not find the book
            }else{
                printf("No such book!\n");
                printf("********************\n");
            }
            // find books by author
        }else if(*answer == '2'){
            getchar();
            memset(answer,'\0',50);
            printf("Please enter the author: ");
            scanf("%[^\n]s",answer);
            BookArray array;
            array = find_book_by_author(answer);
            if(*answer >'0' && *answer <'9'){
                printf("Invalid author!\n");
                printf("********************\n");
            }// find the book
            else if(array.array->next != NULL){
                displayBookArray(array);
                freeBookArray(array);
                // can not find the book
            }else{
                printf("No such book!\n");
                printf("********************\n");
            }
            // find books by year
        }else if(*answer == '3'){
            printf("Please enter the year: ");
            scanf("%s",answer);
            BookArray array;
            array = find_book_by_year(atoi(answer));
            if(*answer <= '0' || *answer >'9'){
                printf("Invalid year!\n");
                printf("********************\n");
            }
            if(array.array->next != NULL){
                displayBookArray(array);
                freeBookArray(array);
            }else{
                printf("No such book!\n");
                printf("********************\n");
            }
            // return to previous menu
        }else if(*answer == '4'){
            break;
        }
    }
}

void freeBook(){
    Book* bookPtr;
    while(headPtrBook->next){
        bookPtr = headPtrBook->next;
        headPtrBook->next = bookPtr->next;
        free(bookPtr->title);
        free(bookPtr->authors);
        free(bookPtr);
    }
    free(headPtrBook);
}

void freeBookArray(BookArray bookArray){
    Book* bookPtr;
    while(bookArray.array->next){
        bookPtr = bookArray.array->next;
        bookArray.array->next = bookPtr->next;
        free(bookPtr->title);
        free(bookPtr->authors);
        free(bookPtr);
    }
    free(bookArray.array);
}