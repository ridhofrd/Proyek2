#ifndef MuhammadHarish
typedef struct {
    int id;
    char username[50];
    char password[50];
    char nim[20];
    char kelas[10];
} Member;

//enum untuk menampung jenis metode enkripsi
typedef enum {
    RAILFENCE =1,
    HILL =2,
    VERNAM =3,
    VIGENERE =4,
    RSA =5
} CipherType;

//struct untuk linked list pesan sebelum disimpan ke file
typedef struct {
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

MessageNode *head = NULL;
MessageNode *undoStack = NULL; // Stack for undo
MessageNode *redoStack = NULL; // Stack for redo


#define MAX_SIZE 100
#define MAX_MEMBERS 100

int readMembersFromFile(Member *members);
void printMenu();
void printOptions();
int processOption(int jumlahMember, Member *members, char username[]);
char *getUsernameFromID(int targetID, Member *members, int numMembers);
void printMembers(Member *members, int numMembers, char *loggedInUsername);
void selectMetode(int *selectedOptionR, char *msg);
void saveEncryptedMessageToFile(char nama_target[], char nama_pengirimpesan[], char msg[], int encryptionMethod);
int mainOpsi2(char username[100]);
void generate_key(int n, char* s, int key_matrix[MAX_SIZE][MAX_SIZE]);
void message_matrix(char* s, int n, int final_matrix[MAX_SIZE][MAX_SIZE][1], int* matrix_count);
void multiply_and_convert(int key[MAX_SIZE][MAX_SIZE], int message[MAX_SIZE][1], char res_alpha[MAX_SIZE][1], int n);
int is_valid_key(const char *key, int n);
int modInverse(int a, int m);

void addMessageToList(MessageNode *newNode);
void saveMessagesToFileRecursive(MessageNode *current, FILE *file);
void saveMessagesToFile();
void printMessageList();
void undoMessageDeletion();
void redoMessageDeletion();
void deleteLastMessage();
void deleteMessageList();
int isMessageListEmpty();

#endif
