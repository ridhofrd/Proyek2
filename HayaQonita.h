#ifndef HayaQonita.h
struct UserStats {
    char username[100];
    int messageCount;
};

void getCurrentTimestamp(char timestamp[]);
int mainDataMenfess();
void viewAllMenfess(FILE *file);
void searchRecipient(FILE *file);
void viewStatistics(struct UserStats userStats[], int numUsers);
void removeSpaces();
void decryptVigenere(const char *encryptedMsg, const char *key, char *decryptedMsg);
void vigenere_encrypt(const char *plaintext, const char *key, char *encrypted);
#endif

