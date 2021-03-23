#include "../include/user.h"

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

void storeUsername(char username[], char password[]){
    // declare a user pointer to traverse the linked list for the username
    User* usrPtr = headPtrUser;
    while(usrPtr->next != NULL){
        usrPtr = usrPtr->next;
    }
    // declare a user pointer to store the new user and allocate the memory
    User *newUser = (User *)malloc(sizeof(User*));
    char str[30];

    strcpy(str,username);
    newUser->username = (char*)malloc(sizeof(str));
    strcpy(newUser->username,str);
    memset(str,'\0',30);

    strcpy(str,password);
    newUser->password = (char*)malloc(sizeof(str));
    strcpy(newUser->password,str);
    memset(str,'\0',30);

    newUser->borrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
    newUser->borrowBook->next = (BorrowBook*)malloc(sizeof(BorrowBook));
    newUser->borrowBook->next = NULL;
    // newUser->borrow = NULL;
    newUser->next = NULL;
    usrPtr->next = newUser;
}


int storeUserInFile(){
    FILE *file;
    file = fopen("../users.txt","w");
    if(!file){
        return -1;
    }
    User* userPtr = headPtrUser->next;
    char str[30];
    BorrowBook* borrowBookPtr;
    while(userPtr){
        strcpy(str,userPtr->username);
        fprintf(file,"%s\n",str);
        memset(str,'\0',30);
        
        strcpy(str,userPtr->password);
        fprintf(file,"%s\n\n",str);
        memset(str,'\0',30);

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
        fprintf(file,"**********\n");
        userPtr = userPtr->next;
    }
    fclose(file);
    return 0;
}

int loadUser(){
    FILE *file;
    file = fopen("../users.txt","r");
    if(!file){
        return -1;
    }
    BorrowBook* borrowBookPtr = headPtrBorrowBook;
    BorrowBook* newBorrowBook;
    User* userPtr;
    User* newUser;
    userPtr = headPtrUser;
    char str[30];
    while(!feof(file)){
        newUser = (User*)malloc(sizeof(User));
        newUser->borrowBook = headPtrBorrowBook;

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

        fscanf(file,"%[^\n]s",str);
        while(strcmp(str,"**********")){
            newBorrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
            fscanf(file,"%u",&newBorrowBook->id);
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
            fscanf(file,"%[^\n]s",str);
        }

        fgetc(file);
        fgetc(file);
        memset(str,'\0',strlen(str));
        newUser->next = NULL;
        userPtr->next = newUser;
        userPtr = newUser;
    }
    fclose(file);
    return 0;
}

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
