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
typedef struct Message {
    int status;
    int id;
    char timestamp[100];
    char nama_target[50];
    char nama_pengirim[100];
    int method;
    int n; // Ukuran matriks untuk metode 2
    char key[100];
    char encryptedMsg[100];
    struct Message *next;
} Message;

// Declare functions
void decryptRailFence(char encryptedMsg[], int key, char decryptedMsg[]);
void decryptVigenere(const char *encryptedMsg, const char *key, char *decryptedMsg);
void decryptVernam(char* cipher_text, char* key, char* decryptedMsg);
void displayDecryptedMessage(const char *decryptedMsg);
void viewDecryptionKeyAndMessage(char nama_pengirimpesan[], Message *head, const char *filename);

void clearScreen();
int countLinesInFile(const char *filename);
Message* createMessage(int status, int id, const char *timestamp, const char *nama_target, const char *nama_pengirim, int method, const char *key, int n, const char *encryptedMsg);
Message* loadMessagesFromFile(const char *filename);
int countUnreadMessages(Message *head);
void markMessageAsRead(Message *head, int messageId);
void saveMessagesToFile(const char *filename, Message *head);
void viewDecryptionKeyAndMessageUnRead(char nama_pengirimpesan[], Message *head, const char *filename);

#endif
