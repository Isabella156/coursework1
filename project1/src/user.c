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
    newUser->borrowBook->next = NULL;
    newUser->next = NULL;
    usrPtr->next = newUser;
}


int storeUserInFile() {
    FILE* file;
    file = fopen("users.txt", "w");
    if (!file) {
        printf("Error in handling files!\n");
        return -1;
    }
    User* userPtr = headPtrUser->next;
    char str[50];
    memset(str,'\0',50);
    BorrowBook* borrowBookPtr;
    while (userPtr) {
        strcpy(str,userPtr->name);
        fprintf(file,"%s\n",str);
        memset(str,'\0',50);

        strcpy(str, userPtr->username);
        fprintf(file, "%s\n", str);
        memset(str, '\0', 50);

        strcpy(str, userPtr->password);
        fprintf(file, "%s\n\n", str);
        memset(str, '\0', 50);

        borrowBookPtr = userPtr->borrowBook->next;
        while (borrowBookPtr) {
            fprintf(file, "%u\n", borrowBookPtr->id);
            strcpy(str, borrowBookPtr->title);
            fprintf(file, "%s\n", str);
            memset(str, '\0', 30);
            strcpy(str, borrowBookPtr->authors);
            fprintf(file, "%s\n", borrowBookPtr->authors);
            memset(str, '\0', 30);
            fprintf(file, "%u\n\n", borrowBookPtr->year);

            borrowBookPtr = borrowBookPtr->next;
        }

        if (userPtr->next == NULL) {
            fprintf(file, "**********");
        }
        else {
            fprintf(file, "**********\n");
        }
        userPtr = userPtr->next;
    }
    fclose(file);
    return 0;
}

int loadUser() {
    FILE* file;
    file = fopen("users.txt", "r");
    if (!file) {
        printf("Error in handling files!\n");
        return -1;
    }
    BorrowBook* borrowBookPtr;
    BorrowBook* newBorrowBook;
    User* userPtr;
    User* newUser;
    userPtr = headPtrUser;
    char str[50];
    while (!feof(file)) {
        newUser = (User*)malloc(sizeof(User));
        newUser->borrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
        newUser->borrowBook->authors = NULL;
        newUser->borrowBook->id = 0;
        newUser->borrowBook->title = NULL;
        newUser->borrowBook->year = 0;

        borrowBookPtr = newUser->borrowBook;

        fscanf(file,"%[^\n]s",str);
        newUser->name = (char*)malloc(sizeof(str));
        strcpy(newUser->name,str);
        memset(str,'\0',strlen(str));
        fgetc(file);

        fscanf(file, "%[^\n]s", str);
        newUser->username = (char*)malloc(sizeof(str));
        strcpy(newUser->username, str);
        memset(str, '\0', strlen(str));
        fgetc(file);

        fscanf(file, "%[^\n]s", str);
        newUser->password = (char*)malloc(sizeof(str));
        strcpy(newUser->password, str);
        memset(str, '\0', strlen(str));
        fgetc(file);
        fgetc(file);

        // for the ******
        fscanf(file, "%[^\n]s", str);
        while (strcmp(str, "**********")) {
            newBorrowBook = (BorrowBook*)malloc(sizeof(BorrowBook));
            newBorrowBook->id = atoi(str);
            memset(str, '\0', strlen(str));
            fgetc(file);

            fscanf(file, "%[^\n]s", str);
            newBorrowBook->title = (char*)malloc(sizeof(str));
            strcpy(newBorrowBook->title, str);
            memset(str, '\0', strlen(str));
            fgetc(file);

            fscanf(file, "%[^\n]s", str);
            newBorrowBook->authors = (char*)malloc(sizeof(str));
            strcpy(newBorrowBook->authors, str);
            memset(str, '\0', strlen(str));
            fgetc(file);

            fscanf(file, "%u", &newBorrowBook->year);
            borrowBookPtr->next = newBorrowBook;
            borrowBookPtr = newBorrowBook;
            fgetc(file);
            fgetc(file);

            fscanf(file, "%[^\n]s", str);
        }
        borrowBookPtr->next = NULL;
        // for the /n
        fgetc(file);

        memset(str, '\0', strlen(str));
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
