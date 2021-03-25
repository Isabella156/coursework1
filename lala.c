#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*********************************global variables***********************************************/
    const char firstPrompt[] = "Please choose an option:\n1) Register an account\n2) Login\n\
3) Search for books\n4) Display all books\n5) Quit\n Option:";

    const char librarianPrompt[] = "Please choose an option:\n1) Add a book\n2) Remove a book\n\
3) Search for a book\n4) Display all books\n5) Log out\n Option:";

    const char searchMenu[] = "Please choose an option:\n1) Find books by title\n2) Find books \
by author\n3) Find books by year\n4) Return to previous menu\n Option:";

    const char invalidOption[] = "Sorry, the option you entered was invalid, please try again.\n\n";

    const char userPrompt[] = "Please enter an option:\n1) Borrow a book\n2) Return a book\n\
3) Search for book\n4) Display all books\n5) Log out\n Option: ";

    const char noSuchBook[] = "Sorry, no such book.\n";

    char answer[50];
    char answer2[50];
    char answer3[50];
    char *answerPtr = answer;
    char *answerPtr2 = answer2;
/**********************************global variables*********************************/

typedef struct _Book {
    unsigned int id; //Book ID
    char *title; //book title
    char *authors; //comma separated list of authors
    unsigned int year; // year of publication
    unsigned int copies; //number of copies the library has
    unsigned int initialCopies; // initial number of copies
    struct _Book *next;
}Book;

typedef struct _BookArray {
	Book* array; // pointer to array (or linked list) of struct Book.
	unsigned int length; // number of elements in the (Book*) array 
}BookArray;

typedef struct _BorrowBook{
    unsigned int id;
    char *title;
    char *authors;
    unsigned int year;
    struct _BorrowBook* next;
}BorrowBook;

// declare a struct to store user
typedef struct _User {
    char *name;
    char *username;
    char *password;
    // books that the user borrow
    BorrowBook *borrowBook;
    struct _User*next;
}User;

// a head pointer that points to the head node of the book
static Book *headPtrBook;

// a head pointer that points to the head node of the user
static User *headPtrUser;

/******************************************functions**********************************************/
// function to find book by id
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

