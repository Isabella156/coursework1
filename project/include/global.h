#ifndef GLOBAL_GUARD__H 
#define GLOBAL_GUARD__H

typedef struct _Book {
    unsigned int id; //Book ID
    char *title; //book title
    char *authors; //comma separated list of authors
    unsigned int year; // year of publication
    unsigned int copies; //number of copies the library has
    unsigned int initialCopies;
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

#endif