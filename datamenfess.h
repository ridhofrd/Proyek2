#ifndef datamenfess

int mainDataMenfess();
void vigenere_encrypt(const char *plaintext, const char *key, char *encrypted);
void viewAllMenfess(FILE *file);
void searchRecipient(FILE *file);
void viewStatistics(struct UserStats userStats[], int numUsers);

#endif