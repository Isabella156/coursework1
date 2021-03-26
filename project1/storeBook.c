typedef struct _Book {
    unsigned int id; //Book ID
    char *title; //book title
    char *authors; //comma separated list of authors
    unsigned int year; // year of publication
    unsigned int copies; //number of copies the library has
    struct _Book *next;
}Book;

#include <stdio.h>
int main(void){
    Book BookOne, BookTwo, BookThree, BookFour, BookFive, BookSix, BookSeven, BookEight;
    BookOne.id = 1;
    BookOne.title ="Harry Potter and the Philosopher's Stone";
    BookOne.authors = "J.K. Rowling";
    BookOne.year = 1997;
    BookOne.copies = 5;
    BookOne.copies = 5;
    BookOne.next = &BookTwo;

    BookTwo.id = 2;
    BookTwo.title = "The Forgotten Room";
    BookTwo.authors = "Karen White,Beatriz Williams,Lauren Willing";
    BookTwo.year = 2016;
    BookTwo.copies = 2;
    BookTwo.copies = 2;
    BookTwo.next = &BookThree;

    BookThree.id = 3;
    BookThree.title = "Harry Potter and the Chamber of Secrets";
    BookThree.authors = "J.K. Rowling";
    BookThree.year = 1998;
    BookThree.copies = 12;
    BookThree.copies = 12;
    BookThree.next = &BookFour;

    BookFour.id = 4;
    BookFour.title = "Holidays on Ice";
    BookFour.authors = "David Sedaris";
    BookFour.year = 1997;
    BookFour.copies = 9;
    BookFour.copies = 9;
    BookFour.next = &BookFive;

    BookFive.id = 5;
    BookFive.title = "Java Programming";
    BookFive.authors = "asdf";
    BookFive.year = 1990;
    BookFive.copies = 8;
    BookFive.copies = 8;
    BookFive.next = &BookSix;

    BookSix.id = 6;
    BookSix.title = "C Programming";
    BookSix.authors = "Herbert Schedlt";
    BookSix.year = 1998;
    BookSix.copies = 2;
    BookSix.copies = 2;
    BookSix.next = &BookSeven;

    BookSeven.id = 7;
    BookSeven.title = "Python";
    BookSeven.authors = "abc";
    BookSeven.year = 1990;
    BookSeven.copies = 2;
    BookSeven.copies = 2;
    BookSeven.next = &BookEight;

    BookEight.id = 8;
    BookEight.title = "Algorithms";
    BookEight.authors = "asdff";
    BookEight.year = 1990;
    BookEight.copies = 2;
    BookEight.copies = 2;
    BookEight.next = (Book *)0;

    // a array contains books
    Book bookArray[8];
    bookArray[1] = BookOne;
    bookArray[2] = BookTwo;
    bookArray[3] = BookThree;
    bookArray[4] = BookFour;
    bookArray[5] = BookFive;
    bookArray[6] = BookSix;
    bookArray[7] = BookSeven;
    bookArray[8] = BookEight;

    // save books as text file
    FILE *file1;
    file1 = fopen("books.txt", "w");
    Book* bookPtr = &BookOne;
    
    while(bookPtr){
        if(bookPtr->next != NULL){
            fprintf(file1, "%u\n%s\n%s\n%u\n%u\n\n", bookPtr->id, bookPtr->title, bookPtr->authors,\
        bookPtr->year, bookPtr->copies);
        }else{
            fprintf(file1, "%u\n%s\n%s\n%u\n%u", bookPtr->id, bookPtr->title, bookPtr->authors,\
        bookPtr->year, bookPtr->copies);
        }
        // out put the data of the node to the file output.txt
        
        bookPtr = bookPtr->next;
    }
    fclose(file1);
    return 0;
}