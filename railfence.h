#ifndef railfence.h


int getLastMessageId(char filename[]);
int generateUniqueId(char filename[]);
void encryptMsg(char msg[], int key, char encryptedMsg[]);
void processUserMessage(char nama_user[]);
void decryptRailFence(char encryptedMsg[], int key, char decryptedMsg[]);
void viewDecryptionKeyAndMessage(char nama_user[]);
int mainRailFence();


#endif