void freeUser(){
     User* userPtr;
     BorrowBook* borrowBookPtr;
    while(headPtrUser->next){
        userPtr = headPtrUser->next;
        headPtrUser->next = userPtr->next;
        free(userPtr->name);
        free(userPtr->username);
        free(userPtr->password);
        while(userPtr->borrowBook->next){
            borrowBookPtr = userPtr->borrowBook->next;
            userPtr->borrowBook->next = borrowBookPtr->next;
            free(borrowBookPtr->title);
            free(borrowBookPtr->authors);
            free(borrowBookPtr);
        }
        free(userPtr);
    }
    free(headPtrUser);
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

// function to borrow books for user
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

// function to check if the user borrow two same book
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

//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
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


//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
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

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
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

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
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

//finds books with a given title.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
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

//finds books with the given authors.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
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

//finds books published in the given year.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
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

// function to display the book array
void displayBookArray(BookArray bookArray){
    // declare a book pointer to traverse the linked list for books
    Book *bookPtr = bookArray.array->next;
    printf("ID    Title                                                 Authors\
                                            Year  Copies\n");
    while(bookPtr != NULL){
        printf("%-2u    %-50s    %-50s ",bookPtr->id, bookPtr->title, bookPtr->authors);
        printf("%-4u  %-2u\n", bookPtr->year, bookPtr->copies);
        bookPtr = bookPtr->next;
    }
}

// function to display all books
void displayBooks(){
    Book* bookPtr = headPtrBook->next;
    printf("ID    Title                                                 Authors\
                                            Year  Copies\n");
    
    while(bookPtr != NULL){
        printf("%-2u    %-50s    %-50s ",bookPtr->id, bookPtr->title, bookPtr->authors);
        printf("%-4u  %-2u\n", bookPtr->year, bookPtr->copies);
        bookPtr = bookPtr->next;
    }
}

// function to display all borrow books
void displayBorrowBooks(User user){
    printf("ID    Title                                                 Authors\
                                               Year\n");
    BorrowBook* borrowBookPtr = user.borrowBook->next;
    while(borrowBookPtr != NULL){
        printf("%-2u    %-50s    %-50s    ",borrowBookPtr->id, borrowBookPtr->title, borrowBookPtr->authors);
        printf("%-4u\n", borrowBookPtr->year);
        borrowBookPtr = borrowBookPtr->next;
    }
}

// function to check the returned book
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

// function to return the book
void returnBook(BorrowBook* returnBook, User user){
    BorrowBook* borrowBookPtr = user.borrowBook;
    while(borrowBookPtr->next != returnBook && borrowBookPtr != NULL){
        borrowBookPtr = borrowBookPtr->next;
    }
    borrowBookPtr->next = returnBook->next;
    returnBook->next = NULL;
}

// function to check if the user name already exists
int checkUsername(char *name){
    // declare a user pointer to traverse the linked list for the user
    User *usrPtr = headPtrUser->next;
    int i = 0;
    while(usrPtr != NULL){
        if(!strcmp(usrPtr->username,name)){
            i = 1;
            break;
        }
        usrPtr = usrPtr->next;
    }
    return i;
}

// function to store username
void storeUsername(char name[], char username[], char password[]){
    // declare a user pointer to traverse the linked list for the username
    User* usrPtr = headPtrUser;
    while(usrPtr->next != NULL){
        usrPtr = usrPtr->next;
    }
    // declare a user pointer to store the new user and allocate the memory
    User *newUser = (User *)malloc(sizeof(User));
    char str[50];
    memset(str,'\0',50);

    strcpy(str, name);
    newUser->name = (char*)malloc(sizeof(str));
    strcpy(newUser->name,str);
    memset(str,'\0',50);


    strcpy(str,username);
    newUser->username = (char*)malloc(sizeof(str));
    strcpy(newUser->username,str);
    memset(str,'\0',50);

    strcpy(str,password);
    newUser->password = (char*)malloc(sizeof(str));
    strcpy(newUser->password,str);
    memset(str,'\0',50);

    newUser->borrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
    newUser->borrowBook->next = (BorrowBook*)malloc(sizeof(BorrowBook));
    newUser->borrowBook->next = NULL;
    // newUser->borrow = NULL;
    newUser->next = NULL;
    usrPtr->next = newUser;
}

// function to store user in file
int storeUserInFile(){
    FILE *file;
    file = fopen("users.txt","w");
    if(!file){
        printf("Error in handling files!\n");
        return -1;
    }
    User* userPtr = headPtrUser->next;
    char str[50];
    memset(str,'\0',50);
    BorrowBook* borrowBookPtr;
    while(userPtr){
        strcpy(str,userPtr->name);
        fprintf(file,"%s\n",str);
        memset(str,'\0',50);

        strcpy(str,userPtr->username);
        fprintf(file,"%s\n",str);
        memset(str,'\0',50);

        strcpy(str,userPtr->password);
        fprintf(file,"%s\n\n",str);
        memset(str,'\0',50);

        borrowBookPtr = userPtr->borrowBook->next;
        while(borrowBookPtr){
            fprintf(file,"%u\n",borrowBookPtr->id);
            strcpy(str,borrowBookPtr->title);
            fprintf(file,"%s\n",str);
            memset(str,'\0',30);
            strcpy(str,borrowBookPtr->authors);
            fprintf(file,"%s\n",borrowBookPtr->authors);
            memset(str,'\0',30);
            fprintf(file,"%u\n\n",borrowBookPtr->year);

            borrowBookPtr = borrowBookPtr->next;
        }

        if(userPtr->next == NULL){
            fprintf(file,"**********");
        }else{
            fprintf(file,"**********\n");
        }
        userPtr = userPtr->next;
    }
    fclose(file);
    return 0;
}

int loadUser(){
    FILE *file;
    file = fopen("users.txt","r");
    if(!file){
        printf("Error in handling files!\n");
        return -1;
    }
    BorrowBook* borrowBookPtr;
    BorrowBook* newBorrowBook;
    User* userPtr;
    User* newUser;
    userPtr = headPtrUser;
    char str[50];
    while(!feof(file)){
        newUser = (User*)malloc(sizeof(User));
        newUser->borrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
        newUser->borrowBook->authors = NULL;
        newUser->borrowBook->id = 0;
        newUser->borrowBook->title = NULL;
        newUser->borrowBook->year = 0;
        // newUser->borrowBook->next = (BorrowBook*)malloc(sizeof(BorrowBook));

        borrowBookPtr = newUser->borrowBook;

        fscanf(file,"%[^\n]s",str);
        newUser->name = (char*)malloc(sizeof(str));
        strcpy(newUser->name,str);
        memset(str,'\0',strlen(str));
        fgetc(file);

        fscanf(file,"%[^\n]s",str);
        newUser->username = (char*)malloc(sizeof(str));
        strcpy(newUser->username,str);
        memset(str,'\0',strlen(str));
        fgetc(file);

        fscanf(file,"%[^\n]s",str);
        newUser->password = (char*)malloc(sizeof(str));
        strcpy(newUser->password,str);
        memset(str,'\0',strlen(str));
        fgetc(file);
        fgetc(file);

        // for the ******
        fscanf(file,"%[^\n]s",str);
        while(strcmp(str,"**********")){
            newBorrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
            newBorrowBook->id = atoi(str);
            memset(str,'\0',strlen(str));
            fgetc(file);

            fscanf(file,"%[^\n]s",str);
            newBorrowBook->title = (char*)malloc(sizeof(str));
            strcpy(newBorrowBook->title,str);
            memset(str,'\0',strlen(str));
            fgetc(file);

            fscanf(file,"%[^\n]s",str);
            newBorrowBook->authors = (char*)malloc(sizeof(str));
            strcpy(newBorrowBook->authors,str);
            memset(str,'\0',strlen(str));
            fgetc(file);

            fscanf(file,"%u",&newBorrowBook->year);
            borrowBookPtr->next = newBorrowBook;
            borrowBookPtr = newBorrowBook;
            fgetc(file);
            fgetc(file);
            
            fscanf(file,"%[^\n]s",str);
        }
        borrowBookPtr->next = NULL;
        // for the /n
        fgetc(file);

        memset(str,'\0',strlen(str));
        newUser->next = NULL;
        userPtr->next = newUser;
        userPtr = newUser;
    }
    fclose(file);
    return 0;
}

// function to check password
User* checkPassword(char *username, char *password){
    // declare a user pointer to traverse the linked list for user
    User *userPtr = headPtrUser->next;
    while(userPtr != NULL){
        if(!strcmp(userPtr->username,username)){
            if(!strcmp(userPtr->password,password)){
                break;
            }
        }
        userPtr = userPtr->next;
    }

    return userPtr;
}

// function to 
// function to search for a book
void searchForBook(){
    while (1){
        printf("Loading search menu...\n\n");
        printf("%s",searchMenu);
        scanf("%s",answer);
        // wrong option
        if(*answer <'1' || *answer > '4' || strlen(answer) >1){
            printf("%s", invalidOption);
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
                printf("%s", noSuchBook);
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
            // find the book
            if(array.array->next != NULL){
                displayBookArray(array);
                freeBookArray(array);
                // can not find the book
            }else{
                printf("%s", noSuchBook);
                printf("********************\n");
            }
            // find books by year
        }else if(*answer == '3'){
            printf("Please enter the year: ");
            scanf("%s",answer);
            BookArray array;
            array = find_book_by_year(atoi(answer));
            if(array.array->next != NULL){
                displayBookArray(array);
                freeBookArray(array);
            }else{
                printf("%s", noSuchBook);
                printf("********************\n");
            }
            // return to previous menu
        }else if(*answer == '4'){
            break;
        }
    }
}

int main(void){
    // declaration of book
    headPtrBook = (Book*)malloc(sizeof(Book));
    headPtrBook->id = 0;
    headPtrBook->title = NULL;
    headPtrBook->authors = NULL;
    headPtrBook->year = 0;
    headPtrBook->copies = 0;
    headPtrBook->next = (Book*)malloc(sizeof(Book));
    headPtrBook->next = NULL;



    // declaration of library administrator (librarian)
    User* librarian = (User*)malloc(sizeof(User));
    char string[10] = "librarian";
    librarian->username = (char*)malloc(sizeof(string));
    librarian->password = (char*)malloc(sizeof(string));
    librarian->name = (char*)malloc(sizeof(string));
    librarian->name = string;
    librarian->username = string;
    librarian->password = string;
    librarian->borrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
    librarian->borrowBook->authors = NULL;
    librarian->borrowBook->id = 0;
    librarian->borrowBook->title = NULL;
    librarian->borrowBook->year = 0;
    librarian->borrowBook->next = (BorrowBook*)malloc(sizeof(BorrowBook));
    librarian->borrowBook->next = NULL;
    librarian->next = NULL;


    // declaration of users
    headPtrUser = (User*)malloc(sizeof(User));
    headPtrUser->name = NULL;
    headPtrUser->username = NULL;
    headPtrUser->password = NULL;
    headPtrUser->borrowBook = NULL;
    headPtrUser->next = (User*)malloc(sizeof(User));
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
            memset(answer,'\0',50);
            printf("Please enter the name: ");
            getchar();
            scanf("%[^\n]s",answer);
            memset(answer2,'\0',50);
            printf("Please enter a username: ");
            getchar();
            scanf("%[^\n]s",answer2);
            if(checkUsername(answer2)){
                printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
                printf("********************\n");
                continue;
            }
            printf("Please enter a password: ");
            getchar();
            memset(answer3,'\0',50);
            scanf("%s",answer3);
            storeUsername(answer, answer2, answer3);
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
                            char userName[50];
                            memset(userName,'\0',50);
                            strcpy(userName, currentUser.name);
                            printf("(logged in as: %s)\n",userName);
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
                                findBookByID(atoi(answer))->copies > 0 && !checkSameBorrowBook\
                                (atoi(answer),currentUser)){
                                    borrowBook(findBookByID(atoi(answer)),currentUser);
                                    store_books();
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
                                        store_books();
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
                }else{
                    printf("Incorrect password!\n");
                    printf("********************\n");
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
            freeUser();
            freeBook();
            printf("Thank you for using the library!\n");
            printf("********************\n");
            return 0;
        }
    }
}