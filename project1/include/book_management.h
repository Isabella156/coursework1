#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H

typedef struct _Book {
    unsigned int id; //Book ID
    char *title; //book title
    char *authors; //comma separated list of authors
    unsigned int year; // year of publication
    unsigned int copies; //number of copies the library has
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
    char *username;
    char *password;
    // books that the user borrow
    BorrowBook *borrowBook;
    struct _User*next;
}User;

// a head pointer that points to the head node of the book
Book *headPtrBook;

// a head pointer that points to the head node of the user
User *headPtrUser;

// a head pointer that points to the head node of the user
BorrowBook *headPtrBorrowBook;

// declare a libaray administrator
User librarian;

/*********************************global variables***********************************************/
    const char firstPrompt[] = "Please choose an option:\n1) Register an account\n2) Login\n\
3) Search for books\n4) Display all books\n5) Quit\n Option:";

    const char librarianPrompt[] = "Please choose an option:\n1) Add a book\n2) Remove a book\n\
3) Search for a book\n4) Display all books\n5)Log out\n Option:";

    const char searchMenu[] = "Please choose an option:\n1) Find books by title\n2) Find books \
by author\n3) Find books by year\n4) Return to previous menu\n Option:";

    const char invalidOption[] = "Sorry, the option you entered was invalid, please try again.\n\n";

    const char userPrompt[] = "Please enter an option:\n1) Borrow a book\n2) Return a book\n\
3) Search for book\n4) Display all books\n5) Log out\n Option: ";

    const char noSuchBook[] = "Sorry, no such book.\n";

    char answer[10];
    char answer2[10];
    char *answerPtr = answer;
    char *answerPtr2 = answer2;
/**********************************global variables*********************************/

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
void searchForBook();
void nullifyString(char *string);
#endif