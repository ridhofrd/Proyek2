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

// Enum for encryption methods
typedef enum {
    RAILFENCE = 1,
    HILL = 2,
    VERNAM = 3,
    VIGENERE = 4,
    RSA = 5
} CipherType;

// Struct for linked list messages
typedef struct MessageNode {
    int status;
    int id_pesan;
    char timestamp[50];
    char nama_target[50];
    char nama_pengirimpesan[50];
    char ciphertext[50];
    CipherType type;
    union {
        struct {
            int keyangka;
        } railfence;
        struct {
            int n2;
            char keyhuruf[50];
        } hill;
        struct {
            char keyhuruf[50];
        } vernam;
        struct {
            char keyhuruf[50];
        } vigenere;
        struct {
            int p;
            int q;
        } rsa;
    } cipher;
    struct MessageNode *next;
} MessageNode;

// Declare functions
void decryptRailFence(char encryptedMsg[], int key, char decryptedMsg[]);
void decryptVigenere(const char *encryptedMsg, const char *key, char *decryptedMsg);
void decryptVernam(char* cipher_text, char* key, char* decryptedMsg);
void displayDecryptedMessage(const char *decryptedMsg);
void viewDecryptionKeyAndMessage(char nama_pengirimpesan[], MessageNode *head, const char *filename);
void decryptMessage(int key[MAX][MAX], int inverse[MAX][MAX], char cipher_text[], char decryptedMsg[], int n);
void clearScreen();
int countLinesInFile(const char *filename);
MessageNode* createMessageNode(int status, int id, const char *timestamp, const char *nama_target, const char *nama_pengirim, CipherType type, const char *key1, const char *key2, const char *ciphertext);
MessageNode* loadMessagesFromFile(const char *filename);
int countUnreadMessages(MessageNode *head);
void markMessageAsRead(MessageNode *head, int messageId);
void saveMessagesToFile(const char *filename, MessageNode *head);
void viewDecryptionKeyAndMessageUnRead(char nama_pengirimpesan[], MessageNode *head, const char *filename);

#endif
