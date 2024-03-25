#ifndef AnnisaDian
int mainOpsi3(char *username);
void viewDecryptionKeyAndMessage(char nama_pengirimpesan[], char username[]);
void displayDecryptedMessage(const char *decryptedMsg);
void viewDecryptionKeyAndMessage(char nama_pengirimpesan[], char username[]);
void decryptRailFence(char encryptedMsg[], int key, char decryptedMsg[]);
int getLastMessageId(char filename[]);
int generateUniqueId(char filename[]);
void encryptMsg(char msg[], int key, char encryptedMsg[]);
#endif
