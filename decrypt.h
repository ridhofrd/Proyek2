#ifndef DECRYPT_H
#define DECRYPT_H

// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Define constants
#define MAX 100

// Declare functions
void decryptRailFence(char encryptedMsg[], int key, char decryptedMsg[]);
void decryptVigenere(const char *encryptedMsg, const char *key, char *decryptedMsg);
void decryptVernam(char* cipher_text, char* key, char* decryptedMsg);
void displayDecryptedMessage(const char *decryptedMsg);
void viewDecryptionKeyAndMessage(char nama_pengirimpesan[], char username[]);
void clearScreen();
int countLinesInFile(const char *filename);

#endif
