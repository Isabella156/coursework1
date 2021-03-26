#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/global.h"

extern User* headPtrUser;
extern BorrowBook* headPtrBorrowBook;

// function to check if the user name already exists
int checkUsername(char *name);
// function to store username
void storeUsername(char name[], char username[], char password[]);
// function to store user in file
int storeUserInFile();
// function to load user from the file
int loadUser();
// function to check password
User* checkPassword(char *username, char *password);
// function to free user memory
void freeUser();