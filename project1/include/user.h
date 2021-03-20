#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/global.h"




int checkUsername(char *name);
void storeUsername(char username[], char password[]);
int storeUserInFile(const char* filename);
int loadUser(const char* filename);
User* checkPassword(char *username, char *password);
void displayBorrowBooks(User user);

void displayBooks();